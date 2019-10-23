#include "../HowardSpecial2/Component.h"
#include "../HowardSpecial2/ShaderProgram.h"
#include "../HowardSpecial2/VertexBuffer.h"
#include "../HowardSpecial2/VertexArray.h"

#include <SDL2/SDL.h>
#include <memory>

struct TriangleRenderer : public Component{
	TriangleRenderer();
	void OnUpdate();

	std::shared_ptr<ShaderProgram> shader = std::make_shared<ShaderProgram>("../shaders/simple.vert", "../shaders/simple.frag");
	std::shared_ptr<VertexBuffer> positions;
	std::shared_ptr<VertexBuffer> colors;
	std::shared_ptr<VertexArray> shape;

	SDL_Window *window;

	float angle;

};