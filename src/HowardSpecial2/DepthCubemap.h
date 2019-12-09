#include "Resource.h"
#include <GL/glew.h>

struct DepthCubemap : public Resource {
protected:
	GLuint id;
public:
	GLuint rtFBO;
	GLuint GetId();
	DepthCubemap();
};