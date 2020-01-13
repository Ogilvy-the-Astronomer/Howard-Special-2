#include "NonCopyable.h"
#include <SDL2/SDL.h>
#include <memory>
#include <list>

struct Keyboard : private NonCopyable {
	Keyboard();
	bool GetKey(SDL_Scancode key);
	bool GetKey(SDL_Keycode key);
	bool GetKeyDown(SDL_Scancode key);
	bool GetKeyDown(SDL_Keycode key);
	bool GetKeyUp(SDL_Scancode key);
	bool GetKeyUp(SDL_Keycode key);
	friend struct Core;
private:
	const Uint8 *state;
	Uint8 previousStateData;
	const Uint8 *previousState = &previousStateData;

	std::list<SDL_Keycode> keysDown;
	std::list<SDL_Keycode> keysUp;
	std::list<SDL_Keycode> keys;
	void Update();
};