#pragma once
#include <exception>
#include <string>
/**
 * std::exception expansion which allows for string messages
 */
struct Exception : public std::exception {
public:
	Exception(std::string message);
	~Exception() throw();

	//const char *what();
private:
	std::string message;

};