#pragma once
#include <memory>

struct GameObject;
struct Core;
/**
 * a virtual component for other components to inherit from 
 */
struct Component {
	virtual void OnUpdate(float _deltaT); ///< update function called every frame
	virtual void OnRender();
	virtual void OnStart(); ///<start function called at the beginning of the game loop
	std::shared_ptr<GameObject> GetGameObject(); ///< get the gameobject the component is attached to
	std::shared_ptr<Core> GetCore(); ///< get the core
private:
	friend struct GameObject;
	std::weak_ptr<GameObject> parent; ///< reference to the gameobject the component is attached to
};

