#include <iostream>
#include <HowardSpecial2/HowardSpecial2.h>
#include "TriangleRenderer.h"


int main(){
	std::shared_ptr<Core> core = core->Initialize();
	std::shared_ptr<GameObject> cam = core->AddObject();
	core->mainCamera = cam->AddComponent<Camera>();

	std::shared_ptr<GameObject> object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>("../src/game/textures/fighter.obj", "../src/game/textures/fighter.png");
	//triangle->AddComponent<TriangleRenderer>();
	
	for (int i = 0; i < 1000; i++) {
		core->Update();
	}

	core->Stop();
	return 0;
}