#include "Light.h"
#include "Transform.h"
#include "GameObject.h"

/**
 * light source component
 */
PointLight::PointLight(){
	emissive = ambient = specular = diffuse = glm::vec3(1.0f);
	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;
}

void PointLight::OnUpdate(float _deltaT){
	//view = glm::lookAt(GetGameObject()->GetComponent<Transform>()->position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void PointLight::SetAll(glm::vec3 _colour) {
	emissive = ambient = specular = diffuse = _colour;
}

DirectionalLight::DirectionalLight(){
	emissive = ambient = specular = diffuse = glm::vec3(0.1f);
}

void DirectionalLight::SetAll(glm::vec3 _colour) {
	emissive = ambient = specular = diffuse = _colour;
}
