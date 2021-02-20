#ifndef REGISTER_H
#define REGISTER_H
#include <string>
#include <list>
#include "Operation.h"

class Register
{
public:
	Register() = default;
	~Register(); 
	int get_value();
	void assign_name(std::string input_for_name);
	void add_component(Operation *new_component);
	std::string name{};
	std::list<Operation *> components{};
};

#endif
