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
	std::shared_ptr<ShaderProgram> shader = std::make_shared<ShaderProgram>("../shaders/text.vert", "../shaders/text.frag");

	//SDL_Window *window; //REMOVE
private:
	std::shared_ptr<VertexArray> shape;
	std::shared_ptr<Texture> texture;

	std::weak_ptr<GameObject> cam;
};