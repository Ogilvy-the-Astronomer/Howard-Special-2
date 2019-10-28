#include "TriangleRenderer.h"
#include "SDL2/SDL.h"
#include <glm/ext.hpp>

TriangleRenderer::TriangleRenderer() {

	tex = std::make_shared<Texture>("../src/game/textures/dice.png");

	texCoords = std::make_shared<VertexBuffer>();
	texCoords->add(glm::vec2(0.5f, 0.0f));
	texCoords->add(glm::vec2(0.0f, 1.0f));
	texCoords->add(glm::vec2(1.0f, 1.0f));
	
	positions = std::make_shared<VertexBuffer>();
	positions->add(glm::vec3(0.0f, 0.5f, 0.0f));
	positions->add(glm::vec3(-0.5f, -0.5f, 0.0f));
	positions->add(glm::vec3(0.5f, -0.5f, 0.0f));

	colors = std::make_shared<VertexBuffer>();
	colors->add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	colors->add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	colors->add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	shape = std::make_shared<VertexArray>();
	shape->SetBuffer("in_Position", positions);
	//shape->SetBuffer("in_Color", colors);
	shape->SetBuffer("in_TexCoord", texCoords);

	angle = 0;
}

void TriangleRenderer::OnUpdate(){
	shader->SetUniform("in_Projection", glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f));

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0, 0, -2.5f));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));

	shader->SetUniform("in_Model", model);
	shader->SetUniform("in_Texture", tex);

	shader->Draw(shape);

	angle += 1.0f;

}
