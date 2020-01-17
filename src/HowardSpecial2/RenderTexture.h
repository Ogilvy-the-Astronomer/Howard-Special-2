#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "stb_image.h"
#include <string>
#include "Texture.h"

/**
 * texture that can be drawn to by the camera
 */
struct RenderTexture : public Texture
{
public:
	GLuint rtFBO; ///< frame buffer object id
	RenderTexture(); ///< constructor for depth maps
	RenderTexture(int _o); ///< regular constructor
	~RenderTexture();
};