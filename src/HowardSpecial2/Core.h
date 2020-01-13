#include<gl/glew.h>
#include<SDL2/SDL.h>
#include<vector>
#include<AL/al.h>
#include<AL/alc.h>
#include "NonCopyable.h"

#include "GameObject.h"
#include "Resources.h"
/*
#include "Camera.h"

#include "Resources.h"
#include "RenderTexture.h"
#include "ShaderProgram.h"
#include "DepthCubemap.h"
*/

struct Renderer;
struct Mesh;
struct PointLight;

struct GameObject;
struct Camera;
struct ShaderProgram;
struct DepthCubemap;
struct RenderTexture;
struct Keyboard;
/**
 * The core of the engine with it's crucial functionalities
 */
struct Core : private NonCopyable {
	Core();
	SDL_Window *graphicsContext;
	ALCcontext *soundContext;
	ALCdevice *device;
	int window_h; ///<window height
	int window_w; ///<window width
	std::shared_ptr<GameObject> mainCamera; ///<reference to main camera
	std::vector<std::shared_ptr<GameObject>> gameObjects; ///<list of game objects
	std::vector<std::shared_ptr<PointLight>> lights; ///<list of point lights
	std::vector<std::shared_ptr<Renderer>> renderers; ///<list of renderers (visible objects)
	std::shared_ptr<Resources> resources; ///<list of resources (textures, meshes, sounds, etc)
	std::shared_ptr<GameObject> AddObject(); ///<create an object and add it to the list
	template <class T>
	std::vector<std::shared_ptr<T>> GetComponents(); ///<get a list of all specified components
	void Start();
	void Stop(); ///< shut down dependencies 
	void Update(); ///<go through all gameobjects and update all their components
	void Display(); ///< go through all gameobjects and update all their components and also renders shadows
	std::shared_ptr<Core> Initialize(); ///<intialize dependencies 
	std::shared_ptr<Keyboard> keyboard;

	std::shared_ptr<ShaderProgram> shadowRender; ///<shader that renders the shadow map
	//std::shared_ptr<ShaderProgram> depthMapRender; ///<shader that renders the shadow map
	std::vector<std::shared_ptr<RenderTexture>> depthTextures; ///<list of 2d depth maps
	std::vector<std::shared_ptr<DepthCubemap>> depthCubeTextures; ///<list of depth cube maps

private:
	std::weak_ptr<Core> self; ///<reference to self
	Uint32 currentTicks;
	Uint32 lastTicks;
	int lowestfps = 0;
	int framecount = 0;
};

template<class T>
inline std::vector<std::shared_ptr<T>> Core::GetComponents(){
	std::vector<std::shared_ptr<T>> rtn; //list of components to return
	for (int i = 0; i < (int)gameObjects.size(); i++) { //go through all gameobjects
		std::shared_ptr<T> toAdd = gameObjects.at(i)->GetComponent<T>(); //get component of type from current object
		if (toAdd != nullptr) {
			rtn.push_back(toAdd); //if there is a component add it to the return list
		}
	}
	return rtn;
	
}
