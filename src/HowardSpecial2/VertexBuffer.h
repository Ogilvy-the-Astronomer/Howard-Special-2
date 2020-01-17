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
	void add(glm::vec2 value); ///< add a vec2 value to the buffer
	void add(glm::vec3 value); ///< add a vec3 value to the buffer
	void add(glm::vec4 value); ///< add a vec4 value to the buffer

	int GetComponents(); ///< get the amount of components
	int GetDataSize(); ///< get the amount of data
	glm::fvec3 GetData(); ///< ¯\_(ツ)_/¯
	glm::vec3 GetVertexData(int tri, int vert); ///< get vertex data at triangle location and vertex location
	float GetData(int vert, int axis); ///< get vertex axis position at vertex and axis
	float GetData(int tri, int vert, int axis); ///< get vertex axis position at given triangle, vertex, and axis (useful for collisions)
	GLuint GetId();

};

