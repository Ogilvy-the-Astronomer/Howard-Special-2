#include <glm/ext.hpp>
#include <string>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Component.h"
#include "Texture.h"

struct Transform : public Component {
	Transform();
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 forward;
	glm::vec3 right;

	void OnUpdate();
	glm::mat4 GetModel();
};