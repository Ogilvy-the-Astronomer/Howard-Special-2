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

	//shader->SetUniform("in_Emissive", glm::vec3(0.0f, 0.0f, 0.0f));
	//shader->SetUniform("in_Ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	//shader->SetUniform("in_LightPos", glm::vec3(0.0f, 5.0f, 0.5f));

	shader->SetUniform("lights[0].emissive", glm::vec3(0.0f, 0.0f, 0.0f));
	shader->SetUniform("lights[0].ambient", glm::vec3(0.2f, 0.7f, 0.2f));
	shader->SetUniform("lights[0].pos", glm::vec3(0.0f, 1.0f, 0.5f));
	shader->SetUniform("lights[0].constant", 1.0f);
	shader->SetUniform("lights[0].linear", 0.09f);
	shader->SetUniform("lights[0].quadratic", 0.032f);

	shader->SetUniform("lights[1].emissive", glm::vec3(0.0f, 0.0f, 0.0f));
	shader->SetUniform("lights[1].ambient", glm::vec3(0.2f, 0.2f, 0.7f));
	shader->SetUniform("lights[1].pos", glm::vec3(0.0f, 1.0f, -7.5f));
	shader->SetUniform("lights[1].constant", 1.0f);
	shader->SetUniform("lights[1].linear", 0.09f);
	shader->SetUniform("lights[1].quadratic", 0.032f);

	//shader->SetUniform("in_ViewPos", cam.lock()->GetComponent<Transform>()->position);

	shader->Draw(shape);
}

void Renderer::SetMesh(std::shared_ptr<Mesh> mesh){
	shape = mesh;
}

void Renderer::SetTexture(std::shared_ptr<Texture> image){
	texture = image;
}
