#include <glm/ext.hpp>
#include <string>
#include "Mesh.h"
#include "VertexBuffer.h"
#include "Component.h"
#include "Texture.h"
/**
 * component storing spacial stuff
 */
struct Transform : public Component {
	Transform();
	glm::vec3 position; ///< position in world space
	glm::vec3 rotation; ///< rotation in world space
	glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f); ///< scale
	glm::vec3 forward; ///< forward vector
	glm::vec3 right; ///< right vector

	void OnUpdate();
	glm::mat4 GetModel(); ///< create model matrix from position, rotation, and scale
};