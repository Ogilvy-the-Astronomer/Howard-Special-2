#include <SDL2/SDL.h>
#include <memory>
#include "Component.h"
#include "ShaderProgram.h"

struct Renderer : public Component{
	Renderer();
	Renderer(std::string _shape, std::string _texture);
	void OnDisplay();
	std::shared_ptr<ShaderProgram> shader = std::make_shared<ShaderProgram>("../shaders/text.vert", "../shaders/text.frag");
private:
	std::shared_ptr<VertexArray> shape;
	std::shared_ptr<Texture> texture;
};