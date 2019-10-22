#pragma once
#include <memory>

struct Component {
	//Component();
	virtual void OnUpdate();
	virtual void OnRender();
};

