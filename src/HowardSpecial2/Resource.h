#pragma once
#include <string>
/**
 * a virtual struct for resources to inherit from (meshes, textures, sounds, etc)
 */
struct Resource {
	friend struct Resources;
protected:
	std::string path; ///< path of the resource
};