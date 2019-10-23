#include "TriangleRenderer.h"
#include "SDL2/SDL.h"

TriangleRenderer::TriangleRenderer() {
	positionsVboId = 0;
	// Create a new VBO on the GPU and bind it
	glGenBuffers(1, &positionsVboId);
	if (!positionsVboId)
	{
		throw std::exception();
	}
	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);
	// Upload a copy of the data from memory into the new VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	// Reset the state
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	vaoId = 0;
	// Create a new VAO on the GPU and bind it
	glGenVertexArrays(1, &vaoId);
	if (!vaoId)
	{
		throw std::exception();
	}
	glBindVertexArray(vaoId);
	// Bind the position VBO, assign it to position 0 on the bound VAO
	// and flag it to be used
	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		3 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);
	// Reset the state
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



}

void TriangleRenderer::OnUpdate(){
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shader.programId);
	glBindVertexArray(vaoId);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	glUseProgram(0);

	SDL_GL_SwapWindow(window);
}
