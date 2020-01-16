#pragma once
#include <exception>
#include <string>

struct Exception : public std::exception {
public:
	Exception(std::string message);
	~Exception() throw();

	//const char *what();
private:
	std::string message;

};