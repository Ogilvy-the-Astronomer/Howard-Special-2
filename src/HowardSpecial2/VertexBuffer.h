#pragma once
#include<glm/glm.hpp>
#include<vector>
#include<GL\glew.h>
#include "NonCopyable.h"
#include "Resource.h"
/**
 * A buffer for storing vertex data
 */
struct VertexBuffer : private NonCopyable, public Resource
{
private:
	GLuint id; ///< vertex buffer id
	int components; ///< amount of components in the buffer
	std::vector<GLfloat> data; ///< list of values
	bool dirty;

public:
	VertexBuffer();
	~VertexBuffer();
	void add(glm::vec2 value);
	void add(glm::vec3 value);
	void add(glm::vec4 value);

	int GetComponents();
	int GetDataSize();
	glm::fvec3 GetData();
	glm::vec3 GetVertexData(int tri, int vert);
	float GetData(int vert, int axis);
	float GetData(int tri, int vert, int axis);
	GLuint GetId();

};

