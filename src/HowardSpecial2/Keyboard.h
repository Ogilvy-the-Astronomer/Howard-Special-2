#include "NonCopyable.h"
#include <SDL2/SDL.h>
#include <memory>
#include <list>
#include <glm/vec2.hpp>

struct Core;
/**
 * Input manager (mouse and keyboard (yes I know it's a misnomer))
 */
struct Keyboard : private NonCopyable {
	Keyboard();
	bool GetKey(SDL_Scancode key); ///<check if key is currently down
	bool GetKey(SDL_Keycode key); ///<check if key is currently down
	bool GetKeyDown(SDL_Scancode key); ///< check if key was pressed this frame
	bool GetKeyDown(SDL_Keycode key); ///< check is key was pressed this frame
	bool GetKeyUp(SDL_Scancode key); ///<check if key was released this frame
	bool GetKeyUp(SDL_Keycode key); ///<check if key was released this frame
	glm::vec2 GetMouseMovement(); ///<return the mouse movement
	friend struct Core;
private:
	std::list<SDL_Keycode> keysDown;///< list of keys pressed this frame (cleared every frame)
	std::list<SDL_Keycode> keysUp;///< list of keys released this frame (cleared every frame)
	std::list<SDL_Keycode> keys;///< list of keys currently down
	glm::vec2 mouseMovement; ///< change in mouse position
	glm::ivec2 mousePos; ///< current mouse position
	void Update(); ///< update input states every frame

	std::shared_ptr<Core> core; ///< reference to core
};