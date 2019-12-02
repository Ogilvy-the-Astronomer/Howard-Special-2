#include <SDL2/SDL.h>
#include <memory>
#include "Component.h"
#include "ShaderProgram.h"

struct Camera;

struct Renderer : public Component{
	Renderer();
	Renderer(std::string _shape, std::string _texture);
	void OnDisplay();
	void OnUpdate();
	std::shared_ptr<ShaderProgram> shader = std::make_shared<ShaderProgram>("../shaders/light.vert", "../shaders/light.frag");
	void SetMesh(std::shared_ptr<Mesh> mesh);
	void SetTexture(std::shared_ptr<Texture> image);
	//SDL_Window *window; //REMOVE
private:
	std::shared_ptr<Mesh> shape;
	std::shared_ptr<Texture> texture;

	std::weak_ptr<GameObject> cam;
};