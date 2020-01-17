#pragma once
#include "Texture.h"
#include <GL/glew.h>
/**
 * a cubemap framebuffer with only a depth component
 */
struct DepthCubemap : public Texture {
public:
	GLuint rtFBO; ///< frame buffer id
	DepthCubemap();
};