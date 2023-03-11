#include "Variable.h"

int Variable::get_value()
{
	return value;
}
std::string Variable::get_name()
{
	return name;
}
void Variable::set_value(int v)
{
	value = v;
	return;
}