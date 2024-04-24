#include "Component.h"
#include <glm/vec3.hpp>

/**
 * a very very basic physic component that does velocity and gravity
 */
struct Rigidbody : public Component {
	constexpr static glm::vec3 WorldGravity = glm::vec3(0.0f, -0.000981f, 0.0f);

public:
	Rigidbody();
	void OnUpdate(float _deltaT);
	bool IsGrounded();
	glm::vec3 velocity; ///< value added to position each frame
	glm::vec3 torque; ///< value added to rotation each frame
	float friction; ///< how much velocity is reduced by each frame
	bool doGravity; ///< whether or not this object should be effected by gravity

private:
	friend struct MeshCollider;
	friend struct BoxCollider;
	bool atRest;
	float gravity; ///< gravity velocity
};