#include "GameObject.h"

void GameObject::Update(){
	for(std::list<Component>::iterator it=components.begin(); it != components.end(); ++it)
	{
		*it.OnUpdate();
	}
}