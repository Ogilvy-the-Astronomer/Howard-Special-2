#pragma once
#include <glm/vec3.hpp>
#include "Component.h"
//TODO: make pointlight derive from dir light
struct PointLight : public Component {
	PointLight();

	glm::vec3 emissive;
	glm::vec3 ambient;
	glm::vec3 specular;
	glm::vec3 diffuse;

	float constant;
	float linear;
	float quadratic;
};

struct DirectionalLight : public Component {
	DirectionalLight();

	glm::vec3 emissive;
	glm::vec3 ambient;
	glm::vec3 specular;
	glm::vec3 diffuse;
};

