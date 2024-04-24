#include <string>
#include "Renderer.h"
#include "SDL2/SDL.h"
#include <glm/ext.hpp>
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"
#include "Core.h"
#include "Light.h"
#include "Material.h"
#include "ShaderProgram.h"
Renderer::Renderer() {
	material = std::make_shared<Material>();
}

Renderer::Renderer(std::string _shape, std::string _texture) {
	shape = std::make_shared<Mesh>(_shape);
	texture = std::make_shared<Texture>(_texture);
}

void Renderer::OnDisplay() {

}

void Renderer::OnUpdate(float _deltaT){
	cam = GetCore()->mainCamera; //get the main camera
	//set uniforms for the projection, model, and view matrices as well as the texture
	material->shader->SetUniform("in_Projection", cam.lock()->GetComponent<Camera>()->GetProjection());
	material->shader->SetUniform("in_Model", GetGameObject()->GetTransform()->GetModel());
	material->shader->SetUniform("in_Texture", texture);
	material->shader->SetUniform("in_View", cam.lock()->GetComponent<Camera>()->GetView());
	//get lists of all point and direction lights
	std::vector<std::shared_ptr<PointLight>> lights = GetCore()->lights;
	std::vector<std::shared_ptr<DirectionalLight>> dLights = GetCore()->GetComponents<DirectionalLight>();

	for (int i = 0; i < (int)dLights.size(); i++) { //go through list of every direction light and set corresponding uniforms in the shader
		material->shader->SetUniform("dlights[" + std::to_string(i) + "].emissive", dLights[i]->emissive);
		material->shader->SetUniform("dlights[" + std::to_string(i) + "].ambient", dLights[i]->ambient);
		material->shader->SetUniform("dlights[" + std::to_string(i) + "].diffuse", dLights[i]->diffuse);
		material->shader->SetUniform("dlights[" + std::to_string(i) + "].specular", dLights[i]->specular);
		material->shader->SetUniform("dlights[" + std::to_string(i) + "].dir", dLights[i]->GetGameObject()->GetTransform()->rotation);
	}
	for (int i = 0; i < (int)lights.size(); i++) {
		material->shader->SetUniform("lights[" + std::to_string(i) + "].emissive", lights[i]->emissive); //go through list of every point light and set corresponding uniforms in the shader
		material->shader->SetUniform("lights[" + std::to_string(i) + "].ambient", lights[i]->ambient);
		material->shader->SetUniform("lights[" + std::to_string(i) + "].diffuse", lights[i]->diffuse);
		material->shader->SetUniform("lights[" + std::to_string(i) + "].specular", lights[i]->specular);
		material->shader->SetUniform("lights[" + std::to_string(i) + "].pos", lights[i]->GetGameObject()->GetTransform()->position);
		material->shader->SetUniform("lights[" + std::to_string(i) + "].constant", lights[i]->constant);
		material->shader->SetUniform("lights[" + std::to_string(i) + "].linear", lights[i]->linear);
		material->shader->SetUniform("lights[" + std::to_string(i) + "].quadratic", lights[i]->quadratic);

		material->shader->SetUniform("in_ShadowMaps[" + std::to_string(i) + "]", depthCubeTextures[i]);
	}
	material->shader->SetUniform("in_FarPlane", 200.0f);//set the near and far plane for linearizing the depth values of the shadowmap

	//set material properties
	material->shader->SetUniform("material.ambient", material->ambient);
	material->shader->SetUniform("material.specular", material->specular);
	material->shader->SetUniform("material.diffuse", material->diffuse);
	material->shader->SetUniform("material.shininess", material->shininess);

	//shader->SetUniform("in_NearPlane", 1.0f);
	material->shader->Draw(shape); //draw the object to screen
}

void Renderer::SetMesh(std::shared_ptr<Mesh> _mesh){
	shape = _mesh;
}

void Renderer::SetTexture(std::shared_ptr<Texture> _texture){
	texture = _texture;
}

void Renderer::SetShader(std::shared_ptr<ShaderProgram> _shader) {
	material->shader = _shader;
}
