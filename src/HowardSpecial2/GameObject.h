#pragma once
#include<memory>
#include<vector>
#include <typeinfo>
#include"Component.h"

struct GameObject {
	GameObject();
	~GameObject();
	
	template <class T>
	std::shared_ptr<T> AddComponent();
	template <class A>
	std::shared_ptr<A> GetComponent();
	void Update();
	void Render();

	uint32_t id;
	std::vector < std::shared_ptr<Component>> components;
};

template<class T>
inline std::shared_ptr<T> GameObject::AddComponent(){
	std::shared_ptr<T> component = std::make_shared<T>();
	components.push_back(component);
	return component;
}

template<class A>
inline std::shared_ptr<A> GameObject::GetComponent()
{
	std::shared_ptr<A> foundComponent;
	for (int i = 0; i < components.size(); i++) {
		if (typeid(std::shared_ptr<A>) == typeid(std::dynamic_pointer_cast<A>(components.at(i)))) {
			foundComponent = std::dynamic_pointer_cast<A>(components.at(i));
		}
	}
	return foundComponent;
}
