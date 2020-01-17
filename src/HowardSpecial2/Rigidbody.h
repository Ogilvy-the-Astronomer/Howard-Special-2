#include "Component.h"
#include <glm/vec3.hpp>

/**
 * a very very basic physic component that does velocity and gravity
 */
struct Rigidbody : public Component {
	Rigidbody();
	void OnUpdate();
	glm::vec3 velocity; ///< value added to position each frame
	glm::vec3 torque; ///< value added to rotation each frame
	float friction; ///< how much velocity is reduced by each frame

private:
	friend struct MeshCollider;
	friend struct BoxCollider;
	bool doGravity; ///< whether or not this object should be effected by gravity
	float gravity; ///< gravity velocity
};