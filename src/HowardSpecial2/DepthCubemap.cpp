#include "DepthCubemap.h"

#include <iostream>

DepthCubemap::DepthCubemap(){
	glGenTextures(1, &id); //assign texture id
	glGenFramebuffers(1, &rtFBO); //assign frame buffer id

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	const unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;
	glBindTexture(GL_TEXTURE_CUBE_MAP, id); //bind the texture as a cube map
	for (unsigned int i = 0; i < 6; i++) { //attach depth components to each face
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}
	//set the texture parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, rtFBO); //bind the frame buffer
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, id, 0); //add a depth attachment to the frame buffer texture
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	GLenum res = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (res != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete! Value = " << res <<std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0); //unbind the frame buffer

}
