#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "stb_image.h"
#include <string>
#include "NonCopyable.h"
#include "Resource.h"

class Texture : private NonCopyable, public Resource
{
	GLuint id;
public:
	GLuint GetId();
	Texture();
	Texture(std::string image);
	std::shared_ptr<Texture> load(std::string image);
	~Texture();
};

