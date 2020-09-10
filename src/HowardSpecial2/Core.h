#include<gl/glew.h>
#include<SDL2/SDL.h>
#include<vector>
#include<AL/al.h>
#include<AL/alc.h>
#include<iostream>
#include "NonCopyable.h"

#include "GameObject.h"
#include "Resources.h"

struct Renderer;
struct Mesh;
struct PointLight;

struct GameObject;
struct Camera;
struct ShaderProgram;
struct DepthCubemap;
struct RenderTexture;
struct Keyboard;
struct BoxCollider;
/**
 * The core of the engine with it's crucial functionalities
 */
struct Core : private NonCopyable {
	Core();
	SDL_Window *graphicsContext; ///< the screen
	ALCcontext *soundContext; ///< the sound "screen"
	ALCdevice *device; ///< audio playback device
	int window_h; ///<window height
	int window_w; ///<window width
	std::shared_ptr<GameObject> mainCamera; ///<reference to main camera
	std::vector<std::shared_ptr<GameObject>> gameObjects; ///<list of game objects
	std::vector<std::shared_ptr<PointLight>> lights; ///<list of point lights
	std::vector<std::shared_ptr<Renderer>> renderers; ///<list of renderers (visible objects)
	std::vector<std::shared_ptr<BoxCollider>> boxColliders; ///<list of renderers (visible objects)
	std::shared_ptr<Resources> resources; ///<list of resources (textures, meshes, sounds, etc)
	std::shared_ptr<GameObject> AddObject(); ///<create an object and add it to the list
	template <class T>
	std::vector<std::shared_ptr<T>> GetComponents(); ///<get a list of all specified components
	void Start(); ///< calls start function on all objects
	void Stop(); ///< shut down dependencies 
	void Update(); ///<go through all gameobjects and update all their components
	void Display(); ///< go through all gameobjects and update all their components and also renders shadows
	std::shared_ptr<Core> Initialize(); ///<intialize dependencies 
	std::shared_ptr<Keyboard> keyboard; ///< input handler (does mouse input to)

	std::shared_ptr<ShaderProgram> shadowRender; ///<shader that renders the shadow map
	//std::shared_ptr<ShaderProgram> depthMapRender; ///<shader that renders the shadow map
	std::vector<std::shared_ptr<RenderTexture>> depthTextures; ///<list of 2d depth maps
	std::vector<std::shared_ptr<DepthCubemap>> depthCubeTextures; ///<list of depth cube maps

	float fps;
	float deltaT;
private:
	std::weak_ptr<Core> self; ///<reference to self
	Uint32 currentTicks; ///< total amount of tick since startup
	Uint32 lastTicks; ///< ticks last frame
	int lowestfps = 0;
	int framecount = 0;
};

template<class T>
inline std::vector<std::shared_ptr<T>> Core::GetComponents(){
	std::vector<std::shared_ptr<T>> rtn; //list of components to return
	std::shared_ptr<T> toAdd;
	for (int i = 0; i < (int)gameObjects.size(); i++) { //go through all gameobjects
		toAdd = nullptr;
		try{
		toAdd = gameObjects.at(i)->GetComponent<T>(); //get component of type from current object
		}
		catch (Exception& e) {
			if(e.what() == ""){
				std::cout << "Exception: " << e.what() << std::endl; //getcomponent throws an exception when we look for a component on an object that doesn't have it
			}														 //which is fine in this case because we have to look for the speciied component on every object 
		}
		if (toAdd != nullptr) {
			rtn.push_back(toAdd); //if there is a component add it to the return list
		}
	}
	return rtn;
	
}
