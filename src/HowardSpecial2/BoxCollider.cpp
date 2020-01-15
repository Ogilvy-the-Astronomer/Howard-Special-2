#include "BoxCollider.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Transform.h"
#include "Core.h"

#include<vector>
#include<iostream>
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

void BoxCollider::BuildDimensionsfromMesh(){
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

void BoxCollider::BuildDimensionsfromMesh(std::shared_ptr<Mesh> mesh){
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
	glm::mat4 model = GetGameObject()->GetTransform()->GetModel();
	Ax = glm::normalize(model * glm::vec4(1, 0, 0, 1));
	Ay = glm::normalize(model * glm::vec4(0, 1, 0, 1));
	Az = glm::normalize(model * glm::vec4(0, 0, 1, 1));

	if (isColliding()) {
		std::cout << "colliding\n";
	}
	else {
		std::cout << "not colliding\n";
	}

}

using namespace glm;
#define c1 (abs(dot(T, Ax)) > Wa + abs(Wb * dot(Ax, Bx)) + abs(Hb * dot(Ax, By)) + abs(Db * dot(Ax, Bz)))
#define c2 (abs(dot(T, Ay)) > Ha + abs(Wb * dot(Ay, Bx)) + abs(Hb * dot(Ay, By)) + abs(Db * dot(Ay, Bz)))
#define c3 (abs(dot(T, Az)) > Da + abs(Wb * dot(Az, Bx)) + abs(Hb * dot(Az, By)) + abs(Db * dot(Az, Bz)))
#define c4 (abs(dot(T, Bx)) > abs(Wa * dot(Ax, Bx)) + abs(Ha * dot(Ay, Bx)) + abs(Da * dot(Az, Bx) + Wb))
#define c5 (abs(dot(T, By)) > abs(Wa * dot(Ax, By)) + abs(Ha * dot(Ay, By)) + abs(Da * dot(Az, By) + Hb))
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

bool BoxCollider::isColliding(){
	std::vector<std::shared_ptr<BoxCollider>> others = GetCore()->boxColliders;
	mat4 model = GetGameObject()->GetTransform()->GetModel();
	vec3 Pa = GetGameObject()->GetTransform()->position;
	float Wa = dimensions.x / 2;
	float Ha = dimensions.y / 2;
	float Da = dimensions.z / 2;
	
	for (int i = 0; i < (int)others.size(); i++) {
		std::shared_ptr<BoxCollider> other = others.at(i);
		if (other != GetGameObject()->GetComponent<BoxCollider>()) {
			vec3 Pb = other->GetGameObject()->GetTransform()->position;
			vec3 Bx = other->Ax;
			vec3 By = other->Ay;
			vec3 Bz = other->Az;
			float Wb = other->dimensions.x / 2;
			float Hb = other->dimensions.y / 2;
			float Db = other->dimensions.z / 2;
			vec3 T = Pb - Pa;
			//bool a1 = c1, a2 = c2, a3 = c3, a4 = c4, a5 = c5, a6 = c6, a7 = c7, a8 = c8, a9 = c9, a10 = c10, a11 = c11, a12 = c12, a13 = c13, a14 = c14, a15 = c15;
			if (c1 || c2 || c3 || c4 || c5 || c6 || c7 || c8 || c9 || c10 || c11 || c12 || c13 || c14 || c15) {
				return false;
			}
			else {
				return true;
			}
		}
	}
	return false;
}

bool BoxCollider::isColliding(std::shared_ptr<BoxCollider> other){
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
