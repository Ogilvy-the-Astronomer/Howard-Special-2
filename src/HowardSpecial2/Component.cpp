#include <iostream>
#include "Component.h"
#include "GameObject.h"

void Component::OnUpdate(){
}

void Component::OnRender(){
}

void Component::OnStart(){
}

std::shared_ptr<GameObject> Component::GetGameObject(){
	return parent.lock(); //return shared pointer to parent game object
}

std::shared_ptr<Core> Component::GetCore(){
	return GetGameObject()->GetCore(); //return shared pointer to core
}
