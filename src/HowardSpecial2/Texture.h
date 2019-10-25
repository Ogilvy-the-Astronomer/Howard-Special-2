#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "stb_image.h"
#include <string>


class Texture
{
	GLuint id;
public:
	GLuint GetId();
	Texture();
	Texture(std::string image);
	~Texture();
};

