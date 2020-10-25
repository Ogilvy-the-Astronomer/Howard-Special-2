#pragma once
#include <glm/glm.hpp>
#include "Component.h"
/**
 * a point light which shines light in all directions
 */
struct PointLight : public Component {
	PointLight(); ///< default constructor
	void OnUpdate();

	void SetAll(glm::vec3 _colour);

	glm::vec3 emissive; ///< creates darkness behind objects
	glm::vec3 ambient; ///< a flat value added around the light
	glm::vec3 specular; ///< the shine of an object because of the light
	glm::vec3 diffuse; ///< the colour of the light

	float constant; ///< constant attenuation value
	float linear; ///< linear attenuation value
	float quadratic; ///< quadratic attenuation value
	
	glm::mat4 view; ///< point light view matrix
};
/**
 * a directional light which shines light in one direction
 */
struct DirectionalLight : public Component {
	DirectionalLight();

	void SetAll(glm::vec3 _colour);

	glm::vec3 emissive; ///< creates darkness behind objects
	glm::vec3 ambient; ///< a flat value added around the light
	glm::vec3 specular; ///< the shine of an object because of the light
	glm::vec3 diffuse; ///< the colour of the light
};

