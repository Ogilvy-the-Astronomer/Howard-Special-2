#include "Component.h"
#include "ShaderProgram.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

struct TriangleRenderer : public Component{
	TriangleRenderer();
	void OnUpdate();
	ShaderProgram shader;
	const GLfloat positions[9] = {
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};
	GLuint positionsVboId;
	GLuint vaoId;

	SDL_Window *window;

};