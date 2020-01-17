#pragma once
#include "Component.h"
#include "glm/vec3.hpp"

struct VertexBuffer;
struct Mesh;
struct BoxCollider;
/**
 * a static collider for checking mesh vs boxes
 */
struct MeshCollider : public Component {
	MeshCollider(); ///< default constructor
	MeshCollider(glm::vec3 _dimensions); ///< constructor giving dimension values
	MeshCollider(glm::vec3 _dimensions, glm::vec3 _offset); ///< consturctor giving dimension and offset values

	bool TriTriIntersect(std::shared_ptr<GameObject> _other); ///< mesh to mesh collision (not used because it's inefficient)
	bool TriBoxIntersect(std::shared_ptr<GameObject> _other); ///< box to mesh collision

	bool isColliding(std::shared_ptr<GameObject> _other, glm::vec3 _position); ///< returns if this object is colliding with another at the given position
	std::shared_ptr<GameObject> isColliding(); ///< returns which object is colliding with this one
	
	void CollisionResponse(); ///< "kludge" collision response to other mesh because this mesh is static
	void OnStart(); 

	glm::vec3 dimensions; ///< box dimensions
	glm::vec3 offset; ///< box offset
private:
	std::shared_ptr<VertexBuffer> shape; ///< the shape of the mesh this component is attached to
};