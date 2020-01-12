#pragma once
#include "Texture.h"
#include <GL/glew.h>

struct DepthCubemap : public Texture {
public:
	GLuint rtFBO; ///< frame buffer id
	DepthCubemap();
};