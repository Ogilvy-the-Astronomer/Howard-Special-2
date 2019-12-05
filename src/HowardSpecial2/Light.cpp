#include "Light.h"

PointLight::PointLight(){
	emissive, ambient, specular, diffuse = glm::vec3(0.0f);
	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;
}

DirectionalLight::DirectionalLight(){
	emissive, ambient, specular, diffuse = glm::vec3(0.0f);
}
