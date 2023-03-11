#pragma once
#include<vector>
#include<string>
#include"Operator.h"
#include "Logger.h"
class Function {
private:
	Logger* log = NULL;
	std::vector<Operator*> body_of_function;
	std::vector<Variable*> all_variables;
	std::string name;
	void notify(std::string msg);
public:
	Function(std::string name, Logger* log) :name(name), log(log) {};
	int variable_exist(std::string name);
	Variable* get_variable(int index);
	void add_operator(Operator* op);
	void add_variable(Variable* var);
	std::string get_name();
	std::string run(int& current_index, Stack* stack, bool& is_extern);

};