#include <iostream>
#include "../HowardSpecial2/Core.h"
#include "TriangleRenderer.h"


int main(){
	std::shared_ptr<Core> core = std::make_shared<Core>();
	core->Start();
	std::shared_ptr<GameObject> triangle = core->AddObject();
	triangle->AddComponent<TriangleRenderer>();

	std::shared_ptr<VertexBuffer> colors = std::make_shared<VertexBuffer>();
	colors->add(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	colors->add(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
	colors->add(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

	std::shared_ptr<TriangleRenderer> triRend2 = triangle->GetComponent<TriangleRenderer>();
	triRend2->shape->SetBuffer("in_Color", colors);
	
	for (int i = 0; i < 1000; i++) {
		core->Update();
	}

	//std::cin.get();
	core->Stop();
	return 0;
}