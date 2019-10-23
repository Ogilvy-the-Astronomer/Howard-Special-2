#include <GL/glew.h>

struct ShaderProgram {
	GLuint vertexShaderId;
	GLuint fragmentShaderId;
	GLuint programId;
	const GLchar *vertexShaderSrc =
		"attribute vec3 in_Position; " \
		" " \
		"void main() " \
		"{ " \
		" gl_Position = vec4(in_Position, 1.0); " \
		"} ";

	const GLchar *fragmentShaderSrc =
		"void main() " \
		"{ " \
		" gl_FragColor = vec4(0, 0, 1, 1); " \
		"} ";
	ShaderProgram();
};