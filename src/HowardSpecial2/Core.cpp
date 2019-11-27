#include "Core.h"
#include<exception>
//#include "stb_vorbis.h"

Core::Core()
{
	window_h = 300;
	window_w = 300;
	window = SDL_CreateWindow("Triangle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_w, window_h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(window)) {
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
	context = alcCreateContext(device, NULL);

	if (context == NULL)
	{
		alcCloseDevice(device);
		throw std::exception();
	}

	// Set as current context
	if (!alcMakeContextCurrent(context))
	{
		alcDestroyContext(context);
		alcCloseDevice(device);
		throw std::exception();
	}

	// Generally not needed. Translate sources instead
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	
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
	alcDestroyContext(context);
	alcCloseDevice(device);
	SDL_DestroyWindow(window);
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
	//TODO: Get component renderer, get camera
	for (int i = 0; i < (int)gameObjects.size(); i++) {
		gameObjects.at(i)->Update();
	}
	SDL_GL_SwapWindow(window);
}

