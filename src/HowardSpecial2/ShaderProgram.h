#pragma once
#include<string>
#include<GL\glew.h>
#include<glm\glm.hpp>
#include<vector>
#include<memory>
#include<fstream>

struct Texture;
struct Mesh;
struct RenderTexture;
struct DepthCubemap;

struct Sampler
{
	GLint id;
	std::shared_ptr <Texture> texture;
};

class ShaderProgram
{
private:
	GLuint id;
	std::vector<Sampler> samplers;
public:
	ShaderProgram();
	ShaderProgram(std::string vert, std::string frag);
	ShaderProgram(std::string vert, std::string frag, std::string geom);
	~ShaderProgram();
	void Draw(std::shared_ptr<Mesh> vertextArray);
	void SetUniform(std::string uniform, std::shared_ptr<Texture> texture);
	void SetUniform(std::string uniform, glm::vec4 value);
	void SetUniform(std::string uniform, glm::vec3 value);
	void SetUniform(std::string uniform, glm::mat4 value);
	void SetUniform(std::string uniform, float value);
	void SetUniform(std::string uniform, int value);
	void printShaderInfoLog(GLuint obj);
	void printProgramInfoLog(GLuint obj);
	GLuint GetId();


};

