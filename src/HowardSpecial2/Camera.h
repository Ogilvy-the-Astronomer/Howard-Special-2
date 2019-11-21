#pragma once
#include "Component.h"
#include <glm/ext.hpp>
struct Camera : public Component {
	Camera();
	glm::mat4 GetView();
	glm::mat4 GetProjection();
	void OnUpdate();
private:
	glm::mat4 projection;
};