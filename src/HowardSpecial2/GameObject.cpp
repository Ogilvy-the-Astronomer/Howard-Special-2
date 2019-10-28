#include "GameObject.h"
#include "Core.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
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
