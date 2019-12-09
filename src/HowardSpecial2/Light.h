#pragma once
#include <glm/glm.hpp>
#include "Component.h"
//TODO: make pointlight derive from dir light
struct PointLight : public Component {
	PointLight();
	void OnUpdate();

	glm::vec3 emissive;
	glm::vec3 ambient;
	glm::vec3 specular;
	glm::vec3 diffuse;

	float constant;
	float linear;
	float quadratic;
	
	glm::mat4 view;
};

struct DirectionalLight : public Component {
	DirectionalLight();

	glm::vec3 emissive;
	glm::vec3 ambient;
	glm::vec3 specular;
	glm::vec3 diffuse;
};

