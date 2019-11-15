#include "Core.h"
#include<exception>

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

