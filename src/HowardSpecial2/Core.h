#include<gl/glew.h>
#include<SDL2/SDL.h>

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
	~Core();
	SDL_Window *window;
	int window_h;
	int window_w;
private:
	void Start();
	void Stop();
};