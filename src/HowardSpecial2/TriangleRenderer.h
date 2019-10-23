#include "Component.h"
#include "ShaderProgram.h"
#include "VertexArray.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <memory>

struct TriangleRenderer : public Component{
	TriangleRenderer();
	void OnUpdate();
	ShaderProgram shader;
	const GLfloat positions[9] = {
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};

	const GLfloat colors[12] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	};
	//std::shared_ptr<VertexBuffer> positions;
	//std::shared_ptr<VertexBuffer> colours;
	GLuint positionsVboId;
	GLuint vaoId;
	GLuint colorsVboId;

	SDL_Window *window;

};