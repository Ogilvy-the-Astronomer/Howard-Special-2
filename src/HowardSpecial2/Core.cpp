#include "Core.h"

#include "Renderer.h"
#include "Transform.h"
#include "Mesh.h"
#include "Light.h"

#include "Camera.h"
#include "RenderTexture.h"
#include "ShaderProgram.h"
#include "Cubemap.h"
#include "DepthCubemap.h"
#include "Keyboard.h"
#include "BoxCollider.h"

#include<exception>
#include<iostream>

Core::Core()
{
	window_h = 900;
	window_w = 1600;
	graphicsContext = SDL_CreateWindow("Howard Special 2 Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_w, window_h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL); //create the program window

	if (!SDL_GL_CreateContext(graphicsContext)) { //throw exceptions if something goes wrong
		throw Exception("graphics context didn't get created properly");
	}
	if (glewInit() != GLEW_OK) {
		throw Exception("glew didn't get initializied properly");;
	}

   // Open up the OpenAL device
	device = alcOpenDevice(NULL);

	if (device == NULL) {
		throw Exception("there's no sound device to opem");
	}

	// Create audio context
	soundContext = alcCreateContext(device, NULL);

	if (soundContext == NULL) {
		alcCloseDevice(device);
		throw Exception("sound context didn't get created properly");
	}

	// Set as current context
	if (!alcMakeContextCurrent(soundContext)) {
		alcDestroyContext(soundContext);
		alcCloseDevice(device);
		throw Exception("sound context machine broke");
	}

	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f); //set the position of the listener.
	resources = std::make_shared<Resources>(); //create a list for resources (textures, sounds, meshes, etc)
	resources->resources.clear(); //empty the list

	shadowRender = std::make_shared<ShaderProgram>("../shaders/shadow_mapper.vert", "../shaders/shadow_mapper.frag"); //create the shader for rendering the scene to the shadowmap
	keyboard = std::make_shared<Keyboard>();
}

std::shared_ptr<GameObject> Core::AddObject(){
	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(); //create a game object
	gameObject->core = self; //assign a core reference to the game object
	gameObject->self = gameObject; //assign a reference to itself
	gameObject->id = createdObjectCount++;
	gameObject->name = std::string("Object: ") + std::to_string(gameObject->id);
	gameObjects.push_back(gameObject); //add it to the list of gameobjects
	return gameObject;
}

std::shared_ptr<GameObject> Core::AddObject(std::string _name) {
	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(); //create a game object
	gameObject->core = self; //assign a core reference to the game object
	gameObject->self = gameObject; //assign a reference to itself
	gameObject->id = createdObjectCount++;
	gameObject->name = _name;
	gameObjects.push_back(gameObject); //add it to the list of gameobjects
	return gameObject;
}

std::shared_ptr<Core> Core::Initialize() {
	std::shared_ptr<Core> rtn = std::make_shared<Core>();//create the core
	rtn->self = rtn; //give it a reference to itself
	return rtn;
}

void Core::Start() {
	keyboard->core = self.lock();
	lights = GetComponents<PointLight>(); //add a list of lights to the core
	renderers = GetComponents<Renderer>(); //add a list of visible objects to the core
	boxColliders = GetComponents<BoxCollider>();

	if (lights.size() != depthCubeTextures.size()) { //create a depth cube map for every light in the scene
		for (int i = 0; i < (int)lights.size(); i++) {
			depthCubeTextures.push_back(std::make_shared <DepthCubemap>());
		}
	}

	//enable face culling for performance and depth testing for shadow maps
	//glEnable(GL_CULL_FACE);
	renderTarget = std::make_shared<RenderTexture>(window_h, window_w);
	renderQuad = resources->load<Mesh>("../src/game/models/quad2.obj"); //TODO: not this
	renderShader = resources->load<ShaderProgram>("../shaders/rendtex");

	cubeMesh = resources->load<Mesh>("../src/game/models/cube.obj");
	std::vector<std::string> faces {
		"../src/game/textures/skybox/skybox0.jpg", 
		"../src/game/textures/skybox/skybox1.jpg", 
		"../src/game/textures/skybox/skybox2.jpg", 
		"../src/game/textures/skybox/skybox3.jpg", 
		"../src/game/textures/skybox/skybox5.jpg", 
		"../src/game/textures/skybox/skybox4.jpg"};
	skyboxTexture = std::make_shared<Cubemap>(faces);
	skyboxShader = resources->load<ShaderProgram>("../shaders/skybox");

	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < (int)gameObjects.size(); i++) { //go through list of all gameobjects and call start on them
		gameObjects.at(i)->Start();
	}
	lastTicks = 0.0f;
}

void Core::Stop() {
	alcMakeContextCurrent(NULL); //unassign the current audio context
	alcDestroyContext(soundContext); //destroy the audio context
	alcCloseDevice(device); //close the audio device
	SDL_DestroyWindow(graphicsContext); //destroy the graphics context
	/* Get average fps
	lowestfps = lowestfps / framecount;
	std::cout << lowestfps << std::endl;
	std::cin.get();
	*/
	SDL_Quit(); //quit sdl
}

