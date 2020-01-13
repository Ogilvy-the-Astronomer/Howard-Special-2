#include "Keyboard.h"


bool Keyboard::GetKey(SDL_Scancode key){
	SDL_Keycode Key = SDL_GetKeyFromScancode(key);
	auto it = keys.begin();
	while (it != keys.end()) {
		if (Key == *it) {
			return true;
		}
		else {
			it++;
		}
	}
	return false;
}

bool Keyboard::GetKey(SDL_Keycode key){
	auto it = keys.begin();
	while (it != keys.end()) {
		if (key == *it) {
			return true;
		}
		else {
			it++;
		}
	}
	return false;
}

bool Keyboard::GetKeyDown(SDL_Scancode key) {
	SDL_Keycode Key = SDL_GetKeyFromScancode(key);
	auto it = keysDown.begin();
	while (it != keysDown.end()) {
		if (Key == *it) {
			return true;
		}
		else {
			it++;
		}
	}
	return false;
}

bool Keyboard::GetKeyDown(SDL_Keycode key){
	auto it = keysDown.begin();
	while (it != keysDown.end()) {
		if (key == *it) {
			return true;
		}
		else {
			it++;
		}
	}
	return false;
}

bool Keyboard::GetKeyUp(SDL_Scancode key) {
	SDL_Keycode Key = SDL_GetKeyFromScancode(key);
	auto it = keysUp.begin();
	while (it != keysUp.end()) {
		if (Key == *it) {
			return true;
		}
		else {
			it++;
		}
	}
	return false;
}

bool Keyboard::GetKeyUp(SDL_Keycode key){
	auto it = keysUp.begin();
	while (it != keysUp.end()) {
		if (key == *it) {
			return true;
		}
		else {
			it++;
		}
	}
	return false;
}

void Keyboard::Update(){
	keysDown.clear();
	keysUp.clear();
	SDL_Event event = { 0 }; //sdl events variable

	while (SDL_PollEvent(&event)) { //go through list of sdl events
		if (event.type == SDL_QUIT) { //end the game if hit escape or close the window then exit the game
			//quit = true;
		}
		if (event.type == SDL_KEYDOWN) {
			bool alreadyPressed = false;
			auto it = keys.begin();
			while (it != keys.end()) {
				if (event.key.keysym.sym == *it) {
					alreadyPressed = true;
				}
				it++;
			}
			if (!alreadyPressed) {
				keysDown.push_back(event.key.keysym.sym);
				keys.push_back(event.key.keysym.sym);
			}
		}
		if (event.type == SDL_KEYUP) {
			keysUp.push_back(event.key.keysym.sym);

			auto it = keys.begin();
			while (it != keys.end()) {
				if (event.key.keysym.sym == *it) {
					it = keys.erase(it);
				}
				else {
					it++;
				}
			}
		}
	}
}

Keyboard::Keyboard() {
	previousState = new Uint8;
	state = SDL_GetKeyboardState(NULL);
}
