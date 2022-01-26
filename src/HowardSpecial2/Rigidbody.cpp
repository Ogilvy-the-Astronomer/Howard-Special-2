#include "Rigidbody.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "Core.h"

Rigidbody::Rigidbody(){
	velocity = torque = glm::vec3(0.0f);
	friction = 0;
	doGravity = true;
	gravity = 0;
}

void Rigidbody::OnUpdate(){
	if (doGravity && !atRest) { //move the object down if it's not resting
		gravity -= 0.0005f * GetCore()->deltaT;
		velocity.y += gravity;
	}
	else {
		if (!GetGameObject()->GetComponent<BoxCollider>()->isColliding(GetGameObject()->GetTransform()->position - glm::vec3(0.0f, 0.5f, 0.0f))) { //if the object will collide when moved down, enable gravity
			atRest = false;
		}
		gravity = 0.0f; //if the object is resting get rid of negative velocity and reset the gravity
	}
	GetGameObject()->GetTransform()->position += velocity * GetCore()->deltaT; //adjust position by velocti
	GetGameObject()->GetTransform()->rotation += torque * GetCore()->deltaT; //adjust rotation by torque
	velocity.x *= 1.0f - friction; //reduce lateral velocity by friction
	velocity.z *= 1.0f - friction;
 
}
