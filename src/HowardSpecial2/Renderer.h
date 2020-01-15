#include <SDL2/SDL.h>
#include <memory>
#include "Component.h"
#include "ShaderProgram.h"

struct Camera;
struct RenderTexture;
struct DepthCubemap;
/**
 * The renderer component which has the visual properties of the object and the functionality to draw it to the screen
 */
struct Renderer : public Component{
	friend struct Core;
	Renderer();
	Renderer(std::string _shape, std::string _texture); ///< consturct the renderer with textur and mesh provided at paths
	void OnDisplay();
	void OnUpdate(); ///< update the component and draw it to the screen
	std::shared_ptr<ShaderProgram> shader = std::make_shared<ShaderProgram>("../shaders/shadowing.vert", "../shaders/shadowing.frag"); ///< shader used to draw the object
	void SetMesh(std::shared_ptr<Mesh> _mesh); ///< set the object mesh
	void SetTexture(std::shared_ptr<Texture> _texture); ///< set the object texture
	
	std::vector<std::shared_ptr<RenderTexture>> depthTextures; ///<list of 2d shadow maps
	std::vector<std::shared_ptr<DepthCubemap>> depthCubeTextures; ///< list of shadow cubemaps
private:
	std::shared_ptr<Mesh> shape; ///< object mesh
	std::shared_ptr<Texture> texture; ///< object texture

	std::weak_ptr<GameObject> cam; ///< reference to the main camera
};