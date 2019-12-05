#include <string>
#include "Renderer.h"
#include "SDL2/SDL.h"
#include <glm/ext.hpp>
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"
#include "Core.h"
#include "Light.h"
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
	std::vector<std::shared_ptr<PointLight>> lights = GetCore()->lights;
	std::vector<std::shared_ptr<DirectionalLight>> dLights = GetCore()->dLights;
	/*
	shader->SetUniform("dlights[0].emissive", glm::vec3(0.0f, 0.0f, 0.0f));
	shader->SetUniform("dlights[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader->SetUniform("dlights[0].diffuse", glm::vec3(0.3f, 0.3f, 0.3f));
	shader->SetUniform("dlights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->SetUniform("dlights[0].dir", glm::vec3(glm::radians(-45.0f),glm::radians(-40.0f),0.0f));

	shader->SetUniform("lights[0].emissive", glm::vec3(0.0f, 0.0f, 0.0f));
	shader->SetUniform("lights[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader->SetUniform("lights[0].diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->SetUniform("lights[0].specular", glm::vec3(0.2f, 0.2f, 0.2f));
	shader->SetUniform("lights[0].pos", glm::vec3(0.0f, 5.0f, -5.5f));
	shader->SetUniform("lights[0].constant", 1.0f);
	shader->SetUniform("lights[0].linear", 0.09f);
	shader->SetUniform("lights[0].quadratic", 0.032f);
	*/

	for (int i = 0; i < dLights.size(); i++) {
		shader->SetUniform("dlights[" + std::to_string(i) + "].emissive", dLights[i]->emissive);
		shader->SetUniform("dlights[" + std::to_string(i) + "].ambient", dLights[i]->ambient);
		shader->SetUniform("dlights[" + std::to_string(i) + "].diffuse", dLights[i]->diffuse);
		shader->SetUniform("dlights[" + std::to_string(i) + "].specular", dLights[i]->specular);
		shader->SetUniform("dlights[" + std::to_string(i) + "].dir", dLights[i]->GetGameObject()->GetComponent<Transform>()->rotation);
	}

	for (int i = 0; i < lights.size(); i++) {
		shader->SetUniform("lights[" + std::to_string(i) + "].emissive", lights[i]->emissive);
		shader->SetUniform("lights[" + std::to_string(i) + "].ambient", lights[i]->ambient);
		shader->SetUniform("lights[" + std::to_string(i) + "].diffuse", lights[i]->diffuse);
		shader->SetUniform("lights[" + std::to_string(i) + "].specular", lights[i]->specular);
		shader->SetUniform("lights[" + std::to_string(i) + "].pos", lights[i]->GetGameObject()->GetComponent<Transform>()->position);
		shader->SetUniform("lights[" + std::to_string(i) + "].constant", lights[i]->constant);
		shader->SetUniform("lights[" + std::to_string(i) + "].linear", lights[i]->linear);
		shader->SetUniform("lights[" + std::to_string(i) + "].quadratic", lights[i]->quadratic);
	}

	glm::mat4 lightProjection = glm::ortho(100.0f, -100.0f, 100.0f, -100.0f, 1.0f, 500.0f);
	glm::mat4 lightView = glm::lookAt(lights[0]->GetGameObject()->GetComponent<Transform>()->position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 lightSpaceMatrix = lightProjection * lightView; //light mvp matrix

	shader->SetUniform("in_LightSpaceMatrix", lightSpaceMatrix);
	shader->SetUniform("in_ShadowMap", depthTexture);
	/*
	shader->SetUniform("lights[1].emissive", glm::vec3(0.0f, 0.0f, 0.0f));
	shader->SetUniform("lights[1].ambient", glm::vec3(0.2f, 0.2f, 0.7f));
	shader->SetUniform("lights[1].pos", glm::vec3(0.0f, 1.0f, -7.5f));
	shader->SetUniform("lights[1].constant", 1.0f);
	shader->SetUniform("lights[1].linear", 0.09f);
	shader->SetUniform("lights[1].quadratic", 0.032f);
	*/
	//shader->SetUniform("in_ViewPos", cam.lock()->GetComponent<Transform>()->position);

	shader->Draw(shape);
}

void Renderer::SetMesh(std::shared_ptr<Mesh> mesh){
	shape = mesh;
}

void Renderer::SetTexture(std::shared_ptr<Texture> image){
	texture = image;
}
