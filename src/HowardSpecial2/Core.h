#include<gl/glew.h>
#include<SDL2/SDL.h>
#include<vector>
#include<AL/al.h>
#include<AL/alc.h>
#include "GameObject.h"
#include "Camera.h"
#include "NonCopyable.h"
#include "Resources.h"
#include "RenderTexture.h"
#include "ShaderProgram.h"

struct Renderer;
struct Mesh;
struct PointLight;

struct Core : private NonCopyable {
	Core();
	SDL_Window *graphicsContext;
	ALCcontext *soundContext;
	ALCdevice *device;
	int window_h;
	int window_w;
	std::shared_ptr<GameObject> mainCamera;
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	std::vector<std::shared_ptr<PointLight>> lights;
	std::vector<std::shared_ptr<Renderer>> renderers;
	std::shared_ptr<Resources> resources;
	std::shared_ptr<GameObject> AddObject();
	template <class T>
	std::vector<std::shared_ptr<T>> GetComponents();
	void Start();
	void Stop();
	void Update();
	void Display();
	std::shared_ptr<Core> Initialize();

	std::shared_ptr<ShaderProgram> shadowRender;
	std::shared_ptr<ShaderProgram> depthMapRender;
	std::vector<std::shared_ptr<RenderTexture>> depthTextures;
	std::shared_ptr<RenderTexture> frameBuffer;
private:
	std::weak_ptr<Core> self;
};

template<class T>
inline std::vector<std::shared_ptr<T>> Core::GetComponents(){
	std::vector<std::shared_ptr<T>> rtn;
	for (int i = 0; i < (int)gameObjects.size(); i++) {
		std::shared_ptr<T> toAdd = gameObjects.at(i)->GetComponent<T>();
		if (toAdd != nullptr) {
			rtn.push_back(toAdd);
		}
	}
	return rtn;
	
}
