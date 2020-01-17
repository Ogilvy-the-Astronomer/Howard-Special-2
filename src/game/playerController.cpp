#include "playerController.h"

void PlayerController::OnUpdate(){
	glm::vec3 camVel;
	if (Input->GetKey(SDL_SCANCODE_W)) camVel -= glm::vec3(camera->GetTransform()->forward.x, 0.0f, camera->GetTransform()->forward.z)  * 0.2f;
	if (Input->GetKey(SDL_SCANCODE_S)) camVel += glm::vec3(camera->GetTransform()->forward.x, 0.0f, camera->GetTransform()->forward.z) * 0.2f;
	if (Input->GetKey(SDL_SCANCODE_A)) camVel -= glm::vec3(camera->GetTransform()->right.x, 0.0f, camera->GetTransform()->right.z) * 0.2f;
	if (Input->GetKey(SDL_SCANCODE_D)) camVel += glm::vec3(camera->GetTransform()->right.x, 0.0f, camera->GetTransform()->right.z)* 0.2f;
	if (rb->velocity.y == 0 && Input->GetKeyDown(SDL_SCANCODE_SPACE)) camVel.y = 0.2f;
	rb->velocity += camVel;

	GetGameObject()->GetTransform()->rotation -= glm::vec3(GetCore()->keyboard->GetMouseMovement().y, GetCore()->keyboard->GetMouseMovement().x, 0.0f) * 0.01f;
	GetGameObject()->GetTransform()->rotation.x = glm::clamp(GetGameObject()->GetTransform()->rotation.x, -clampVal, clampVal);

	camera->GetTransform()->position = rb->GetGameObject()->GetTransform()->position;
}

void PlayerController::OnStart(){
	camera = GetGameObject();
	Input = GetCore()->keyboard;
}
