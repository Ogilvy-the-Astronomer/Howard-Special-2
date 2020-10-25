#include "Material.h"
#include "ShaderProgram.h"

Material::Material(){
	shader = std::make_shared<ShaderProgram>();
	ambient = diffuse = specular = glm::vec3(1.0f);
	shininess = 64.0f;
}
