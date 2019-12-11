#include "Core.h"
//REDO SHADOW STUFF
#include "Renderer.h"
#include "Transform.h"
#include "Mesh.h"
#include "Light.h"
//REDO
#include<exception>
//#include "stb_vorbis.h"

Core::Core()
{
	window_h = 600;
	window_w = 600;
	graphicsContext = SDL_CreateWindow("Triangle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_w, window_h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(graphicsContext)) {
		throw std::exception();
	}
	if (glewInit() != GLEW_OK) {
		throw std::exception();
	}

	/*
   * Initialize OpenAL audio system
   */

   // Open up the OpenAL device
	device = alcOpenDevice(NULL);

	if (device == NULL)
	{
		throw std::exception();
	}

	// Create audio context
	soundContext = alcCreateContext(device, NULL);

	if (soundContext == NULL)
	{
		alcCloseDevice(device);
		throw std::exception();
	}

	// Set as current context
	if (!alcMakeContextCurrent(soundContext))
	{
		alcDestroyContext(soundContext);
		alcCloseDevice(device);
		throw std::exception();
	}

	// Generally not needed. Translate sources instead
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	resources = std::make_shared<Resources>();
	resources->resources.clear();

	shadowRender = std::make_shared<ShaderProgram>("../shaders/shadows.vert", "../shaders/shadows.frag");
	depthMapRender = std::make_shared<ShaderProgram>("../shaders/rendtex.vert", "../shaders/rendtex.frag");
	frameBuffer = std::make_shared<RenderTexture>(1);
}

std::shared_ptr<GameObject> Core::AddObject(){
	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
	gameObject->core = self;
	gameObjects.push_back(gameObject);
	gameObject->self = gameObject;
	return gameObject;
}

std::shared_ptr<Core> Core::Initialize() {
	std::shared_ptr<Core> rtn = std::make_shared<Core>();
	rtn->self = rtn;
	return rtn;
}

void Core::Start() {

}

void Core::Stop() {
	alcMakeContextCurrent(NULL);
	alcDestroyContext(soundContext);
	alcCloseDevice(device);
	SDL_DestroyWindow(graphicsContext);
	SDL_Quit();
}

void Core::Update(){
	for (int i = 0; i < (int)gameObjects.size(); i++) {
		gameObjects.at(i)->Update();
	}
}

void Core::Display(){
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//REDO SHADOW STUFF
	glEnable(GL_DEPTH_TEST);
	//glm::mat4 lightProjection = glm::ortho(100.0f, -100.0f, 100.0f, -100.0f, 1.0f, 500.0f);
	glm::mat4 lightProjection = glm::perspective(glm::radians(90.0f), 1.0f, 1.0f, 1000.0f);
	if (lights.size() != depthCubeTextures.size()) {
		for (int i = 0; i < lights.size(); i++) {
			depthCubeTextures.push_back(std::make_shared <DepthCubemap>());
		}
	}
	for (int i = 0; i < (int)lights.size(); i++) {
		glm::vec3 pos = lights[i]->GetGameObject()->GetComponent<Transform>()->position;
		std::vector<glm::mat4> cubeDirs;
		cubeDirs.push_back(lightProjection * glm::lookAt(pos, pos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		cubeDirs.push_back(lightProjection * glm::lookAt(pos, pos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f,-1.0f, 0.0f)));
		cubeDirs.push_back(lightProjection * glm::lookAt(pos, pos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
		cubeDirs.push_back(lightProjection * glm::lookAt(pos, pos + glm::vec3(0.0f,-1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
		cubeDirs.push_back(lightProjection * glm::lookAt(pos, pos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		cubeDirs.push_back(lightProjection * glm::lookAt(pos, pos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		//glm::mat4 lightView = glm::lookAt(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//glm::mat4 lightSpaceMatrix = lightProjection * lightView; //light mvp matrix
		//glViewport(0, 0, 2048, 2048);
		for (int k = 0; k < 6; k++) {
			glActiveTexture(GL_TEXTURE0);
			glUseProgram(shadowRender->GetId());
			shadowRender->SetUniform("lightSpaceMatrix", cubeDirs[k]); //set the light mvp matrix
			glUseProgram(shadowRender->GetId()); //set uniform unbinds the current program so rebind it
			glBindFramebuffer(GL_FRAMEBUFFER, depthCubeTextures[i]->rtFBO); //bind the correct fbo
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_CUBE_MAP_POSITIVE_X + k, depthCubeTextures[i]->GetId(), 0); //use the correct face

			glViewport(0, 0, 2048, 2048);

			glClear(GL_DEPTH_BUFFER_BIT);


			GLenum res = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			//if (res != GL_FRAMEBUFFER_COMPLETE)
			//	std::cout << "Framebuffer not complete! Value = " << res << std::endl;



			for (int j = 0; j < (int)renderers.size(); j++) {
				shadowRender->SetUniform("in_Model", renderers[j]->GetGameObject()->GetComponent<Transform>()->GetModel());
				glUseProgram(shadowRender->GetId());
				glBindVertexArray(renderers[j]->shape->GetId());
				glDrawArrays(GL_TRIANGLES, 0, renderers[j]->shape->GetVertexCount());
				glBindVertexArray(0);

				renderers[j]->depthCubeTextures = depthCubeTextures;
			}
			glUseProgram(0);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}

	glViewport(0, 0, window_h, window_w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color and depth buffer
	//REDO

	for (int i = 0; i < (int)gameObjects.size(); i++) {
		gameObjects.at(i)->Update();
	}
	glDisable(GL_DEPTH_TEST);
	SDL_GL_SwapWindow(graphicsContext);
}

