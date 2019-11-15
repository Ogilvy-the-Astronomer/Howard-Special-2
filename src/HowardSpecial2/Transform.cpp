#include "Transform.h"


Transform::Transform()
{
	position = glm::vec3(0.0f, 0.0f, -5.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Transform::OnUpdate()
{
	rotation.y += 0.01f;
}

glm::mat4 Transform::GetModel()
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, scale);
	return model;
}
