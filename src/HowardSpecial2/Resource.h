#pragma once
#include <string>
struct Resource {
	friend struct Resources;
protected:
	std::string path;
};