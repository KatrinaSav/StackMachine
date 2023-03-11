#pragma once
#include<string>
#include <iostream>
class Logger
{
public:
	void print_log(std::string messege)
	{
		std::cout << "LOG: " << messege << std::endl;
	}
};