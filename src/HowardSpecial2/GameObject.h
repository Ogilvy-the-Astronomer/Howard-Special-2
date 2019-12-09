#pragma once
#include<memory>
#include<vector>
#include <typeinfo>
#include"Component.h"

struct Core;

struct GameObject {
	GameObject();
	~GameObject();
	
	template <class T>
	std::shared_ptr<T> AddComponent();
	template <class T, class A>
	std::shared_ptr<T> AddComponent(A a);
	template <class T, class A, class B>
	std::shared_ptr<T> AddComponent(A a, B b);
	template <class T>
	std::shared_ptr<T> GetComponent();



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

template<class T, class A>
inline std::shared_ptr<T> GameObject::AddComponent(A a){
	std::shared_ptr<T> component = std::make_shared<T>(a);
	component->parent = self;
	components.push_back(component);
	return component;
}

template<class T, class A, class B>
inline std::shared_ptr<T> GameObject::AddComponent(A a, B b)
{
	std::shared_ptr<T> component = std::make_shared<T>(a,b);
	component->parent = self;
	components.push_back(component);
	return component;
}

template<class T>
inline std::shared_ptr<T> GameObject::GetComponent()
{
	std::shared_ptr<T> foundComponent;
	for (int i = 0; i < (int)components.size(); i++) {
		if (typeid(std::shared_ptr<T>) == typeid(std::dynamic_pointer_cast<T>(components.at(i)))) {
			foundComponent = std::dynamic_pointer_cast<T>(components.at(i));
			if (foundComponent.get() != NULL) {
				return foundComponent;
				i = (int)components.size();
			}
		}
	}
	return nullptr;
}
