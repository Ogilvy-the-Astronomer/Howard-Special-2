#pragma once
#include<glm/glm.hpp>
#include "Component.h"

struct Mesh;
struct GameObject;
/**
 * The boxcollider component which detects collisions with SAT
 */
struct BoxCollider : public Component {
	BoxCollider();
	BoxCollider(glm::vec3 _dimensions); ///< construct box collider with given dimensions
	BoxCollider(glm::vec3 _dimensions, glm::vec3 _offset);///< construct box collider with given offset and dimensions
	void BuildDimensionsfromMesh();///<get box dimensions from mesh vertices
	void BuildDimensionsfromMesh(std::shared_ptr<Mesh> mesh); ///< get box dimensions from given mesh vertices
	void OnUpdate(); ///<update called every frame
	//bool isColliding();
	bool isColliding(std::shared_ptr<BoxCollider> other); ///< checks if object is colliding with other object
	bool isColliding(std::shared_ptr<BoxCollider> other, glm::vec3 position); ///< checks if object is colliding with other object at given position
	std::shared_ptr<BoxCollider> isColliding(); ///< returns the first object this object is colliding with
	std::shared_ptr<BoxCollider> isColliding(glm::vec3 _position);///< returns the first object this object is colliding with
	void CollisionResponse();///< "cludge" method collision response
	bool TriTriIntersect(std::shared_ptr<GameObject> _other);
	glm::vec3 TriTriIntersectNormal(std::shared_ptr<GameObject> _other);
	///< checks exact mesh to mesh collision with other object (unused (because it's really bad for performance)

	glm::vec3 dimensions;///< collider box dimensions
	glm::vec3 offset; ///< collider box offset
private:
	friend struct BoxCollider;
	glm::vec3 Ax;///<local x axis
	glm::vec3 Ay;///<local y axis
	glm::vec3 Az;///<local z axis
};
