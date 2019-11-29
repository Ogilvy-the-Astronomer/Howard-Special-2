#include "Resource.h"
#include <vector>
#include <memory>
struct Resources {
	std::vector<std::shared_ptr<Resource>> resources;
	template<class T>
	std::shared_ptr<T> load(std::string path);
};

template<class T>
inline std::shared_ptr<T> Resources::load(std::string path){
	std::shared_ptr<T> rtn = std::make_shared<T>();
	rtn->path = path;
	// core
	rtn->load(path);
	resources.push_back(rtn);
	return rtn;

}
