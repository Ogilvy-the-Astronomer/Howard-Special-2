#include <iostream>
#include <HowardSpecial2/HowardSpecial2.h>
#include "TriangleRenderer.h"


int main(){
	std::shared_ptr<Core> core = core->Initialize();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	core->mainCamera = core->AddObject();
	core->mainCamera->AddComponent<Camera>();

	std::shared_ptr<GameObject> object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>("../src/game/models/fighter.obj", "../src/game/textures/fighter.png");
	//rend->window = core->window; //REMOVE

	//std::shared_ptr<GameObject> triangle = core->AddObject();
	//triangle->AddComponent<TriangleRenderer>();
	
	for (int i = 0; i < 1000; i++) {
		core->Update();
		core->Display();
	}

	core->Stop();
	return 0;
}