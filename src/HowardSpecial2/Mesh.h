#pragma once
#include<vector>
#include<GL\glew.h>
#include<memory>
#include "Resource.h"

class VertexBuffer;

class Mesh : public Resource
{
private:
	GLuint id;
	std::vector<std::shared_ptr<VertexBuffer>> buffers;
	bool dirty;
public:
	Mesh();
	Mesh(std::string path);
	std::shared_ptr<Mesh> load(std::string path);
	void splitStringWhitespace(std::string & input, std::vector<std::string>& output);
	void splitString(std::string & input, char splitter, std::vector<std::string>& output);
	~Mesh();
	std::shared_ptr<VertexBuffer> GetBuffers(int _pos);
	void SetBuffer(std::string attribute, std::shared_ptr<VertexBuffer> buffer);

	int GetVertexCount();
	GLuint GetId();
};

