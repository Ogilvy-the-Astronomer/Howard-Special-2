#include "Cubemap.h"
#include "Exception.h"

#include <iostream>

Cubemap::Cubemap(std::vector<std::string> images) {
	int w = 0;
	int h = 0;
	int channels = 0;
	id = 0;
	
	// Create and bind a texture.
	glGenTextures(1, &id);
	if (!id)
	{
		throw Exception("coudln't generate texture id");
	}

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glBindTexture(GL_TEXTURE_CUBE_MAP, id); //bind the texture as a cube map
	for (unsigned int i = 0; i < 6; i++) { //attach depth components to each face
		unsigned char* data = stbi_load(images[i].c_str(), &w, &h, &channels, 4);
		if (!data)
		{
			throw Exception("couldn't load image");
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	//set the texture parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
