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
	glViewport(0, 0, 2048, 2048);
	glm::mat4 lightProjection = glm::ortho(100.0f, -100.0f, 100.0f, -100.0f, 1.0f, 500.0f);
	if (lights.size() != depthTextures.size()) {
		for (int i = 0; i < lights.size(); i++) {
			depthTextures.push_back(std::make_shared <RenderTexture>());
		}
	}
	for (int i = 0; i < (int)lights.size(); i++) {
		glm::mat4 lightView = glm::lookAt(lights[i]->GetGameObject()->GetComponent<Transform>()->position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 lightSpaceMatrix = lightProjection * lightView; //light mvp matrix
		//depthTextures.push_back(std::make_shared <RenderTexture>());
		glUseProgram(shadowRender->GetId());
		glBindFramebuffer(GL_FRAMEBUFFER, depthTextures[i]->rtFBO); //bind the correct fbo
		glClear(GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		shadowRender->SetUniform("lightSpaceMatrix", lightSpaceMatrix); //set the light mvp matrix
		glUseProgram(shadowRender->GetId()); //set uniform unbinds the current program so rebind it
		glBindFramebuffer(GL_FRAMEBUFFER, depthTextures[i]->rtFBO);
		//TODO: Get component renderer, get camera
		for (int j = 0; j < (int)renderers.size(); j++) {
			shadowRender->SetUniform("in_Model", renderers[j]->GetGameObject()->GetComponent<Transform>()->GetModel());
			glUseProgram(shadowRender->GetId());
			glBindVertexArray(renderers[j]->shape->GetId());
			glDrawArrays(GL_TRIANGLES, 0, renderers[j]->shape->GetVertexCount());
			glBindVertexArray(0);

			renderers[j]->depthTextures = depthTextures;
		}
		glUseProgram(0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	//depthTextures.clear();

	glViewport(0, 0, window_h, window_w);
	//glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer->rtFBO); //bind the correct fbo
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color and depth buffer
	//REDO

	for (int i = 0; i < (int)gameObjects.size(); i++) {
		gameObjects.at(i)->Update();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);

	SDL_GL_SwapWindow(graphicsContext);
}

