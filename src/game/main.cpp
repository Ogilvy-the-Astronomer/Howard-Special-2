#include <iostream>
#include "../HowardSpecial2/Core.h"
#include "TriangleRenderer.h"


int main(){
	std::shared_ptr<Core> core = std::make_shared<Core>();
	core->Start();
	std::shared_ptr<GameObject> triangle = core->AddObject();
	std::shared_ptr<TriangleRenderer> triRend = triangle->AddComponent<TriangleRenderer>();
	triRend->window = core->window;
	
	for (int i = 0; i < 1000; i++) {
		core->Update();
	}

	//std::cin.get();
	core->Stop();
	return 0;
}