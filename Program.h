#pragma once
#include<vector>
#include<fstream>
#include <iostream>
#include<string>
#include <functional>
#include <map>
#include "Function.h"



class Program {
	
private:
	Logger* log =NULL;
	void notify(std::string msg);
	std::vector<Function> all_functions;
	std::map<std::string, std::function<void(Stack*)>>* external_functions;
	std::function<void(Stack*)> find_extern_function(std::string name_of_function);
	int find_function(std::string name_of_function);
	int index_of_main = -1;
	bool is_number(std::string S);
	const std::string tokens[6] = {"dup","add","sub","div","mul","return"};
	const std::string tokens_param[8] = { "goto","push","pop","peek","ifeq","ifgr","call","callext" };
	bool is_token(std::string str);
	bool is_token_param(std::string str);
public:
	Program(Logger* log);
	~Program();
	void add_extern_func(std::string functionName, std::function<void(Stack*)> function);
	void lexer(std::string file);
	int get_index_of_main();
	void run(int index, Stack* stack); 
	
};