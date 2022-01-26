#include "BoxCollider.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Transform.h"
#include "Core.h"
#include "Renderer.h"
#include "MeshCollider.h"
#include "TriTriOverlap.h"
#include "Rigidbody.h"
#include "MeshCollider.h"

#include<glm/gtx/normal.hpp>
#include<iostream>
#include <stdlib.h>
//https://www.jkh.me/files/tutorials/Separating%20Axis%20Theorem%20for%20Oriented%20Bounding%20Boxes.pdf

BoxCollider::BoxCollider(){
	dimensions = glm::vec3(1.0f);
	offset = glm::vec3(0.0f);
}

BoxCollider::BoxCollider(glm::vec3 _dimensions){
	dimensions = _dimensions;
	offset = glm::vec3(0.0f);
}

BoxCollider::BoxCollider(glm::vec3 _dimensions, glm::vec3 _offset){
	dimensions = _dimensions;
	offset = _offset;
}

void BoxCollider::BuildDimensionsfromMesh(){ //go through every vertex and store the maximum position in each axis (not used and not finished)
	std::shared_ptr<Mesh> mesh = GetGameObject()->GetComponent<Mesh>();
	for (int i = 0; i < mesh->GetVertexCount(); i++) {
		for (int j = 0; j < 3; i++) {
			glm::vec3 vert = glm::vec3(mesh->GetBuffers(0)->GetVertexData(i, j));
			if (dimensions.x < vert.x) dimensions.x = vert.x;
			if (dimensions.x < vert.y) dimensions.y = vert.y;
			if (dimensions.x < vert.z) dimensions.z = vert.z;
		}
	}
}

void BoxCollider::BuildDimensionsfromMesh(std::shared_ptr<Mesh> mesh){ //go through every vertex and store the maximum position in each axis (not used and not finished)
	for (int i = 0; i < mesh->GetVertexCount(); i++) {
		for (int j = 0; j < 3; i++) {
			glm::vec3 vert = glm::vec3(mesh->GetBuffers(0)->GetVertexData(i, j));
			if (dimensions.x < vert.x) dimensions.x = vert.x;
			if (dimensions.x < vert.y) dimensions.y = vert.y;
			if (dimensions.x < vert.z) dimensions.z = vert.z;
		}
	}
}

void BoxCollider::OnUpdate() {
	glm::mat4 model(1.0f); //create model matrix from scale and rotation (position breaks it)
	std::shared_ptr<Transform> t = GetGameObject()->GetTransform();
	model = glm::rotate(model, t->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, t->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, t->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, t->scale);
	//create local unit vectors from model matrix
	Ax = glm::normalize(model * glm::vec4(1, 0, 0, 1));
	Ay = glm::normalize(model * glm::vec4(0, 1, 0, 1));
	Az = glm::normalize(model * glm::vec4(0, 0, 1, 1));
	prevCollisions.clear();
	std::shared_ptr<MeshCollider> mc = GetGameObject()->GetComponent<MeshCollider>(); //if the object also has a mesh collider, use that collision response instead
	if (mc) mc->CollisionResponse();
	else CollisionResponse();
	
}

