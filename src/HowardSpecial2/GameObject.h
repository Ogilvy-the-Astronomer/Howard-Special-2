#include"Component.h"

#include<memory>
#include<list>

struct GameObject {
	GameObject();
	~GameObject();
	
	template <class T>
	std::shared_ptr<T> AddComponent();
	void Update();
	void Render();
	uint32_t id;

	std::list < std::shared_ptr<Component>> components;
};

template<class T>
inline std::shared_ptr<T> GameObject::AddComponent(){
	std::shared_ptr<T> component = std::make_shared<T>();
	components.push_back(component);
	return component;
}
