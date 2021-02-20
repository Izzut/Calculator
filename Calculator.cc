#include "Calculator.h"
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <cctype>

using namespace std;

Calculator::~Calculator()
{
	list<Register *>::iterator it;
	for (it = existing_registers.begin(); it != existing_registers.end(); ++it)
	{
		delete (*it);
	}
}

void Calculator::run_from_terminal()
{
	cout << "Welcome to the calculator!\n";
	do
	{
		get_command();
		execute_command();
	} while (first_arg != "quit");
}

void Calculator::run_from_file(string filename)
{
	int current_line = 1;
	do
	{
		get_file_command(filename, current_line);
		current_line++;
		execute_command();
	} while (first_arg != "quit");
}


bool Calculator::is_string_alphanumeric(string string_input) const
{
	return all_of(string_input.begin(), string_input.end(), [](char c){return isalnum(c);});
}

bool Calculator::is_string_number(string string_input) const
{
	return all_of(string_input.begin(), string_input.end(), [](int i){return isdigit(i);});
}

void Calculator::get_command()
{
	first_arg = "";
	second_arg = "";
	third_arg = "";
	string additional_arg;

	string input;
	getline(cin, input);
	istringstream input_stream{input};

	input_stream >> first_arg;
	input_stream >> second_arg;
	input_stream >> third_arg;
	input_stream >> additional_arg;

	if (!additional_arg.empty())
		cerr << "Too many arguments was entered, some will be ignored" << endl;

	transform(first_arg.begin(), first_arg.end(), first_arg.begin(), ::tolower);
	transform(second_arg.begin(), second_arg.end(), second_arg.begin(), ::tolower);
	transform(third_arg.begin(), third_arg.end(), third_arg.begin(), ::tolower);
}

void Calculator::get_file_command(string filename, int current_line)
{
	first_arg = "";
	second_arg = "";
	third_arg = "";
	string additional_arg;
	
	string input;
	ifstream current_file (filename);
	if (current_file.is_open())
	{
		for (int i = 0; i < current_line; ++i)
		{
			if (current_file.eof()){
				current_file.close();
				first_arg = "quit";
				return;
			}
			getline(current_file, input);
		}
	}
	else{
		cerr << "Unable to open file" << endl;
		first_arg = "quit";
	}
	current_file.close();

	istringstream input_stream{input};

	input_stream >> first_arg;
	input_stream >> second_arg;
	input_stream >> third_arg;
	input_stream >> additional_arg;

	if (!additional_arg.empty())
		cerr << "Too many arguments was entered, some will be ignored" << endl;

	transform(first_arg.begin(), first_arg.end(), first_arg.begin(), ::tolower);
	transform(second_arg.begin(), second_arg.end(), second_arg.begin(), ::tolower);
	transform(third_arg.begin(), third_arg.end(), third_arg.begin(), ::tolower);
}

//If adding register to register, we want to avoid 'a add b' and then 'b add a'
//Also checks so we dont add the register to itself
bool Calculator::sanity_check(Register* first_reg, Register* third_reg)
{
	if (first_reg->name == third_reg->name){
		cout << "You cannot add a register to istelf" << endl;
		return false;
	}
	list<Operation *>::iterator it;
	for (it = third_reg->components.begin(); it != third_reg->components.end(); ++it)
	{
		if((*it)->reg != nullptr && (*it)->reg->name == first_reg->name){
			cout << "This action would create an endless loop and is not allowed" << endl;
			return false;
		}
	}
	//returns true if sanity check is ok
	return true;
}

void Calculator::create_operation_from_register(Register* first_reg, Register* third_reg)
{
	if (second_arg == "add")
	{
		Add_Operation *new_op = new Add_Operation(third_reg);
		first_reg->add_component(new_op);
		return;
	}
	if (second_arg == "subtract")
	{
		Sub_Operation *new_op = new Sub_Operation(third_reg);
		first_reg->add_component(new_op);
		return;
	}
	if (second_arg == "multiply")
	{
		Mult_Operation *new_op = new Mult_Operation(third_reg);
		first_reg->add_component(new_op);
		return;
	}
}

