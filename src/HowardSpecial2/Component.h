#pragma once
#include <memory>

class GameObject;
class Core;

struct Component {
	virtual void OnUpdate();
	virtual void OnRender();
	std::shared_ptr<GameObject> GetGameObject();
	std::shared_ptr<Core> GetCore();
private:
	friend struct GameObject;
	std::weak_ptr<GameObject> parent;
};

