#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "stb_image.h"
#include <string>
#include "NonCopyable.h"
#include "Resource.h"
/**
 * A texture 
 */
struct Texture : private NonCopyable, public Resource
{
protected:
	GLuint id; ///< texture id
public:
	GLuint GetId();
	Texture();
	Texture(std::string image);
	void load(std::string image);
	~Texture();
};

