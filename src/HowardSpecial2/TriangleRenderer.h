#include "Component.h"
#include <GL/glew.h>

struct TriangleRenderer : public Component{
	TriangleRenderer();

	const GLfloat positions[9] = {
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};

};