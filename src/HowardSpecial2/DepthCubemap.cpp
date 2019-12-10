#include "DepthCubemap.h"

#include <iostream>

DepthCubemap::DepthCubemap(){
	glGenTextures(1, &id);
	glGenFramebuffers(1, &rtFBO);

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	const unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
	for (unsigned int i = 0; i < 6; ++i) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, rtFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, id, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	GLenum res = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (res != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete! Value = " << res <<std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
