#include <memory>

struct Component {
	Component();
	virtual void OnUpdate();
	virtual void OnDisplay();
};

struct TestComp : Component {
	void OnUpdate();
	void OnDisplay();

};

class NonCopyable{
protected:
	NonCopyable(){}
	~NonCopyable(){}
private:
	NonCopyable(const NonCopyable &);
	NonCopyable& operator=(const NonCopyable &);
}