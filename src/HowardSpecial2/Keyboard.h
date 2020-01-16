#include "NonCopyable.h"
#include <SDL2/SDL.h>
#include <memory>
#include <list>
#include <glm/vec2.hpp>

struct Core;

struct Keyboard : private NonCopyable {
	Keyboard();
	bool GetKey(SDL_Scancode key);
	bool GetKey(SDL_Keycode key);
	bool GetKeyDown(SDL_Scancode key);
	bool GetKeyDown(SDL_Keycode key);
	bool GetKeyUp(SDL_Scancode key);
	bool GetKeyUp(SDL_Keycode key);
	glm::vec2 GetMouseMovement();
	friend struct Core;
private:
	std::list<SDL_Keycode> keysDown;
	std::list<SDL_Keycode> keysUp;
	std::list<SDL_Keycode> keys;
	glm::vec2 mouseMovement;
	glm::ivec2 mousePos;
	void Update();

	std::shared_ptr<Core> core;
};