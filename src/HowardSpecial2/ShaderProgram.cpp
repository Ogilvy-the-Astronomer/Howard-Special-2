#include "ShaderProgram.h"
#include "Mesh.h"
#include "Texture.h"
#include "DepthCubemap.h"
#include "Exception.h"



ShaderProgram::ShaderProgram() {
	/*
	std::string vertShader;
	std::string fragShader;

	std::ifstream file("../shaders/simple.vert");

	if (!file.is_open()) {
		throw Exception("couldn't open simple vertex shader");
	}
	else {
		while (!file.eof()) {
			std::string line;
			std::getline(file, line);
			vertShader += line + "\n";
		}
	}
	file.close();

	file.open("../shaders/simple.frag");

	if (!file.is_open()) {
		throw Exception("couldn't open simple fragment shader");
	}
	else {
		while (!file.eof()) {
			std::string line;
			std::getline(file, line);
			fragShader += line + "\n";
		}
	}
	file.close();

	const char *vertex = vertShader.c_str();
	const char *fragment = fragShader.c_str();

	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertex, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		printShaderInfoLog(id);
		throw Exception("vertex shader couldn't compile");
	}

	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragment, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		printShaderInfoLog(id);
		throw Exception("fragment shader couldn't compile");
	}

	id = glCreateProgram();
	glAttachShader(id, vertexShaderId);
	glAttachShader(id, fragmentShaderId);
	// Ensure the VAO "position" attribute stream gets set as the first position
	// during the link.
	glBindAttribLocation(id, 0, "in_Position");
	glBindAttribLocation(id, 1, "in_TexCoord");

	if (glGetError() != GL_NO_ERROR) {
		throw Exception("shader machine broke");
	}
	// Perform the link and check for failure
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		throw Exception("shader coudln't link");
	}
	// Detach and destroy the shader objects. These are no longer needed
	// because we now have a complete shader program.
	glDetachShader(id, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(id, fragmentShaderId);
	glDeleteShader(fragmentShaderId);
	*/
}

ShaderProgram::ShaderProgram(std::string vert, std::string frag)
{
	std::string vertShader;
	std::string fragShader;

	std::ifstream file(vert); //load the vertex shader

	if (!file.is_open()) {
		throw Exception("couldn't open vertex shader at path");
	}
	else {
		while (!file.eof()) { //go through every line of the vertex shader and write it to a string
			std::string line;
			std::getline(file, line);
			vertShader += line + "\n";
		}
	}
	file.close();

	file.open(frag); //load the fragment shader

	if (!file.is_open()) {
		throw Exception("couldn't open fragment shader at path");
	}
	else {
		while (!file.eof()) {
			std::string line;
			std::getline(file, line);
			fragShader += line + "\n";
		}
	}
	file.close();

	const char *vertex = vertShader.c_str();
	const char *fragment = fragShader.c_str();

	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER); //assign vertex shader id
	glShaderSource(vertexShaderId, 1, &vertex, NULL); //create the shader from the source
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		printShaderInfoLog(vertexShaderId);
		throw Exception("check error log");
	}

	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);//assign fragment shader id
	glShaderSource(fragmentShaderId, 1, &fragment, NULL);//create the shader from the source
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		printShaderInfoLog(fragmentShaderId);
		throw Exception("check error log");
	}

	id = glCreateProgram(); //assign program id
	//attach shaders to the program
	glAttachShader(id, vertexShaderId);
	glAttachShader(id, fragmentShaderId);
	// Ensure the VAO "position" attribute stream gets set as the first position
	// during the link.
	glBindAttribLocation(id, 0, "in_Position");
	glBindAttribLocation(id, 1, "in_Color");
	glBindAttribLocation(id, 2, "in_TexCoord");
	glBindAttribLocation(id, 3, "in_Normal");

	if (glGetError() != GL_NO_ERROR) {
		printProgramInfoLog(id);
		throw Exception("check error log");
	}
	// Perform the link and check for failure
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		printProgramInfoLog(id);
		throw Exception("check error log");
	}
	// Detach and destroy the shader objects. These are no longer needed
	// because we now have a complete shader program.
	glDetachShader(id, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(id, fragmentShaderId);
	glDeleteShader(fragmentShaderId);
}

