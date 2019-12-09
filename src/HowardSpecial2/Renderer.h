#include <SDL2/SDL.h>
#include <memory>
#include "Component.h"
#include "ShaderProgram.h"

struct Camera;
struct RenderTexture;
struct DepthCubemap;

struct Renderer : public Component{
	friend struct Core;
	Renderer();
	Renderer(std::string _shape, std::string _texture);
	void OnDisplay();
	void OnUpdate();
	std::shared_ptr<ShaderProgram> shader = std::make_shared<ShaderProgram>("../shaders/shadowing.vert", "../shaders/shadowing.frag");
	void SetMesh(std::shared_ptr<Mesh> mesh);
	void SetTexture(std::shared_ptr<Texture> image);
	
	std::vector<std::shared_ptr<RenderTexture>> depthTextures;
	std::vector<std::shared_ptr<DepthCubemap>> depthCubeTextures;
private:
	std::shared_ptr<Mesh> shape;
	std::shared_ptr<Texture> texture;

	std::weak_ptr<GameObject> cam;
};