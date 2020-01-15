#pragma once
#include<glm/glm.hpp>
#include "Component.h"

struct Mesh;
struct GameObject;

struct BoxCollider : public Component {
	BoxCollider();
	BoxCollider(glm::vec3 _dimensions);
	BoxCollider(glm::vec3 _dimensions, glm::vec3 _offset);
	void BuildDimensionsfromMesh();
	void BuildDimensionsfromMesh(std::shared_ptr<Mesh> mesh);
	void OnUpdate();
	bool isColliding();
	bool isColliding(std::shared_ptr<BoxCollider> other);

	glm::vec3 dimensions;
	glm::vec3 offset;
private:
	friend struct BoxCollider;
	glm::vec3 Ax;
	glm::vec3 Ay;
	glm::vec3 Az;
};