void ShaderProgram::load(std::string path)
{
	std::string vertShader;
	std::string fragShader;

	std::ifstream file(path + ".vert"); //load the vertex shader

	if (!file.is_open()) {
		throw Exception("couldn't open vertex shader at path");
	}
	else {
		while (!file.eof()) { //go through every line of the vertex sjader and write it to a string
			std::string line;
			std::getline(file, line);
			vertShader += line + "\n";
		}
	}
	file.close();

	file.open(path + ".frag"); //load the fragment shader

	if (!file.is_open()) {
		throw Exception("couldn't open fragment shader at path");
	}
	else {
		while (!file.eof()) {
			std::string line;
			std::getline(file, line);
			fragShader += line + "\n";
		}
	}
	file.close();

	const char *vertex = vertShader.c_str();
	const char *fragment = fragShader.c_str();

	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER); //assign vertex shader id
	glShaderSource(vertexShaderId, 1, &vertex, NULL); //create the shader from the source
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		printShaderInfoLog(vertexShaderId);
		throw Exception("check error log");
	}

	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);//assign fragment shader id
	glShaderSource(fragmentShaderId, 1, &fragment, NULL);//create the shader from the source
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		printShaderInfoLog(fragmentShaderId);
		throw Exception("check error log");
	}

	id = glCreateProgram(); //assign program id
	//attach shaders to the program
	glAttachShader(id, vertexShaderId);
	glAttachShader(id, fragmentShaderId);
	// Ensure the VAO "position" attribute stream gets set as the first position
	// during the link.
	glBindAttribLocation(id, 0, "in_Position");
	glBindAttribLocation(id, 1, "in_Color");
	glBindAttribLocation(id, 2, "in_TexCoord");
	glBindAttribLocation(id, 3, "in_Normal");

	if (glGetError() != GL_NO_ERROR) {
		printProgramInfoLog(id);
		throw Exception("check error log");
	}
	// Perform the link and check for failure
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		printProgramInfoLog(id);
		throw Exception("check error log");
	}
	// Detach and destroy the shader objects. These are no longer needed
	// because we now have a complete shader program.
	glDetachShader(id, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(id, fragmentShaderId);
	glDeleteShader(fragmentShaderId);
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::Draw(std::shared_ptr<Mesh> vertexArray)
{
	glUseProgram(id); //bind the shader
	glBindVertexArray(vertexArray->GetId()); //bind the mesh
	
	for (size_t i = 0; i < samplers.size(); i++) //go through list of samplers
	{
		glActiveTexture(GL_TEXTURE0 + i); //set the active texture equal to the position in the list of samplers

		if (samplers.at(i).texture) //if a texture exists at this position, bind it 
		{
			glBindTexture(samplers.at(i).type, samplers.at(i).texture->GetId());
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, 0); //otherwise unbind the current texture
		}
	}

	glDrawArrays(GL_TRIANGLES, 0, vertexArray->GetVertexCount()); //draw the mesh

	for (size_t i = 0; i < samplers.size(); i++) //go through list of samplers and unbind all of the textures
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	glBindVertexArray(0); //unbind the mesh and program
	glUseProgram(0);
}

void ShaderProgram::SetUniform(std::string uniform, glm::vec4 value)
{
	GLint uniformId = glGetUniformLocation(id, uniform.c_str());
	if (uniformId == -1)
	{
		throw Exception("coudln't set uniform: " + uniform);
	}

	glUseProgram(id);
	glUniform4f(uniformId, value.x, value.y, value.z, value.w);
	glUseProgram(0);

}
void ShaderProgram::SetUniform(std::string uniform, glm::vec3 value) {
	GLint uniformId = glGetUniformLocation(id, uniform.c_str());
	if (uniformId == -1)
	{
		throw Exception("coudln't set uniform: " + uniform);
	}

	glUseProgram(id);
	glUniform3f(uniformId, value.x, value.y, value.z);
	glUseProgram(0);
}

void ShaderProgram::SetUniform(std::string uniform, glm::mat4 value)
{
	GLint uniformId = glGetUniformLocation(id, uniform.c_str());
	if (uniformId == -1)
	{
		throw Exception("coudln't set uniform: " + uniform);
	}

	glUseProgram(id);
	glUniformMatrix4fv(uniformId, 1, GL_FALSE, &value[0][0]);
	glUseProgram(0);

}

void ShaderProgram::SetUniform(std::string uniform, std::shared_ptr<Texture> texture)
{
	GLint uniformId = glGetUniformLocation(id, uniform.c_str());

	if (uniformId == -1)
	{
		throw Exception("coudln't get uniform: " + uniform);
	}

	for (size_t i = 0; i < samplers.size(); i++) //go through the list of samplers and if the texture already exists bind that one
	{
		if (samplers.at(i).id == uniformId)
		{
			samplers.at(i).texture = texture;

			glUseProgram(id);
			glUniform1i(uniformId, i);
			glUseProgram(0);
			return;
		}
	}
	//if not create a new sampler of the texture, add it to the list and bind that
	Sampler s;
	s.id = uniformId;
	s.type = GL_TEXTURE_2D;
	s.texture = texture;
	samplers.push_back(s);

	glUseProgram(id);
	glUniform1i(uniformId, samplers.size() - 1);
	glUseProgram(0);
}

void ShaderProgram::SetUniform(std::string uniform, std::shared_ptr<DepthCubemap> texture)
{
	GLint uniformId = glGetUniformLocation(id, uniform.c_str());

	if (uniformId == -1)
	{
		throw Exception("coudln't get uniform: " + uniform);
	}

	for (size_t i = 0; i < samplers.size(); i++)
	{
		if (samplers.at(i).id == uniformId)
		{
			samplers.at(i).texture = texture;

			glUseProgram(id);
			glUniform1i(uniformId, i);
			glUseProgram(0);
			return;
		}
	}

	Sampler s;
	s.id = uniformId;
	s.type = GL_TEXTURE_CUBE_MAP;
	s.texture = texture;
	samplers.push_back(s);

	glUseProgram(id);
	glUniform1i(uniformId, samplers.size() - 1);
	glUseProgram(0);
}

void ShaderProgram::SetUniform(std::string uniform, float value)
{
	GLint uniformId = glGetUniformLocation(id, uniform.c_str());
	if (uniformId == -1)
	{
		throw Exception("coudln't set uniform: " + uniform);
	}

	glUseProgram(id);
	glUniform1f(uniformId, value);
	glUseProgram(0);
}

void ShaderProgram::SetUniform(std::string uniform, int value)
{
	GLint uniformId = glGetUniformLocation(id, uniform.c_str());
	if (uniformId == -1)
	{
		throw Exception("coudln't set uniform: " + uniform);
	}

	glUseProgram(id);
	glUniform1i(uniformId, value);
	glUseProgram(0);
}

GLuint ShaderProgram::GetId()
{
	return id;
}


void ShaderProgram::printShaderInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
		free(infoLog);
	}
}

void ShaderProgram::printProgramInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
		free(infoLog);
	}
}
