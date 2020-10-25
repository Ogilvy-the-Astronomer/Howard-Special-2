#include <memory>
#include <glm/glm.hpp>
#include <string>


struct ShaderProgram;

struct Material {
	friend struct Renderer;
	Material();
	glm::vec3 ambient;
	glm::vec3 specular;
	glm::vec3 diffuse;
	float shininess;

private:
	std::shared_ptr<ShaderProgram> shader;
};