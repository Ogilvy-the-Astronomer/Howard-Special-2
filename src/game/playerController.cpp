#include "playerController.h"

void PlayerController::OnUpdate(float _deltaT){
	glm::vec3 camVel;
	if (Input->GetKey(SDL_SCANCODE_W)) camVel -= glm::vec3(camera->GetTransform()->forward.x, 0.0f, camera->GetTransform()->forward.z)  * 0.05f;
	if (Input->GetKey(SDL_SCANCODE_S)) camVel += glm::vec3(camera->GetTransform()->forward.x, 0.0f, camera->GetTransform()->forward.z) * 0.05f;
	if (Input->GetKey(SDL_SCANCODE_A)) camVel -= glm::vec3(camera->GetTransform()->right.x, 0.0f, camera->GetTransform()->right.z) * 0.05f;
	if (Input->GetKey(SDL_SCANCODE_D)) camVel += glm::vec3(camera->GetTransform()->right.x, 0.0f, camera->GetTransform()->right.z)* 0.05f;
	if (rb->IsGrounded() && Input->GetKeyDown(SDL_SCANCODE_SPACE)) camVel.y = 0.2f;
	rb->velocity += camVel * _deltaT;

	if (Input->GetKeyDown(SDL_SCANCODE_F7)) {
		std::vector<std::shared_ptr<BoxCollider>> boxes = GetCore()->GetComponents<BoxCollider>();
		for (int i = 0; i < boxes.size(); i++) {
			boxes[i]->ToggleDebugMode();
		}
	}

	if (glm::length(camVel) > 0.0f && audioSource != nullptr) {
		if (!audioSource->isPlaying && rb->IsGrounded()) {
			audioSource->Play();
		}
	}

	GetGameObject()->GetTransform()->rotation -= glm::vec3(GetCore()->keyboard->GetMouseMovement().y, GetCore()->keyboard->GetMouseMovement().x, 0.0f) * 0.01f;
	GetGameObject()->GetTransform()->rotation.x = glm::clamp(GetGameObject()->GetTransform()->rotation.x, -clampVal, clampVal);

	camera->GetTransform()->position = rb->GetGameObject()->GetTransform()->position + glm::vec3(0.0f,0.5f,0.0f);
	if(GetGameObject()->GetTransform()->position.y < -100.0f ){
		rb->GetGameObject()->GetTransform()->position.y = 0;
		rb->velocity.y = 0;
	}
}

void PlayerController::OnStart(){
	camera = GetGameObject();
	Input = GetCore()->keyboard;
	audioSource = rb->GetGameObject()->GetComponent<SoundSource>();
}
