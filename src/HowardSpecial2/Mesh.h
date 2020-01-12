#pragma once
#include<vector>
#include<GL\glew.h>
#include<memory>
#include "Resource.h"

struct VertexBuffer;
/**
 * A struct for vertex arrays
 */
struct Mesh : public Resource
{
private:
	GLuint id; ///< vertex array id
	std::vector<std::shared_ptr<VertexBuffer>> buffers; ///< list of vertex buffers
	bool dirty;
public:
	Mesh();
	Mesh(std::string path);
	void load(std::string path); ///< load a mesh from a path
	void splitStringWhitespace(std::string & input, std::vector<std::string>& output);
	void splitString(std::string & input, char splitter, std::vector<std::string>& output);
	~Mesh();
	std::shared_ptr<VertexBuffer> GetBuffers(int _pos);
	void SetBuffer(std::string attribute, std::shared_ptr<VertexBuffer> buffer);

	int GetVertexCount();
	GLuint GetId();
};

