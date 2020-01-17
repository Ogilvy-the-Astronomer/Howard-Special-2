#pragma once
/**
 * An abstract struct that cannot be copied
 */
struct NonCopyable {
protected:
	NonCopyable() {}
	~NonCopyable() {}
private:
	NonCopyable(const NonCopyable &);
	NonCopyable& operator=(const NonCopyable &);

};