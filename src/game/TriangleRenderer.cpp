#include "TriangleRenderer.h"
#include "SDL2/SDL.h"
#include <glm/ext.hpp>

TriangleRenderer::TriangleRenderer() {
	
	positions = std::make_shared<VertexBuffer>();
	positions->add(glm::vec3(-0.5f, 0.5f, 0.0f));
	positions->add(glm::vec3(-0.5f, -0.5f, 0.0f));
	positions->add(glm::vec3(0.5f, -0.5f, 0.0f));

	colors = std::make_shared<VertexBuffer>();
	colors->add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	colors->add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	colors->add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	shape = std::make_shared<VertexArray>();
	shape->SetBuffer("in_Position", positions);
	shape->SetBuffer("in_Color", colors);

	angle = 0;
}

void TriangleRenderer::OnUpdate(){
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	shader->SetUniform("in_Projection", glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f));

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0, 0, -2.5f));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));

	shader->SetUniform("in_Model", model);
	shader->Draw(shape);

	angle += 0.1f;
	SDL_GL_SwapWindow(window);
}