void Core::Update(){
	keyboard->Update();
	for (int i = 0; i < (int)gameObjects.size(); i++) { //go through list of all gameobjects and call update on them
		gameObjects.at(i)->Update(deltaT);
	}
}

void Core::Display(){
	keyboard->Update();
	SDL_WarpMouseInWindow(NULL, window_w / 2, window_h / 2);

	currentTicks = SDL_GetTicks();
	deltaT = currentTicks - lastTicks;
	fps = glm::round(1000.0f / deltaT);
	deltaT *= 0.1f;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //clear the screen red
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color and depth buffer

	glEnable(GL_DEPTH_TEST); //enable depth testing
	//glDisable(GL_CULL_FACE); //disable face culling for more accurate shadows

	constexpr float farPlane = 200.0f;
	const glm::mat4 lightProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, farPlane); //create the projection matrix for the light

	for (int i = 0; i < (int)lights.size(); i++) {//go through every point light
		const glm::vec3 pos = lights[i]->GetGameObject()->GetTransform()->position; //get the light position
		std::vector<glm::mat4> cubeDirs; //create a list of 6 view-projection matrices for each face of the cubemap, multiplying the projection matrix by each of the 6 view matrices
		cubeDirs.push_back(lightProjection * glm::lookAt(pos, pos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		cubeDirs.push_back(lightProjection * glm::lookAt(pos, pos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f,-1.0f, 0.0f)));
		cubeDirs.push_back(lightProjection * glm::lookAt(pos, pos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
		cubeDirs.push_back(lightProjection * glm::lookAt(pos, pos + glm::vec3(0.0f,-1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
		cubeDirs.push_back(lightProjection * glm::lookAt(pos, pos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		cubeDirs.push_back(lightProjection * glm::lookAt(pos, pos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

		for (int k = 0; k < 6; k++) {// go through every cube face
			glActiveTexture(GL_TEXTURE0);//unassign the active texture
			glUseProgram(shadowRender->GetId());//use the main rendering program
			shadowRender->SetUniform("lightSpaceMatrix", cubeDirs[k]); //set the light mvp matrix for every face
			shadowRender->SetUniform("LightPos", lights[i]->GetGameObject()->GetTransform()->position);
			shadowRender->SetUniform("in_FarPlane", farPlane);
			glUseProgram(shadowRender->GetId()); //set uniform unbinds the current program so rebind it
			glBindFramebuffer(GL_FRAMEBUFFER, depthCubeTextures[i]->rtFBO); //bind the correct fbo
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_CUBE_MAP_POSITIVE_X + k, depthCubeTextures[i]->GetId(), 0); //assign a depth attachment to the correct face

			glViewport(0, 0, 2048, 2048); //resize the viewport for the shadowmap

			glClear(GL_DEPTH_BUFFER_BIT); //clear the depth buffer
			//GLenum res = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			//if (res != GL_FRAMEBUFFER_COMPLETE)
			//	std::cout << "Framebuffer not complete! Value = " << res << std::endl;



			for (int j = 0; j < (int)renderers.size(); j++) { //go through list of all renderers
				shadowRender->SetUniform("in_Model", renderers[j]->GetGameObject()->GetTransform()->GetModel()); //set the model matrix
				glUseProgram(shadowRender->GetId());
				glBindVertexArray(renderers[j]->shape->GetId()); //bind the mesh
				glDrawArrays(GL_TRIANGLES, 0, renderers[j]->shape->GetVertexCount()); //draw the mesh
				glBindVertexArray(0); //unbind the mesh

				renderers[j]->depthCubeTextures = depthCubeTextures; //assign the depth map to the renderer
			}
			glUseProgram(0); //unbind the program
			glBindFramebuffer(GL_FRAMEBUFFER, 0); //unbind the framebuffer
		}
	}
	glEnable(GL_CULL_FACE); //reset values to default
	glViewport(0, 0, window_w, window_h);

	glBindFramebuffer(GL_FRAMEBUFFER, renderTarget->rtFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color and depth buffer
	RenderSkybox();
	for (int i = 0; i < (int)gameObjects.size(); i++) { //go through list of gameobjects and call update on them, including the renderer which draws the object to the context
		gameObjects.at(i)->Update(deltaT);
		gameObjects.at(i)->Render();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	
	//quad stuff yes I need to wrap this
	glDisable(GL_DEPTH_TEST); //disable depth testing
	glDisable(GL_CULL_FACE);
	renderShader->SetUniform("in_Texture", renderTarget);
	renderShader->Draw(renderQuad);
	

	SDL_GL_SwapWindow(graphicsContext); //display context to screen
	lastTicks = currentTicks;
}

void Core::RenderSkybox() {
	glDepthMask(GL_FALSE);
	glDisable(GL_CULL_FACE);
	skyboxShader->SetUniform("in_Projection", mainCamera->GetComponent<Camera>()->GetProjection());
	skyboxShader->SetUniform("in_Skybox", skyboxTexture);
	skyboxShader->SetUniform("in_View", glm::mat4(glm::mat3(mainCamera->GetComponent<Camera>()->GetView())));

	skyboxShader->Draw(cubeMesh);

	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);

}

