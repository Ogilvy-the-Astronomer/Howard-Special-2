#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Core.h"
#include "Keyboard.h"

Camera::Camera(){
	projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 1000.f);
}

glm::mat4 Camera::GetView(){
	return glm::inverse(GetGameObject()->GetTransform()->GetModel());
}

glm::mat4 Camera::GetProjection(){

	return projection;
}

void Camera::OnUpdate() {
	GetGameObject()->GetTransform()->rotation -= glm::vec3(GetCore()->keyboard->GetMouseMovement().y, GetCore()->keyboard->GetMouseMovement().x, 0.0f) * 0.01f;
	GetGameObject()->GetTransform()->rotation.x = glm::clamp(GetGameObject()->GetTransform()->rotation.x, -clampVal, clampVal);
}
