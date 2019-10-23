#pragma once
#include<vector>
#include<GL\glew.h>
#include<memory>

class VertexBuffer;

class VertexArray
{
private:
	GLuint id;
	std::vector<std::shared_ptr<VertexBuffer>> buffers;
	bool dirty;
public:
	VertexArray();
	VertexArray(std::string path);
	void splitStringWhitespace(std::string & input, std::vector<std::string>& output);
	void splitString(std::string & input, char splitter, std::vector<std::string>& output);
	~VertexArray();
	std::shared_ptr<VertexBuffer> GetBuffers(int _pos);
	void SetBuffer(std::string attribute, std::shared_ptr<VertexBuffer> buffer);

	int GetVertexCount();
	GLuint GetId();
};