using namespace glm; //create 15 planes of separation (3 from object 1 local axis, 3 from object 2 local axis, 9 from the combination of each pair of axis), then test to see if the two objects
#define c1 (abs(dot(T, Ax)) > Wa + abs(Wb * dot(Ax, Bx)) + abs(Hb * dot(Ax, By)) + abs(Db * dot(Ax, Bz))) // overlap when projected onto this plane
#define c2 (abs(dot(T, Ay)) > Ha + abs(Wb * dot(Ay, Bx)) + abs(Hb * dot(Ay, By)) + abs(Db * dot(Ay, Bz))) // the objects are considered colliding if all of the tests fail
#define c3 (abs(dot(T, Az)) > Da + abs(Wb * dot(Az, Bx)) + abs(Hb * dot(Az, By)) + abs(Db * dot(Az, Bz))) // if any one test pass it means the two objects can't be colliding because
#define c4 (abs(dot(T, Bx)) > abs(Wa * dot(Ax, Bx)) + abs(Ha * dot(Ay, Bx)) + abs(Da * dot(Az, Bx) + Wb)) // there is a plane between then which seperates them
#define c5 (abs(dot(T, By)) > abs(Wa * dot(Ax, By)) + abs(Ha * dot(Ay, By)) + abs(Da * dot(Az, By) + Hb)) // you can get the normal of the plane(s) to find out the direction which seperates them
#define c6 (abs(dot(T, Bz)) > abs(Wa * dot(Ax, Bz)) + abs(Ha * dot(Ay, Bz)) + abs(Da * dot(Az, Bz) + Db))
#define c7 (abs(dot(T, Az) * dot(Ay, Bx) - dot(T, Ay) * dot(Az, Bx)) > abs(Ha * dot(Az, Bx)) + abs(Da * dot(Ay, Bx)) + abs(Hb * dot(Ax, Bz)) + abs(Db * dot(Ax, By)))
#define c8 (abs(dot(T, Az) * dot(Ay, By) - dot(T, Ay) * dot(Az, By)) > abs(Ha * dot(Az, By)) + abs(Da * dot(Ay, By)) + abs(Wb * dot(Ax, Bz)) + abs(Db * dot(Ax, Bx)))
#define c9 (abs(dot(T, Az) * dot(Ay, Bz) - dot(T, Ay) * dot(Az, Bz)) > abs(Ha * dot(Az, Bz)) + abs(Da * dot(Ay, Bz)) + abs(Wb * dot(Ax, By)) + abs(Hb * dot(Ax, Bx)))
#define c10 (abs(dot(T, Ax) * dot(Az, Bx) - dot(T, Az) * dot(Ax, Bx)) > abs(Wa * dot(Az, Bx)) + abs(Da * dot(Ax, Bx)) + abs(Hb * dot(Ay, Bz)) + abs(Db * dot(Ay, By)))
#define c11 (abs(dot(T, Ax) * dot(Az, By) - dot(T, Az) * dot(Ax, By)) > abs(Wa * dot(Az, By)) + abs(Da * dot(Ax, By)) + abs(Wb * dot(Ay, Bz)) + abs(Db * dot(Ay, Bx)))
#define c12 (abs(dot(T, Ax) * dot(Az, Bz) - dot(T, Az) * dot(Ax, Bz)) > abs(Wa * dot(Az, Bz)) + abs(Da * dot(Ax, Bz)) + abs(Wb * dot(Ay, By)) + abs(Hb * dot(Ay, Bx)))
#define c13 (abs(dot(T, Ay) * dot(Ax, Bx) - dot(T, Ax) * dot(Ay, Bx)) > abs(Wa * dot(Ay, Bx)) + abs(Ha * dot(Ax, Bx)) + abs(Hb * dot(Az, Bz)) + abs(Db * dot(Az, By)))
#define c14 (abs(dot(T, Ay) * dot(Ax, By) - dot(T, Ax) * dot(Ay, By)) > abs(Wa * dot(Ay, By)) + abs(Ha * dot(Ax, By)) + abs(Wb * dot(Az, Bz)) + abs(Db * dot(Az, Bx)))
#define c15 (abs(dot(T, Ay) * dot(Ax, Bz) - dot(T, Ax) * dot(Ay, Bz)) > abs(Wa * dot(Ay, Bz)) + abs(Ha * dot(Ax, Bz)) + abs(Wb * dot(Az, By)) + abs(Hb * dot(Az, Bx)))

std::shared_ptr<BoxCollider> BoxCollider::isColliding(){
	std::vector<std::shared_ptr<BoxCollider>> others = GetCore()->boxColliders; //get a list of all other box colliders in the scene
	vec3 Pa = GetGameObject()->GetTransform()->position + offset; //get position
	float Wa = dimensions.x / 2 * GetGameObject()->GetTransform()->scale.x; //get box width
	float Ha = dimensions.y / 2 * GetGameObject()->GetTransform()->scale.y; //get box height
	float Da = dimensions.z / 2 * GetGameObject()->GetTransform()->scale.z; //get box depth
	
	for (int i = 0; i < (int)others.size(); i++) { //go through every collider in the scene
		std::shared_ptr<BoxCollider> other = others.at(i);
		bool newCol = true;
		for (int j = 0; j < (int)prevCollisions.size(); j++) {
			if (other == prevCollisions.at(j)) {
				newCol = false;
				j = (int)prevCollisions.size();
			}
		}
		if (newCol) { //if the collider is different to this collider
			vec3 Pb = other->GetGameObject()->GetTransform()->position; //get other object position
			vec3 Bx = other->Ax; //get other box local x axis
			vec3 By = other->Ay;//get other box local y axis
			vec3 Bz = other->Az;//get other box local z axis
			float Wb = other->dimensions.x / 2 * other->GetGameObject()->GetTransform()->scale.x;//get other box width
			float Hb = other->dimensions.y / 2 * other->GetGameObject()->GetTransform()->scale.y;//get other box height
			float Db = other->dimensions.z / 2 * other->GetGameObject()->GetTransform()->scale.z;//get other box depth
			vec3 T = Pb - Pa; //get distance between objects
			//bool a1 = c1, a2 = c2, a3 = c3, a4 = c4, a5 = c5, a6 = c6, a7 = c7, a8 = c8, a9 = c9, a10 = c10, a11 = c11, a12 = c12, a13 = c13, a14 = c14, a15 = c15;
			if (c1 || c2 || c3 || c4 || c5 || c6 || c7 || c8 || c9 || c10 || c11 || c12 || c13 || c14 || c15) { //test if there is collision

			}
			else {
				prevCollisions.push_back(other);
				return other; //if there is no separation, return the current object
			}
		}
	}

	return nullptr; //if there is no colliding object, return null ptr
}

