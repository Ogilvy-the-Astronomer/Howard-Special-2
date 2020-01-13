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

/**
 * A sampler for storing textures
 */
struct Sampler
{
	GLint id;
	int type;
	std::shared_ptr <Texture> texture;
};
/**
 * Class representing an opengl shader program
 */
struct ShaderProgram
{
private:
	GLuint id; ///< id of the shader
	std::vector<Sampler> samplers; ///< list of all samplers (textures)
public:
	ShaderProgram();
	ShaderProgram(std::string vert, std::string frag); ///< constructor taking in paths for the vertex and fragment shader sources
	ShaderProgram(std::string vert, std::string frag, std::string geom);
	~ShaderProgram();
	void Draw(std::shared_ptr<Mesh> vertextArray); ///< draws the specified mesh
	//functions for setting different types of uniforms in the shader
	void SetUniform(std::string uniform, std::shared_ptr<Texture> texture);
	void SetUniform(std::string uniform, std::shared_ptr<DepthCubemap> texture);
	void SetUniform(std::string uniform, glm::vec4 value);
	void SetUniform(std::string uniform, glm::vec3 value);
	void SetUniform(std::string uniform, glm::mat4 value);
	void SetUniform(std::string uniform, float value);
	void SetUniform(std::string uniform, int value);
	//debug functions
	void printShaderInfoLog(GLuint obj);
	void printProgramInfoLog(GLuint obj);
	GLuint GetId();


};

