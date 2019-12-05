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
struct DirectionalLight;

struct Core : private NonCopyable {
	Core();
	SDL_Window *graphicsContext;
	ALCcontext *soundContext;
	ALCdevice *device;
	int window_h;
	int window_w;
	std::shared_ptr<GameObject> mainCamera;
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	std::vector<std::shared_ptr<Renderer>> renderers;
	std::vector<std::shared_ptr<PointLight>> lights;
	std::vector<std::shared_ptr<DirectionalLight>> dLights;
	std::shared_ptr<Resources> resources;
	std::shared_ptr<GameObject> AddObject();
	void Start();
	void Stop();
	void Update();
	void Display();
	std::shared_ptr<Core> Initialize();

	std::shared_ptr<ShaderProgram> shadowRender;
	std::shared_ptr<ShaderProgram> depthMapRender;
	std::shared_ptr<RenderTexture> depthTexture;
	std::shared_ptr<RenderTexture> frameBuffer;
private:
	std::weak_ptr<Core> self;
	std::shared_ptr<Mesh> square;
};