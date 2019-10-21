#include <iostream>
#include "../HowardSpecial2/Core.h"
#include "../HowardSpecial2/GameObject.h"
#include "../HowardSpecial2/TriangleRenderer.h"


int main(){
	std::shared_ptr<Core> core = std::make_shared<Core>();
	GameObject triangle;
	triangle.AddComponent<TriangleRenderer>();
	triangle.Update();
	std::cin.get();

	return 0;
}