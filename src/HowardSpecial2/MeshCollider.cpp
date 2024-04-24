#include "MeshCollider.h"
#include "VertexBuffer.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Exception.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "Core.h"
#include <iostream>
#include "TriBoxOverlap.h"
#include "Rigidbody.h"

MeshCollider::MeshCollider(){
	dimensions = glm::vec3(1.0f);
	offset = glm::vec3(0.0f);
}

MeshCollider::MeshCollider(glm::vec3 _dimensions){
	dimensions = _dimensions;
	offset = glm::vec3(0.0f);
}

MeshCollider::MeshCollider(glm::vec3 _dimensions, glm::vec3 _offset){
	dimensions = _dimensions;
	offset = _offset;
}

bool MeshCollider::TriTriIntersect(std::shared_ptr<GameObject> _other) { //mesh to mesh collision, disabled due to troubles with TriTriOverlap header
	/*
	int vertexCount = shape->GetDataSize() / shape->GetComponents();
	int otherVertexCount = _other->GetComponent<Renderer>()->shape->GetVertexCount() / 3;
	std::shared_ptr<VertexBuffer> otherShape = _other->GetComponent<Renderer>()->shape->GetBuffers(0);
	glm::mat4 model = GetGameObject()->GetTransform()->GetModel();
	glm::mat4 otherModel = _other->GetTransform()->GetModel();
	glm::vec4 tri1Vert1;
	glm::vec4 tri1Vert2;
	glm::vec4 tri1Vert3;
	glm::vec4 tri2Vert1;
	glm::vec4 tri2Vert2;
	glm::vec4 tri2Vert3;
	for (int i = 0; i < vertexCount; i++) {
		tri1Vert1 = model * glm::vec4(shape->GetData(i, 0, 0), shape->GetData(0, 1), shape->GetData(i, 0, 2), 1);
		tri1Vert2 = model * glm::vec4(shape->GetData(i, 1, 0), shape->GetData(1, 1), shape->GetData(i, 1, 2), 1);
		tri1Vert3 = model * glm::vec4(shape->GetData(i, 2, 0), shape->GetData(2, 1), shape->GetData(i, 2, 2), 1);
		float tri10[] = { tri1Vert1.x, tri1Vert1.y, tri1Vert1.z };
		float tri11[] = { tri1Vert2.x, tri1Vert2.y, tri1Vert2.z };
		float tri12[] = { tri1Vert3.x, tri1Vert3.y, tri1Vert3.z };
		for (int j = 0; j < otherVertexCount; j++) {
			glm::vec4 a = glm::vec4(otherShape->GetData(j, 0, 0), otherShape->GetData(j, 0, 1), otherShape->GetData(j, 0, 2), 1);
			glm::vec4 b = glm::vec4(otherShape->GetData(j, 1, 0), otherShape->GetData(j, 1, 1), otherShape->GetData(j, 1, 2), 1);

			tri2Vert1 = otherModel * glm::vec4(otherShape->GetData(j, 0, 0), otherShape->GetData(j, 0, 1), otherShape->GetData(j, 0, 2), 1);
			tri2Vert2 = otherModel * glm::vec4(otherShape->GetData(j, 1, 0), otherShape->GetData(j, 1, 1), otherShape->GetData(j, 1, 2), 1);
			tri2Vert3 = otherModel * glm::vec4(otherShape->GetData(j, 2, 0), otherShape->GetData(j, 2, 1), otherShape->GetData(j, 2, 2), 1);
			float tri20[] = { tri2Vert1.x, tri2Vert1.y, tri2Vert1.z };
			float tri21[] = { tri2Vert2.x, tri2Vert2.y, tri2Vert2.z };
			float tri22[] = { tri2Vert3.x, tri2Vert3.y, tri2Vert3.z };
			if (NoDivTriTriIsect(tri10, tri11, tri12, tri20, tri21, tri22)) {
				return true;
			}
		}
	}
	*/
	return false;
}

bool MeshCollider::TriBoxIntersect(std::shared_ptr<GameObject> _other){ //checks if the mesh collides with other object
	std::shared_ptr<BoxCollider> bc = _other->GetComponent<BoxCollider>(); 
	if (bc) { //check if the other object has a box collider component just to be safe
		const int vertexCount = shape->GetDataSize() / shape->GetComponents(); //get the amount of vertices in this object
		const glm::mat4 model = GetGameObject()->GetTransform()->GetModel(); //get the model matrix
		const glm::vec3 t = _other->GetTransform()->position; //get the other object position
		glm::vec4 tri1Vert1;
		glm::vec4 tri1Vert2;
		glm::vec4 tri1Vert3;
		float boxCenter[] = { t.x + offset.x, t.y + offset.y, t.z + offset.z }; //create the box center from the other object's stuff
		float boxHalfSize[] = { bc->dimensions.x / 2,  bc->dimensions.y / 2,  bc->dimensions.z / 2 }; //create the box dimensions from the other object's stuff
		for (int i = 0; i < vertexCount / 3; i++) { //go through every vertex and check if it's colliding with the box
			tri1Vert1 = model * glm::vec4(shape->GetData(i, 0, 0), shape->GetData(0, 1), shape->GetData(i, 0, 2), 1);
			tri1Vert2 = model * glm::vec4(shape->GetData(i, 1, 0), shape->GetData(1, 1), shape->GetData(i, 1, 2), 1);
			tri1Vert3 = model * glm::vec4(shape->GetData(i, 2, 0), shape->GetData(2, 1), shape->GetData(i, 2, 2), 1);
			float tri[3][3] =
			{ { tri1Vert1.x, tri1Vert1.y, tri1Vert1.z },
			{ tri1Vert2.x, tri1Vert2.y, tri1Vert2.z },
			{ tri1Vert3.x, tri1Vert3.y, tri1Vert3.z } };
			if (triBoxOverlap(boxCenter, boxHalfSize, tri)) {
				return true;
			}
		}
	}
	return false;
}

