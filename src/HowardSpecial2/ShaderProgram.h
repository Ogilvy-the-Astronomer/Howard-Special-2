#pragma once
#include<string>
#include<GL\glew.h>
#include<glm\glm.hpp>
#include<vector>
#include<memory>
#include<fstream>
#include "Resource.h"
#include "NonCopyable.h"

struct Texture;
struct Mesh;
struct RenderTexture;
struct DepthCubemap;

/**
 * A sampler for storing textures
 */
struct Sampler
{
	GLint id; ///< sampler id
	int type; ///< sampler type, for distinguishing 2d textures and cubemaps
	std::shared_ptr <Texture> texture; ///<pointer to a texture
};
/**
 * Class representing an opengl shader program
 */
struct ShaderProgram : private NonCopyable, public Resource
{
private:
	GLuint id; ///<id of the shader
	std::vector<Sampler> samplers; ///< list of all samplers (textures)
public:
	ShaderProgram();
	ShaderProgram(std::string vert, std::string frag); ///< constructor taking in paths for the vertex and fragment shader sources
	void load(std::string path);
	~ShaderProgram();
	void Draw(std::shared_ptr<Mesh> vertextArray); ///< draws the specified mesh
	//functions for setting different types of uniforms in the shader
	void SetUniform(std::string uniform, std::shared_ptr<Texture> texture); ///< set texture uniform
	void SetUniform(std::string uniform, std::shared_ptr<DepthCubemap> texture);///< set cube map uniform
	void SetUniform(std::string uniform, glm::vec4 value);///< set vec4 uniform
	void SetUniform(std::string uniform, glm::vec3 value);///< set vec3 uniform
	void SetUniform(std::string uniform, glm::mat4 value);///< set matrix uniform
	void SetUniform(std::string uniform, float value);///< set float uniform
	void SetUniform(std::string uniform, int value);///< set integer uniform
	//debug functions
	void printShaderInfoLog(GLuint obj);///< print what's wrong with the shader
	void printProgramInfoLog(GLuint obj);///< print what's wrong with the program
	GLuint GetId();


};

