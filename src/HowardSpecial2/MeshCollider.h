#pragma once
#include "Component.h"
#include "glm/vec3.hpp"

struct VertexBuffer;
struct Mesh;
struct BoxCollider;

struct MeshCollider : public Component {
	MeshCollider();
	MeshCollider(glm::vec3 _dimensions);
	MeshCollider(glm::vec3 _dimensions, glm::vec3 _offset);

	MeshCollider(std::shared_ptr<Mesh> _mesh);
	MeshCollider(std::shared_ptr<Mesh> _mesh, glm::vec3 _dimensions);
	MeshCollider(std::shared_ptr<Mesh> _mesh, glm::vec3 _dimensions, glm::vec3 _offset);
	bool TriTriIntersect(std::shared_ptr<GameObject> _other);
	bool TriBoxIntersect(std::shared_ptr<GameObject> _other);

	bool isColliding(std::shared_ptr<GameObject> _other);
	bool isColliding(std::shared_ptr<GameObject> _other, glm::vec3 _position);
	std::shared_ptr<GameObject> isColliding();
	
	void CollisionResponse();
	void OnStart();

	glm::vec3 dimensions;
	glm::vec3 offset;
private:
	std::shared_ptr<VertexBuffer> shape;
};