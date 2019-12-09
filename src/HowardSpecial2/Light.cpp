#include "Light.h"
#include "Transform.h"
#include "GameObject.h"

PointLight::PointLight(){
	emissive, ambient, specular, diffuse = glm::vec3(0.0f);
	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;
}

void PointLight::OnUpdate(){
	//view = glm::lookAt(GetGameObject()->GetComponent<Transform>()->position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

DirectionalLight::DirectionalLight(){
	emissive, ambient, specular, diffuse = glm::vec3(0.0f);
}
