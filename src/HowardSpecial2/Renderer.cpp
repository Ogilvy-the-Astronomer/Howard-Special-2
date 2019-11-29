#include "Renderer.h"
#include "SDL2/SDL.h"
#include <glm/ext.hpp>
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"
#include "Core.h"

Renderer::Renderer() {

}

Renderer::Renderer(std::string _shape, std::string _texture)
{
	shape = std::make_shared<Mesh>(_shape);
	texture = std::make_shared<Texture>(_texture);
}

void Renderer::OnDisplay() {
	shader->SetUniform("in_Projection", glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f)); //TODO: Add camera projection
	shader->SetUniform("in_Model", GetGameObject()->GetComponent<Transform>()->GetModel());
	shader->SetUniform("in_Texture", texture);
	shader->Draw(shape);
}

void Renderer::OnUpdate(){
	cam = GetCore()->mainCamera;
	shader->SetUniform("in_Projection", cam.lock()->GetComponent<Camera>()->GetProjection()); //TODO: Add camera projection
	shader->SetUniform("in_Model", GetGameObject()->GetComponent<Transform>()->GetModel());
	shader->SetUniform("in_Texture", texture);
	shader->SetUniform("in_View", cam.lock()->GetComponent<Camera>()->GetView());
	shader->Draw(shape);

	//SDL_GL_SwapWindow(window); //REMOVE
}

void Renderer::SetMesh(std::shared_ptr<Mesh> mesh){
	shape = mesh;
}

void Renderer::SetTexture(std::shared_ptr<Texture> image){
	texture = image;
}
