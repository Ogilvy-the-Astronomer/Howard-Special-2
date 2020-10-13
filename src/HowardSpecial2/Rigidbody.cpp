#include "Rigidbody.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoxCollider.h"

Rigidbody::Rigidbody(){
	velocity, torque = glm::vec3(0.0f);
	friction = 0;
	doGravity = true;
	gravity = 0;
}

void Rigidbody::OnUpdate(){
	if (doGravity) { //move the object down if it's not resting
		gravity -= 0.005f;
		velocity.y += gravity;
	}
	else {
		gravity = 0; //if the object is resting get rid of negative velocity and reset the gravity
		if (velocity.y < 0) {
			velocity.y = 0;
		}
	}
	if (!GetGameObject()->GetComponent<BoxCollider>()->isColliding(GetGameObject()->GetTransform()->position - glm::vec3(0.0f, 1.0f, 0.0f))) { //if the object will collide when moved down, enable gravity
		doGravity = true; 
	}
	else {
		doGravity = false;
	}
	GetGameObject()->GetTransform()->position += velocity; //adjust position by velocti
	GetGameObject()->GetTransform()->rotation += torque; //adjust rotation by torque
	velocity.x *= 1.0f - friction; //reduce lateral velocity by friction
	velocity.z *= 1.0f - friction;
 
}
