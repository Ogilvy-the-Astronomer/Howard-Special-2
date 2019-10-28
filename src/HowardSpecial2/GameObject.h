#pragma once
#include<memory>
#include<vector>
#include <typeinfo>
#include"Component.h"

class Core;

struct GameObject {
	GameObject();
	~GameObject();
	
	template <class T>
	std::shared_ptr<T> AddComponent();
	template <class A>
	std::shared_ptr<A> GetComponent();
	std::shared_ptr<Core> GetCore();
	void Update();
	void Render();

	uint32_t id;
	
private:
	friend struct Core;
	std::vector < std::shared_ptr<Component>> components;
	std::weak_ptr<Core> core;
	std::weak_ptr<GameObject> self;
};

template<class T>
inline std::shared_ptr<T> GameObject::AddComponent(){
	std::shared_ptr<T> component = std::make_shared<T>();
	component->parent = self;
	components.push_back(component);
	return component;
}

template<class A>
inline std::shared_ptr<A> GameObject::GetComponent()
{
	std::shared_ptr<A> foundComponent;
	for (int i = 0; i < (int)components.size(); i++) {
		if (typeid(std::shared_ptr<A>) == typeid(std::dynamic_pointer_cast<A>(components.at(i)))) {
			foundComponent = std::dynamic_pointer_cast<A>(components.at(i));
		}
	}
	return foundComponent;
}