void Calculator::create_operation_from_value(Register* first_reg, int new_value)
{
	if (second_arg == "add")
	{
		Add_Operation *new_op = new Add_Operation(new_value);
		first_reg->add_component(new_op);
		return;
	}
	if (second_arg == "subtract")
	{
		Sub_Operation *new_op = new Sub_Operation(new_value);
		first_reg->add_component(new_op);
		return;
	}
	if (second_arg == "multiply")
	{
		Mult_Operation *new_op = new Mult_Operation(new_value);
		first_reg->add_component(new_op);
		return;
	}
}

bool Calculator::do_operation_on_register()
{
	//Does the first argument already exist as a register?
	list<Register *>::iterator it;
	for (it = existing_registers.begin(); it != existing_registers.end(); ++it)
	{
		if ((*it)->name == first_arg)
		{
			//if found, check if the third argument is also a register
			list<Register *>::iterator it2;
			for (it2 = existing_registers.begin(); it2 != existing_registers.end(); ++it2)
			{
				//If third argument is found as a register, add it to the first register
				if (third_arg == (*it2)->name)
				{
					if (sanity_check((*it), (*it2)))
						create_operation_from_register((*it),(*it2));
					return true;
				}
			}
			//If the third argument is not found as an existing register, check if it is a number
			if (is_string_number(third_arg))
			{
				int new_value = stoi(third_arg);
				create_operation_from_value((*it), new_value);
				return true;
			}
			//if the third argument is not found in existing register and it is not a number,
			//it must be a new register, create it
			else
			{
				Register *new_reg = new Register();
				new_reg->assign_name(third_arg);
				existing_registers.push_back(new_reg);
				if (sanity_check((*it), new_reg))
					create_operation_from_register((*it),new_reg);
				return true;
			}
		}
	}
	//The first argument was not found in the existing registers
	return false;
}

void Calculator::execute_command()
{
	if (first_arg == "quit")
	{
		if (!second_arg.empty())
			cerr << "Additional arguments where entered after quit, ignoring those" << endl;
		return;
	}
	if (first_arg == "print")
	{
		if (!third_arg.empty())
			cerr << "Too many arguments after print, ignoring some" << endl;
		//look for register amoung existing registers
		if (is_string_alphanumeric(second_arg))
		{
			list<Register *>::iterator it;
			for (it = existing_registers.begin(); it != existing_registers.end(); ++it)
			{
				if ((*it)->name == second_arg)
				{
					cout << (*it)->get_value() << endl;
					return;
				}
			}
			//if no register is found create a new one
			//print will then return the default value of 0
			Register *new_reg = new Register();
			new_reg->assign_name(second_arg);
			existing_registers.push_back(new_reg);
			cout << new_reg->get_value() << endl;
			return;
		}
		else
			cerr << "Only alphanumreic names for registers are accepted as arguments, please try again" << endl;
	}
	if ((second_arg == "add" || second_arg == "subtract" || second_arg == "multiply") && !third_arg.empty())
	{
		if (is_string_alphanumeric(first_arg) && 
			(is_string_alphanumeric(third_arg) || is_string_number(third_arg)))
		{
			//try to do the operation on the first argument, returns true if the first argument exists as a register
			if (do_operation_on_register())
				return;
			//if the first argument did not exist as a register, create it and the run the same function again
			Register *new_reg = new Register();
			new_reg->assign_name(first_arg);
			existing_registers.push_back(new_reg);
			if (do_operation_on_register())
				return;
			else{
				cerr << "This should not happen, something whent wrong with the calculator" << endl;
				return;
			}
		}
		else{
			cerr << "Only positive integer values and alphanumreic names for registers are accepted as arguments, please try again" << endl;
			return;
		}
	}
	else
		cerr << "The arguments entred was not recognized as a valid command, please try again" << endl;
}