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
	return parent.lock();
}

std::shared_ptr<Core> Component::GetCore(){
	return GetGameObject()->GetCore();
}
