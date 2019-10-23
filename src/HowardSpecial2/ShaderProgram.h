#include <GL/glew.h>

struct ShaderProgram {
	GLuint vertexShaderId;
	GLuint fragmentShaderId;
	GLuint programId;
	const GLchar *vertexShaderSrc =
		"attribute vec3 in_Position;" \
		"attribute vec4 in_Color;" \
		"" \
		"varying vec4 ex_Color;" \
		"" \
		"void main()" \
		"{" \
		" gl_Position = vec4(in_Position, 1.0);" \
		" ex_Color = in_Color;" \
		"}" \
		"";

	const GLchar *fragmentShaderSrc =
		"varying vec4 ex_Color;" \
		"void main()" \
		"{" \
		" gl_FragColor = ex_Color;" \
		"}" \
		"";
	ShaderProgram();
	void printShaderInfoLog(GLuint obj);
	void printProgramInfoLog(GLuint obj);
};