std::shared_ptr<BoxCollider> BoxCollider::isColliding(glm::vec3 _position){ //does the same as above function but uses the given position instead of the object position
	std::vector<std::shared_ptr<BoxCollider>> others = GetCore()->boxColliders;
	vec3 Pa = _position + offset;
	float Wa = (dimensions.x / 2.0f) * (GetGameObject()->GetTransform()->scale.x);
	float Ha = (dimensions.y / 2.0f) * (GetGameObject()->GetTransform()->scale.y);
	float Da = (dimensions.z / 2.0f) * (GetGameObject()->GetTransform()->scale.z);

	for (int i = 0; i < (int)others.size(); i++) {
		std::shared_ptr<BoxCollider> other = others.at(i);
		if (other != GetGameObject()->GetComponent<BoxCollider>()) {
			vec3 Pb = other->GetGameObject()->GetTransform()->position;
			vec3 Bx = other->Ax;
			vec3 By = other->Ay;
			vec3 Bz = other->Az;
			float Wb = other->dimensions.x / 2.0f * other->GetGameObject()->GetTransform()->scale.x;
			float Hb = other->dimensions.y / 2.0f * other->GetGameObject()->GetTransform()->scale.y;
			float Db = other->dimensions.z / 2.0f * other->GetGameObject()->GetTransform()->scale.z;
			vec3 T = Pb - Pa;
			//bool a1 = c1, a2 = c2, a3 = c3, a4 = c4, a5 = c5, a6 = c6, a7 = c7, a8 = c8, a9 = c9, a10 = c10, a11 = c11, a12 = c12, a13 = c13, a14 = c14, a15 = c15;
			if (c1 || c2 || c3 || c4 || c5 || c6 || c7 || c8 || c9 || c10 || c11 || c12 || c13 || c14 || c15) {

			}
			else {
				return other;
				std::shared_ptr<MeshCollider> complex = other->GetGameObject()->GetComponent<MeshCollider>();
				if (complex) {
					if (complex->isColliding(GetGameObject(), glm::vec3(0.0f))) {
						return other;
					}
					else {
						return nullptr;
					}
				}
				else {
					return other;
				}
			}
		}

	}
	return nullptr;
}

void BoxCollider::CollisionResponse() { //repeatedly adjusts colliding object and checks collision until the object is no longer colliding
	prevCollisions.push_back(GetGameObject()->GetComponent<BoxCollider>());
	std::shared_ptr<Rigidbody> rb = GetGameObject()->GetComponent<Rigidbody>();
	std::shared_ptr<BoxCollider> other = isColliding();
	int num = 0;
	while (other != nullptr) {
		float amount = 0.05f;
		float step = 0.01f;
		glm::vec3 position = vec3(0.0f);
		if (rb) {
			while (true) {
				if (!isColliding(GetGameObject()->GetTransform()->position + position)) break;
				position.x += amount;
				if (!isColliding(GetGameObject()->GetTransform()->position + position)) break;
				position.x -= amount;
				position.x -= amount;
				if (!isColliding(GetGameObject()->GetTransform()->position + position)) break;
				position.x += amount;
				position.z += amount;
				if (!isColliding(GetGameObject()->GetTransform()->position + position)) break;
				position.z -= amount;
				position.z -= amount;
				if (!isColliding(GetGameObject()->GetTransform()->position + position)) break;
				position.z += amount;
				position.y += amount;
				if (!isColliding(GetGameObject()->GetTransform()->position + position)) break;
				position.y -= amount;
				position.y -= amount;
				if (!isColliding(GetGameObject()->GetTransform()->position + position)) break;
				position.y += amount;
				amount += step;
				if (amount > 2.0f) {
					position = rb->velocity * -2.0f;
				}
			}
			num++;
			rb->velocity += glm::vec3(position.x, 0.0f, position.z);
			rb->GetGameObject()->GetTransform()->position.y += position.y;
			if (position.y > 0.0f) {
				rb->atRest = true;
				rb->velocity.y = 0.0f;
			}

			other = isColliding();
		}
		else {
			while (true) {
				if (!isColliding(GetGameObject()->GetTransform()->position + position)) break;
				position.x += amount;
				if (!isColliding(GetGameObject()->GetTransform()->position + position)) break;
				position.x -= amount;
				position.x -= amount;
				if (!isColliding(GetGameObject()->GetTransform()->position + position)) break;
				position.x += amount;
				position.z += amount;
				if (!isColliding(GetGameObject()->GetTransform()->position + position)) break;
				position.z -= amount;
				position.z -= amount;
				if (!isColliding(GetGameObject()->GetTransform()->position + position)) break;
				position.z += amount;
				position.y += amount;
				if (!isColliding(GetGameObject()->GetTransform()->position + position)) break;
				position.y -= amount;
				position.y -= amount;
				if (!isColliding(GetGameObject()->GetTransform()->position + position)) break;
				position.y += amount;

				amount += step;
			}
			num++;
			GetGameObject()->GetTransform()->position += position;
			if(GetGameObject()->name == std::string("Scarecrow"))
			{
				std::cout << GetGameObject()->name << ' ' << std::to_string(position.x) << ' ' << std::to_string(position.y) << ' ' << std::to_string(position.z) << std::endl;
			}
		}
		other = isColliding();
	}

	//if(num > 0) std::cout << "collided with " << num << " things" << std::endl;
	std::string name = GetGameObject()->name;
	if (num > 0 && name != std::string("Player")) std::cout << name << std::endl;
}

