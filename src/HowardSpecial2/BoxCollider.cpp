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

#include "ShaderProgram.h"
#include "Material.h"
#include "Camera.h"

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

void BoxCollider::OnUpdate(float _deltaT) {
	glm::mat4 model(1.0f); //create model matrix from scale and rotation (position breaks it)
	const std::shared_ptr<Transform> t = GetGameObject()->GetTransform();
	//model = glm::translate(model, t->position + offset);
	model = glm::rotate(model, t->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, t->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, t->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, t->scale * dimensions);
	//create local unit vectors from model matrix
	Ax = glm::normalize(model * glm::vec4(1, 0, 0, 1));
	Ay = glm::normalize(model * glm::vec4(0, 1, 0, 1));
	Az = glm::normalize(model * glm::vec4(0, 0, 1, 1));
	prevCollisions.clear();
	std::shared_ptr<MeshCollider> mc = GetGameObject()->GetComponent<MeshCollider>(); //if the object also has a mesh collider, use that collision response instead
	if (mc) mc->CollisionResponse();
	else CollisionResponse();
	
}

void BoxCollider::OnRender() {
	if (debugMode) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		const std::weak_ptr<GameObject> cam = GetCore()->mainCamera; //get the main camera
		//set uniforms for the projection, model, and view matrices as well as the texture
		glm::mat4 model(1.0f);
		const std::shared_ptr<Transform> t = GetGameObject()->GetTransform();
		model = glm::translate(model, t->position + offset);
		model = glm::rotate(model, t->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, t->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, t->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, t->scale * dimensions);

		debugMat->shader->SetUniform("in_Projection", cam.lock()->GetComponent<Camera>()->GetProjection());
		debugMat->shader->SetUniform("in_Model", model);
		debugMat->shader->SetUniform("in_View", cam.lock()->GetComponent<Camera>()->GetView());

		debugMat->shader->Draw(debugShape);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void BoxCollider::OnStart(){
	debugMat = std::make_shared<Material>();
	debugMat->shader = GetCore()->resources->load<ShaderProgram>("../shaders/simple");
	debugShape = std::make_shared<Mesh>();
	debugShape = GetCore()->resources->load<Mesh>("../src/HowardSpecial2/models/cube.obj");
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
	const vec3 Pa = GetGameObject()->GetTransform()->position + offset; //get position
	const vec3 myScale = GetGameObject()->GetTransform()->scale;
	const float Wa = dimensions.x / 2.0f * myScale.x; //get box width
	const float Ha = dimensions.y / 2.0f * myScale.y; //get box height
	const float Da = dimensions.z / 2.0f * myScale.z; //get box depth
	
	for (int i = 0; i < (int)others.size(); i++) { //go through every collider in the scene TODO: less than that
		std::shared_ptr<BoxCollider> other = others.at(i);
		bool newCol = true;
		for (int j = 0; j < (int)prevCollisions.size(); j++) {
			if (other == prevCollisions.at(j)) {
				newCol = false;
				j = (int)prevCollisions.size();
			}
		}
		if (newCol) { //if the collider is different to this collider
			const vec3 Pb = other->GetGameObject()->GetTransform()->position; //get other object position
			const vec3 Bx = other->Ax; //get other box local x axis
			const vec3 By = other->Ay;//get other box local y axis
			const vec3 Bz = other->Az;//get other box local z axis
			const vec3 BScale = other->GetGameObject()->GetTransform()->scale;
			const float Wb = other->dimensions.x / 2 * BScale.x;//get other box width
			const float Hb = other->dimensions.y / 2 * BScale.y;//get other box height
			const float Db = other->dimensions.z / 2 * BScale.z;//get other box depth
			const vec3 T = Pb - Pa; //get distance between objects
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
	const vec3 Pa = _position + offset;
	const vec3 myScale = GetGameObject()->GetTransform()->scale;
	const float Wa = (dimensions.x / 2.0f) * (myScale.x);
	const float Ha = (dimensions.y / 2.0f) * (myScale.y);
	const float Da = (dimensions.z / 2.0f) * (myScale.z);

	for (int i = 0; i < (int)others.size(); i++) { //go through every collider in the scene TODO: less than that
		std::shared_ptr<BoxCollider> other = others.at(i);
		if (other != GetGameObject()->GetComponent<BoxCollider>()){
			const vec3 Pb = other->GetGameObject()->GetTransform()->position;
			const vec3 Bx = other->Ax;
			const vec3 By = other->Ay;
			const vec3 Bz = other->Az;
			const vec3 BScale = other->GetGameObject()->GetTransform()->scale;
			const float Wb = other->dimensions.x / 2.0f * BScale.x;
			const float Hb = other->dimensions.y / 2.0f * BScale.y;
			const float Db = other->dimensions.z / 2.0f * BScale.z;
			const vec3 T = Pb - Pa;
			if (c1 || c2 || c3 || c4 || c5 || c6 || c7 || c8 || c9 || c10 || c11 || c12 || c13 || c14 || c15) {
				continue;
			}
			else {
				return other; 
				//TODO: figure out what is was about
				/*
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
				*/
			}
		}

	}
	return nullptr;
}

bool BoxCollider::IsCollidingWithObject(std::shared_ptr<BoxCollider> _other, const glm::vec3 _position){
	const vec3 Pa = _position + offset; //get position
	const vec3 myScale = GetGameObject()->GetTransform()->scale;
	const float Wa = dimensions.x / 2.0f * myScale.x; //get box width
	const float Ha = dimensions.y / 2.0f * myScale.y; //get box height
	const float Da = dimensions.z / 2.0f * myScale.z; //get box depth

	const vec3 Pb = _other->GetGameObject()->GetTransform()->position; //get other object position
	const vec3 Bx = _other->Ax; //get other box local x axis
	const vec3 By = _other->Ay;//get other box local y axis
	const vec3 Bz = _other->Az;//get other box local z axis
	const vec3 BScale = _other->GetGameObject()->GetTransform()->scale;
	const float Wb = _other->dimensions.x / 2 * BScale.x;//get other box width
	const float Hb = _other->dimensions.y / 2 * BScale.y;//get other box height
	const float Db = _other->dimensions.z / 2 * BScale.z;//get other box depth
	const vec3 T = Pb - Pa; //get distance between objects
	//bool a1 = c1, a2 = c2, a3 = c3, a4 = c4, a5 = c5, a6 = c6, a7 = c7, a8 = c8, a9 = c9, a10 = c10, a11 = c11, a12 = c12, a13 = c13, a14 = c14, a15 = c15;
	if (c1 || c2 || c3 || c4 || c5 || c6 || c7 || c8 || c9 || c10 || c11 || c12 || c13 || c14 || c15) { //test if there is collision
		return false;
	}
	else {
		return true; //if there is no separation, return true
	}
}

void BoxCollider::CollisionResponse() { //repeatedly adjusts colliding object and checks collision until the object is no longer colliding
	prevCollisions.push_back(GetGameObject()->GetComponent<BoxCollider>());
	std::shared_ptr<Rigidbody> rb = GetGameObject()->GetComponent<Rigidbody>();
	glm::vec3 myPos = GetGameObject()->GetTransform()->position;
	std::shared_ptr<BoxCollider> other = isColliding(myPos);

	if (other == nullptr)
		return;

	float amount = collisionResponseStep;
	glm::vec3 position = vec3(0.0f);

	while (other != nullptr) {
		while (true) {
			if (!IsCollidingWithObject(other, myPos + position)) break; //base
			position.x += amount;
			if (!IsCollidingWithObject(other, myPos + position)) break; //x+
			position.x -= amount;
			position.x -= amount;
			if (!IsCollidingWithObject(other, myPos + position)) break; //x-
			position.x += amount;
			position.z += amount;
			if (!IsCollidingWithObject(other, myPos + position)) break; //z+
			position.z -= amount;
			position.z -= amount;
			if (!IsCollidingWithObject(other, myPos + position)) break; //z-
			position.z += amount;
			position.y += amount;
			if (!IsCollidingWithObject(other, myPos + position)) break; //y+
			position.y -= amount;
			position.y -= amount;
			if (!IsCollidingWithObject(other, myPos + position)) break; //y-
			position.y += amount;
			amount += collisionResponseStep;
		}
			
		GetGameObject()->GetTransform()->position += position;
		if (rb) {
			if (position.y > 0.0f) {
				rb->atRest = true;
				rb->velocity.y = 0.0f;
			}
		}

		prevCollisions.push_back(other);
		myPos = GetGameObject()->GetTransform()->position;
		other = isColliding(myPos);
		amount = collisionResponseStep;
	}
	prevCollisions.clear();
}

bool BoxCollider::TriTriIntersect(std::shared_ptr<GameObject> _other){ //formats two meshes into triangles and loops through them to check if any two triangles are colliding
	const int vertexCount = GetGameObject()->GetComponent<Renderer>()->shape->GetVertexCount() / 3;
	const int otherVertexCount = _other->GetComponent<Renderer>()->shape->GetVertexCount() / 3;
	const std::shared_ptr<VertexBuffer> shape = GetGameObject()->GetComponent<Renderer>()->shape->GetBuffers(0);
	const std::shared_ptr<VertexBuffer> otherShape = _other->GetComponent<Renderer>()->shape->GetBuffers(0);
	const glm::mat4 model = GetGameObject()->GetTransform()->GetModel();
	const glm::mat4 otherModel = _other->GetTransform()->GetModel();
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
			const glm::vec4 a = glm::vec4(otherShape->GetData(j, 0, 0), otherShape->GetData(j, 0, 1), otherShape->GetData(j, 0, 2), 1);
			const glm::vec4 b = glm::vec4(otherShape->GetData(j, 1, 0), otherShape->GetData(j, 1, 1), otherShape->GetData(j, 1, 2), 1);

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
	const int vertexCount = GetGameObject()->GetComponent<Renderer>()->shape->GetVertexCount() / 3;
	const int otherVertexCount = _other->GetComponent<Renderer>()->shape->GetVertexCount() / 3;
	const std::shared_ptr<VertexBuffer> shape = GetGameObject()->GetComponent<Renderer>()->shape->GetBuffers(0);
	const std::shared_ptr<VertexBuffer> otherShape = _other->GetComponent<Renderer>()->shape->GetBuffers(0);
	const glm::mat4 model = GetGameObject()->GetTransform()->GetModel();
	const glm::mat4 otherModel = _other->GetTransform()->GetModel();
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
			const glm::vec4 a = glm::vec4(otherShape->GetData(j, 0, 0), otherShape->GetData(j, 0, 1), otherShape->GetData(j, 0, 2), 1);
			const glm::vec4 b = glm::vec4(otherShape->GetData(j, 1, 0), otherShape->GetData(j, 1, 1), otherShape->GetData(j, 1, 2), 1);

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

void BoxCollider::ToggleDebugMode()
{
	debugMode = !debugMode;
}