bool MeshCollider::isColliding(std::shared_ptr<GameObject> _other, glm::vec3 _position){ //same as above but using given position
	const std::shared_ptr<BoxCollider> bc = _other->GetComponent<BoxCollider>();
	if (bc) {
		const int vertexCount = shape->GetDataSize() / shape->GetComponents();
		const glm::mat4 model = GetGameObject()->GetTransform()->GetModel();
		const glm::vec3 t = _other->GetTransform()->position + _position;
		glm::vec3 s = _other->GetTransform()->scale;// *2.0f;
		glm::vec4 tri1Vert1;
		glm::vec4 tri1Vert2;
		glm::vec4 tri1Vert3;
		float boxCenter[] = { t.x + offset.x, t.y + offset.y, t.z + offset.z };
		float boxHalfSize[] = { s.x * bc->dimensions.x / 1.0f, s.y * bc->dimensions.y / 1.0f, s.z * bc->dimensions.z / 1.0f };
		for (int i = 0; i < vertexCount / 3; i++) {
			tri1Vert1 = model * glm::vec4(shape->GetData(i, 0, 0), shape->GetData(i, 0, 1), shape->GetData(i, 0, 2), 1);
			tri1Vert2 = model * glm::vec4(shape->GetData(i, 1, 0), shape->GetData(i, 1, 1), shape->GetData(i, 1, 2), 1);
			tri1Vert3 = model * glm::vec4(shape->GetData(i, 2, 0), shape->GetData(i, 2, 1), shape->GetData(i, 2, 2), 1);
			float tri[3][3] =
			{ { tri1Vert1.x, tri1Vert1.y, tri1Vert1.z },
			{ tri1Vert2.x, tri1Vert2.y, tri1Vert2.z },
			{ tri1Vert3.x, tri1Vert3.y, tri1Vert3.z } };
			if (triBoxOverlap(boxCenter, boxHalfSize, tri)) {
				return true;
			}
		}
	}
	return false;
}
//TODO: add vector variant of this function
std::shared_ptr<GameObject> MeshCollider::isColliding(){ //check collisions vs every object in the scene and return the first collision
	std::vector<std::shared_ptr<BoxCollider>> others = GetCore()->boxColliders;
	std::shared_ptr<GameObject> rtn;
	for (int i = 0; i < (int)others.size(); i++) {
		rtn = others.at(i)->GetGameObject();
		if (rtn != GetGameObject() && !rtn->GetComponent<MeshCollider>()) {
			if (TriBoxIntersect(rtn)) {
				return rtn;
			}
		}
	}
	return nullptr;
}

void MeshCollider::CollisionResponse(){ //kludge the colliding object
	std::shared_ptr<GameObject> other = isColliding();
	if (other) {
		std::shared_ptr<Rigidbody> rb = other->GetComponent<Rigidbody>();
		if (rb) return;
		float amount = 0.1f;
		float step = 0.1f;
		glm::vec3 position = glm::vec3(0.0f);
		while (true) {
			if (!isColliding(other, position)) break; //base
			position.x += amount;
			if (!isColliding(other, position)) break; //x+
			position.x -= amount;
			position.x -= amount;
			if (!isColliding(other, position)) break; //x-
			position.x += amount;
			position.z += amount;
			if (!isColliding(other, position)) break; //z+
			position.z -= amount;
			position.z -= amount;
			if (!isColliding(other, position)) break; //z-
			position.z += amount;
			position.y += amount;
			if (!isColliding(other, position)) break; //y+
			position.y -= amount;
			position.y -= amount;
			if (!isColliding(other, position)) break; //y-
			position.y += amount;
			amount += step; //increment step
			std::cout << amount << std::endl;
		}
		other->GetTransform()->position += position;
		std::cout << "kludge" << std::endl;
	}
}

void MeshCollider::OnStart(){
	try {
		if(!shape) shape = GetGameObject()->GetComponent<Renderer>()->shape->GetBuffers(0);
		std::shared_ptr<BoxCollider> bc = GetGameObject()->GetComponent<BoxCollider>();
		dimensions = bc->dimensions;
		offset = bc->offset;
	}
	catch (Exception& e) {
		std::cout << "MeshCollider component added to an object without a Renderer and/or BoxCollider component" << std::endl;
	}
}
