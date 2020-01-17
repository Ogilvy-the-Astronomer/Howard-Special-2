#include "Texture.h"
#include "Exception.h"

GLuint Texture::GetId()
{
	return id;
}

Texture::Texture() {
}

Texture::Texture(std::string image)
{
	int w = 0;
	int h = 0;
	int channels = 0;
	id = 0;
	unsigned char *data = stbi_load(image.c_str(), &w, &h, &channels, 4);
	if (!data)
	{
		throw Exception("coudln't load image");
	}
	// Create and bind a texture.
	glGenTextures(1, &id);
	if (!id)
	{
		throw Exception("coudln't generate texture id");
	}
	glBindTexture(GL_TEXTURE_2D, id);
	// Upload the image data to the bound texture unit in the GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// Free the loaded data because we now have a copy on the GPU
	free(data);
	// Generate Mipmap so the texture can be mapped correctly
	glGenerateMipmap(GL_TEXTURE_2D);
	// Unbind the texture because we are done operating on it
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Texture::load(std::string image)
{
	int w = 0;
	int h = 0;
	int channels = 0;
	id = 0;
	unsigned char *data = stbi_load(image.c_str(), &w, &h, &channels, 4);
	if (!data)
	{
		throw Exception("coudln't load image");
	}
	// Create and bind a texture.
	glGenTextures(1, &id);
	if (!id)
	{
		throw Exception("coudln't generate texture id");
	}
	glBindTexture(GL_TEXTURE_2D, id);
	// Upload the image data to the bound texture unit in the GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// Free the loaded data because we now have a copy on the GPU
	free(data);
	// Generate Mipmap so the texture can be mapped correctly
	glGenerateMipmap(GL_TEXTURE_2D);
	// Unbind the texture because we are done operating on it
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
}



glm::vec2 Sprite::GetSize(){
	return glm::vec2(w, h);
}

void Sprite::load(std::string image)
{
	w = 0;
	h = 0;
	int channels = 0;
	id = 0;
	data = stbi_load(image.c_str(), &w, &h, &channels, 4);
	if (!data)
	{
		throw Exception("coudln't load image");
	}
	// Create and bind a texture.
	glGenTextures(1, &id);
	if (!id)
	{
		throw Exception("coudln't generate texture id");
	}
	glBindTexture(GL_TEXTURE_2D, id);
	// Upload the image data to the bound texture unit in the GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// Don't free the loaded data because we want to make smaller sprites out of it
	//free(data);
	// Generate Mipmap so the texture can be mapped correctly
	glGenerateMipmap(GL_TEXTURE_2D);
	// Unbind the texture because we are done operating on it
	glBindTexture(GL_TEXTURE_2D, 0);
}

std::shared_ptr<Texture> Sprite::createTextureFromSprite(int _left, int _top, int _width, int _height){
	std::shared_ptr<Texture> rtn = std::make_shared<Texture>();
	glGenTextures(1, &rtn->id);
	if (!rtn->id)
	{
		throw Exception("coudln't generate texture id");
	}
	glBindTexture(GL_TEXTURE_2D, rtn->id);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, w);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, _left);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, _top);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Upload the image data to the bound texture unit in the GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// Generate Mipmap so the texture can be mapped correctly
	glGenerateMipmap(GL_TEXTURE_2D);
	// Unbind the texture because we are done operating on it
	glBindTexture(GL_TEXTURE_2D, 0);

	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	return rtn;
}
