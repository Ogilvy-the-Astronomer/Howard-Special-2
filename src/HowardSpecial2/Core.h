#include<gl/glew.h>
#include<SDL2/SDL.h>
#include<vector>
#include "GameObject.h"

struct NonCopyable {
protected:
	NonCopyable() {}
	~NonCopyable() {}
private:
	NonCopyable(const NonCopyable &);
	NonCopyable& operator=(const NonCopyable &);

};

struct Core : private NonCopyable {
	Core();
	SDL_Window *window;
	int window_h;
	int window_w;
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	std::shared_ptr<GameObject> AddObject();
	void Start();
	void Stop();
	void Update();
};