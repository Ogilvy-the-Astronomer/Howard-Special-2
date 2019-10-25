#include "Texture.h"


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
		throw std::exception();
	}
	// Create and bind a texture.
	glGenTextures(1, &id);
	if (!id)
	{
		throw std::exception();
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
