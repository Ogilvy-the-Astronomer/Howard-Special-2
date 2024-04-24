#pragma once
#include "Texture.h"
#include <GL/glew.h>
#include <vector>
/**
 * a cubemap framebuffer with only a depth component
 */
struct Cubemap : public Texture {
public:
	Cubemap(std::vector<std::string> images);
};