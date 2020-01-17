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
	friend struct Sprite;
	GLuint GetId();
	Texture();
	Texture(std::string image);
	void load(std::string image);
	~Texture();
};

struct Sprite : public Texture
{
protected:
	GLuint id; ///< texture id
	unsigned char* data;
	int w;
	int h;
public:
	glm::vec2 GetSize();
	void load(std::string image);
	std::shared_ptr<Texture> createTextureFromSprite(int _left, int _top, int _width, int _height);
};

