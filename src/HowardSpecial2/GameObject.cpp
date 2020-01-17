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
	return GetComponent<Transform>(); //return transform component
}

std::shared_ptr<Core> GameObject::GetCore()
{
	return core.lock(); //return reference to core
}

void GameObject::Update(){
	for(int i = 0; i < (int)components.size(); i++){
		components.at(i)->OnUpdate(); //update all components in the game object
	}
}

void GameObject::Render()
{
}

void GameObject::Start(){
	for (int i = 0; i < (int)components.size(); i++) {
		components.at(i)->OnStart(); //start all components in the game object
	}
}
