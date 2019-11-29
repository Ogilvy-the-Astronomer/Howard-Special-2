#include <HowardSpecial2/HowardSpecial2.h>
#include <SDL2/SDL.h>
#include <memory>

struct TriangleRenderer : public Component{
	TriangleRenderer();
	void OnUpdate();

	std::shared_ptr<ShaderProgram> shader = std::make_shared<ShaderProgram>("../shaders/text.vert", "../shaders/text.frag");
	std::shared_ptr<VertexBuffer> positions;
	std::shared_ptr<VertexBuffer> texCoords;
	std::shared_ptr<VertexBuffer> colors;
	std::shared_ptr<Mesh> shape;
	std::shared_ptr<Texture> tex;

	float angle;

};