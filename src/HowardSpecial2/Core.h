#include "Component.h"
struct Core : private NonCopyable {
	Core();
	~Core();
private:
	void Start();
	void Stop();


};