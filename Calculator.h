#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "Register.h"
#include <list>
#include <string>
#include <fstream>

class Calculator
{
public:
	Calculator() = default;
	~Calculator();
	void run_from_terminal();
	void run_from_file(std::string filename);
private:
	void get_command();
	void get_file_command(std::string filename, int current_line);
	void execute_command();
	void create_operation_from_register(Register* fisrt_reg, Register* third_reg);
	void create_operation_from_value(Register* fisrt_reg, int new_value);
	bool do_operation_on_register();
	bool check_components(Register* old_reg, Register* new_reg);
	bool sanity_check(Register* first_reg, Register* third_reg);
	bool is_string_number(std::string input_string) const;
	bool is_string_alphanumeric(std::string input_string) const;
	std::list<Register*> existing_registers{};
	std::string first_arg;
	std::string second_arg;
	std::string third_arg;
};

#endif
