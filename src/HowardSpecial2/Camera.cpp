#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Core.h"
#include "Keyboard.h"

Camera::Camera(){
	aspectRatio = 1.0f;
	projection = glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 1000.f); //create camera perspective matrix
}

glm::mat4 Camera::GetView(){
	return glm::inverse(GetGameObject()->GetTransform()->GetModel()); //get the inverse of the model matrix of the object the camera is attached to
}

glm::mat4 Camera::GetProjection(){

	return projection;
}

void Camera::OnUpdate() {
	//GetGameObject()->GetTransform()->rotation -= glm::vec3(GetCore()->keyboard->GetMouseMovement().y, GetCore()->keyboard->GetMouseMovement().x, 0.0f) * 0.01f;
	//GetGameObject()->GetTransform()->rotation.x = glm::clamp(GetGameObject()->GetTransform()->rotation.x, -clampVal, clampVal);
}

void Camera::OnStart() {
	float w = GetCore()->window_w;
	float h = GetCore()->window_h;
	aspectRatio = w / h;
	projection = glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 1000.f); //create camera perspective matrix
}

