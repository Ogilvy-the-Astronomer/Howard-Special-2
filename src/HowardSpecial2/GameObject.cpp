#include "GameObject.h"
#include "Core.h"
#include "Transform.h"


GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

std::shared_ptr<Transform> GameObject::GetTransform(){
	return GetComponent<Transform>();
}

std::shared_ptr<Core> GameObject::GetCore()
{
	return core.lock();
}

void GameObject::Update(){
	for(int i = 0; i < (int)components.size(); i++){
		components.at(i)->OnUpdate();
	}
}

void GameObject::Render()
{
}
