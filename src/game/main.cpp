#include <iostream>
#include "../HowardSpecial2/Core.h"
#include "../HowardSpecial2/TriangleRenderer.h"


int main(){
	std::shared_ptr<Core> core = std::make_shared<Core>();
	core->Start();
	//std::shared_ptr<GameObject> triangle = core->AddObject();
	//triangle->AddComponent<TriangleRenderer>();
	//triangle->Update();
	std::cin.get();
	core->Stop();
	return 0;
}