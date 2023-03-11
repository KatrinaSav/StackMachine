#pragma once
#include<string>
class Variable {
private:
	std::string name;
	int value = -1;
public:
	Variable(std::string name) :name(name) {};

	int get_value();
	
	std::string get_name();
	
	void set_value(int v);

};