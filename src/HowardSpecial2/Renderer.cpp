#include "Renderer.h"
#include "SDL2/SDL.h"
#include <glm/ext.hpp>
#include "GameObject.h"
#include "Transform.h"

Renderer::Renderer() {

}

Renderer::Renderer(std::string _shape, std::string _texture)
{
	shape = std::make_shared<VertexArray>(_shape);
	texture = std::make_shared<Texture>(_texture);
}

void Renderer::OnDisplay() {
	shader->SetUniform("in_Projection", glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f)); //TODO: Add camera projection
	shader->SetUniform("in_Model", GetGameObject()->GetComponent<Transform>()->GetModel());
	shader->SetUniform("in_Texture", texture);
	shader->Draw(shape);
}