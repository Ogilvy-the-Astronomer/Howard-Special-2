#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Update(){
	for(int i = 0; i < (int)components.size(); i++)
	{
		components.at(i)->OnUpdate();
	}
}

void GameObject::Render()
{
}
