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

Renderer::Renderer(std::string _shape, std::string _texture) {
	shape = std::make_shared<Mesh>(_shape);
	texture = std::make_shared<Texture>(_texture);
}

void Renderer::OnDisplay() {

}

void Renderer::OnUpdate(){
	cam = GetCore()->mainCamera; //get the main camera
	//set uniforms for the projection, model, and view matrices as well as the texture
	shader->SetUniform("in_Projection", cam.lock()->GetComponent<Camera>()->GetProjection());
	shader->SetUniform("in_Model", GetGameObject()->GetTransform()->GetModel());
	shader->SetUniform("in_Texture", texture);
	shader->SetUniform("in_View", cam.lock()->GetComponent<Camera>()->GetView());
	//get lists of all point and direction lights
	std::vector<std::shared_ptr<PointLight>> lights = GetCore()->lights;
	std::vector<std::shared_ptr<DirectionalLight>> dLights = GetCore()->GetComponents<DirectionalLight>();

	for (int i = 0; i < (int)dLights.size(); i++) { //go through list of every direction light and set corresponding uniforms in the shader
		shader->SetUniform("dlights[" + std::to_string(i) + "].emissive", dLights[i]->emissive);
		shader->SetUniform("dlights[" + std::to_string(i) + "].ambient", dLights[i]->ambient);
		shader->SetUniform("dlights[" + std::to_string(i) + "].diffuse", dLights[i]->diffuse);
		shader->SetUniform("dlights[" + std::to_string(i) + "].specular", dLights[i]->specular);
		shader->SetUniform("dlights[" + std::to_string(i) + "].dir", dLights[i]->GetGameObject()->GetTransform()->rotation);
	}
	for (int i = 0; i < (int)lights.size(); i++) {
		shader->SetUniform("lights[" + std::to_string(i) + "].emissive", lights[i]->emissive); //go through list of every point light and set corresponding uniforms in the shader
		shader->SetUniform("lights[" + std::to_string(i) + "].ambient", lights[i]->ambient);
		shader->SetUniform("lights[" + std::to_string(i) + "].diffuse", lights[i]->diffuse);
		shader->SetUniform("lights[" + std::to_string(i) + "].specular", lights[i]->specular);
		shader->SetUniform("lights[" + std::to_string(i) + "].pos", lights[i]->GetGameObject()->GetTransform()->position);
		shader->SetUniform("lights[" + std::to_string(i) + "].constant", lights[i]->constant);
		shader->SetUniform("lights[" + std::to_string(i) + "].linear", lights[i]->linear);
		shader->SetUniform("lights[" + std::to_string(i) + "].quadratic", lights[i]->quadratic);

		shader->SetUniform("in_ShadowMaps[" + std::to_string(i) + "]", depthCubeTextures[i]);
	}
	shader->SetUniform("in_FarPlane", 50.0f);//set the near and far plane for linearizing the depth values of the shadowmap
	//shader->SetUniform("in_NearPlane", 1.0f);
	shader->Draw(shape); //draw the object to screen
}

void Renderer::SetMesh(std::shared_ptr<Mesh> _mesh){
	shape = _mesh;
}

void Renderer::SetTexture(std::shared_ptr<Texture> _texture){
	texture = _texture;
}
