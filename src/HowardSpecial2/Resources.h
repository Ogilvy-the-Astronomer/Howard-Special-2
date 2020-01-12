#include "Resource.h"
#include <vector>
#include <memory>
/**
 * List of resources meant to help manage them
 */
struct Resources {
	std::vector<std::shared_ptr<Resource>> resources; ///< list of resources
	template<class T>
	std::shared_ptr<T> load(std::string path); ///< template function for loading different resources
};

template<class T>
inline std::shared_ptr<T> Resources::load(std::string path){
	for (int i = 0; i < (int)resources.size(); i++) { //check if a resource already exists at this path 
		if (resources.at(i)->path == path) {
			std::shared_ptr<T> rtn;
			if (rtn = std::static_pointer_cast<T>(resources.at(i))) {
				return rtn;
			}
		}
	}
	std::shared_ptr<T> rtn = std::make_shared<T>(); //if not create a new one and at it to the list 
	rtn->path = path;
	
	rtn->load(path);
	resources.push_back(rtn);
	return rtn;

}