bool BoxCollider::TriTriIntersect(std::shared_ptr<GameObject> _other){ //formats two meshes into triangles and loops through them to check if any two triangles are colliding
	int vertexCount = GetGameObject()->GetComponent<Renderer>()->shape->GetVertexCount() / 3;
	int otherVertexCount = _other->GetComponent<Renderer>()->shape->GetVertexCount() / 3;
	std::shared_ptr<VertexBuffer> shape = GetGameObject()->GetComponent<Renderer>()->shape->GetBuffers(0);
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
	return false;
}

glm::vec3 BoxCollider::TriTriIntersectNormal(std::shared_ptr<GameObject> _other) { //formats two meshes into triangles and loops through them to check if any two triangles are colliding
	int vertexCount = GetGameObject()->GetComponent<Renderer>()->shape->GetVertexCount() / 3;
	int otherVertexCount = _other->GetComponent<Renderer>()->shape->GetVertexCount() / 3;
	std::shared_ptr<VertexBuffer> shape = GetGameObject()->GetComponent<Renderer>()->shape->GetBuffers(0);
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
				glm::vec3 a = tri2Vert1;
				glm::vec3 b = tri2Vert2;
				glm::vec3 c = tri2Vert3;
				glm::vec3 rtn = glm::triangleNormal(a,b,c);
				return rtn;
			}
		}
	}
	return {};
}


//!!! DANGER !!! do not use these idk why they're here but i don't wanna get rid of them in case they break something
bool BoxCollider::isColliding(std::shared_ptr<BoxCollider> other){ //same as isColliding function above but returns true/ false with specified object
	mat4 model = GetGameObject()->GetTransform()->GetModel();
	vec3 Pa = GetGameObject()->GetTransform()->position;
	float Wa = dimensions.x / 2;
	float Ha = dimensions.y / 2;
	float Da = dimensions.z / 2;

	vec3 Pb = other->GetGameObject()->GetTransform()->position;
	vec3 Bx = other->Ax;
	vec3 By = other->Ay;
	vec3 Bz = other->Az;
	float Wb = other->dimensions.x / 2;
	float Hb = other->dimensions.y / 2;
	float Db = other->dimensions.z / 2;
	vec3 T = Pb - Pa;
	if (c1 && c2 && c3 && c4 && c5 && c6 && c7 && c8 && c9 && c10 && c11 && c12 && c13 && c14 && c15) {
		return true;
	}
	else {
		return false;
	}
	return false;
}

bool BoxCollider::isColliding(std::shared_ptr<BoxCollider> other, glm::vec3 position) { //same as above but using given position;

	mat4 model = GetGameObject()->GetTransform()->GetModel(position);
	vec3 Pa = GetGameObject()->GetTransform()->position + position;
	float Wa = dimensions.x / 2;
	float Ha = dimensions.y / 2;
	float Da = dimensions.z / 2;

	vec3 Pb = other->GetGameObject()->GetTransform()->position;
	vec3 Bx = other->Ax;
	vec3 By = other->Ay;
	vec3 Bz = other->Az;
	float Wb = other->dimensions.x / 2;
	float Hb = other->dimensions.y / 2;
	float Db = other->dimensions.z / 2;
	vec3 T = Pb - Pa;
	if (c1 || c2 || c3 || c4 || c5 || c6 || c7 || c8 || c9 || c10 || c11 || c12 || c13 || c14 || c15) {
		return true;
	}
	else {
		return false;
	}
	return nullptr;
}
