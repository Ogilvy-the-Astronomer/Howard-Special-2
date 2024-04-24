#pragma once
#include<memory>
#include<vector>
#include<typeinfo>
#include"Component.h"
#include"Exception.h"

struct Core;
struct Transform;
/**
 A game object, which acts like a container and manager of all the components attached to
 */
struct GameObject {
	GameObject();
	~GameObject();
	
	template <class T>
	std::shared_ptr<T> AddComponent(); ///< default add component function
	template <class T, class A>
	std::shared_ptr<T> AddComponent(A a); ///< add component with 1 parameter
	template <class T, class A, class B>
	std::shared_ptr<T> AddComponent(A a, B b);///< add component with 1 parameter
	template <class T>
	std::shared_ptr<T> GetComponent(); ///< get component of type in object


	std::shared_ptr<Transform> GetTransform(); ///< shortcut function to get the transform component of an object
	std::shared_ptr<Core> GetCore(); ///< shortcut function to get the engine core
	void Update(float _deltaT); ///< update all components
	void Render();
	void Start(); ///< start all components

	uint32_t id; ///< game object id
	std::string name;
	
private:
	friend struct Core;
	std::vector < std::shared_ptr<Component>> components; ///< list of all components contained in the object
	std::weak_ptr<Core> core; ///< weak reference to the core
	std::weak_ptr<GameObject> self; ///< weak reference to self (for giving components a reference to their parent)
};

template<class T>
inline std::shared_ptr<T> GameObject::AddComponent(){
	std::shared_ptr<T> component = std::make_shared<T>(); //make a new instance of the component
	component->parent = self; //give it a reference to it's parent
	components.push_back(component); //add it to the list of components
	return component;
}

template<class T, class A>
inline std::shared_ptr<T> GameObject::AddComponent(A a){
	std::shared_ptr<T> component = std::make_shared<T>(a); //make a new instance of the component
	component->parent = self; //give it a reference to it's parent
	components.push_back(component);
	return component;
}

template<class T, class A, class B>
inline std::shared_ptr<T> GameObject::AddComponent(A a, B b){
	std::shared_ptr<T> component = std::make_shared<T>(a,b); //make a new instance of the component
	component->parent = self; //give it a reference to it's parent
	components.push_back(component); //add it to the list of components
	return component;
}

template<class T>
inline std::shared_ptr<T> GameObject::GetComponent(){
	std::shared_ptr<T> foundComponent;
	for (int i = 0; i < (int)components.size(); i++) { //go through the list of components
		if (typeid(std::shared_ptr<T>) == typeid(std::dynamic_pointer_cast<T>(components.at(i)))) { //if the component type matches the given component (I don't think this works)
			foundComponent = std::dynamic_pointer_cast<T>(components.at(i)); //down cast the component back into it's original type
			if (foundComponent.get() != NULL) { //if the casting succeeded
				return foundComponent; //return the component
				i = (int)components.size(); //
			}
		}
	}
	//throw Exception("No component of type found"); //I turned this off because it's more trouble than it's worth
	return nullptr;
}

