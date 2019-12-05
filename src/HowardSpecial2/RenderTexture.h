#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "stb_image.h"
#include <string>
#include "Texture.h"

struct RenderTexture : public Texture
{
public:
	GLuint rtFBO;
	RenderTexture();
	RenderTexture(int _o);
	~RenderTexture();
};