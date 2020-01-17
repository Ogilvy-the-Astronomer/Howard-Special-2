#include "Keyboard.h"
#include "Core.h"

bool Keyboard::GetKey(SDL_Scancode key){ //check if the key is in the list of keys currently pressed
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

bool Keyboard::GetKey(SDL_Keycode key){//check if the key is in the list of keys currently pressed
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

bool Keyboard::GetKeyDown(SDL_Scancode key) {//check if the key is in the list of keys just pressed
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

bool Keyboard::GetKeyDown(SDL_Keycode key){ //check if the key is in the list of keys just pressed
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

bool Keyboard::GetKeyUp(SDL_Scancode key) { //check if the key is in the list of keys just released
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

bool Keyboard::GetKeyUp(SDL_Keycode key){//check if the key is in the list of keys just released
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

glm::vec2 Keyboard::GetMouseMovement() {
	SDL_GetMouseState(&mousePos.x, &mousePos.y); //get the mouse position
	mouseMovement = mousePos - glm::ivec2(core->window_w / 2, core->window_h / 2);
	return mouseMovement;
}

void Keyboard::Update(){
	keysDown.clear(); //clear the list of keys prssed and keys released
	keysUp.clear();
	SDL_Event event = { 0 }; //sdl events variable

	while (SDL_PollEvent(&event)) { //go through list of sdl events
		if (event.type == SDL_QUIT) { 
			
		}
		if (event.type == SDL_KEYDOWN) { //if a key is down, check if it's currently in the list of keys pressed and add it if it isn't
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
		if (event.type == SDL_KEYUP) { //if a key is released, add it to the list of keys released and remove it from the list of keys pressed
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

}
