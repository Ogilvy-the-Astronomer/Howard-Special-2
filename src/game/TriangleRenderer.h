#include <HowardSpecial2/HowardSpecial2.h>
#include <SDL2/SDL.h>
#include <memory>

struct TriangleRenderer : public Component{
	TriangleRenderer();
	void OnUpdate();

	std::shared_ptr<ShaderProgram> shader = std::make_shared<ShaderProgram>("../shaders/simple.vert", "../shaders/simple.frag");
	std::shared_ptr<VertexBuffer> positions;
	std::shared_ptr<VertexBuffer> texCoords;
	std::shared_ptr<VertexBuffer> colors;
	std::shared_ptr<VertexArray> shape;
	std::shared_ptr<Texture> tex = std::make_shared<Texture>("Textures/todd.png");

	float angle;

};