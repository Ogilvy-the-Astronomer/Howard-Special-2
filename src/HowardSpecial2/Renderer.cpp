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

}

void Renderer::OnUpdate(){
	cam = GetCore()->mainCamera;
	shader->SetUniform("in_Projection", cam.lock()->GetComponent<Camera>()->GetProjection());
	shader->SetUniform("in_Model", GetGameObject()->GetComponent<Transform>()->GetModel());
	shader->SetUniform("in_Texture", texture);
	shader->SetUniform("in_View", cam.lock()->GetComponent<Camera>()->GetView());

	shader->SetUniform("in_Emissive", glm::vec3(0.0f, 0.0f, 0.0f));
	shader->SetUniform("in_Ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader->SetUniform("in_LightPos", glm::vec3(0.0f, 5.0f, 0.5f));
	//shader->SetUniform("in_ViewPos", cam.lock()->GetComponent<Transform>()->position);

	shader->Draw(shape);
}

void Renderer::SetMesh(std::shared_ptr<Mesh> mesh){
	shape = mesh;
}

void Renderer::SetTexture(std::shared_ptr<Texture> image){
	texture = image;
}
