#include "Function.h"


void Function::notify(std::string msg)
{
	if (this->log != NULL)
	{
		this->log->print_log(msg);
	}
	return;
}

int Function::variable_exist(std::string name)
{
	for (int i = 0; i < all_variables.size(); i++)
	{
		if (all_variables[i]->get_name() == name)
		{ 
			
			return i;
		}	
	}

	return -1;
}
Variable* Function::get_variable(int index)
{
	
	return all_variables[index];
}
void Function::add_operator(Operator* op)
{
	this->body_of_function.push_back(op);

	return;
}
void Function::add_variable(Variable* var)
{
	this->all_variables.push_back(var);
	
	return;
}
std::string Function::get_name()
{
	return this->name;
}

std::string Function::run(int& current_index, Stack* stack, bool& is_extern)
{
	
	Logger* log =NULL;
	Return* r = new Return(log);
	Call* c = new Call("name", log);
	Callext* ce = new Callext("name", log);
	Goto* g = new Goto("name", log);
	Ifgr* gr = new Ifgr("name", log);
	Ifeq* eq = new Ifeq("name", log);
	const type_info& type_return = typeid(*r);
	const type_info& type_call = typeid(*c);
	const type_info& type_callext = typeid(*ce);
	const type_info& type_goto = typeid(*g);
	const type_info& type_ifeq = typeid(*eq);
	const type_info& type_ifgr = typeid(*gr);
	delete r, c, g, eq, gr, ce;
	for (int i = current_index; i < body_of_function.size(); i++)
	{
		const type_info& current_type = typeid(*body_of_function[i]);
		if (current_type == type_call)
		{
			Call* operat = dynamic_cast<Call*> (body_of_function[i]);
			operat->action(stack);
			current_index = i + 1;
			is_extern = false;
			return operat->get_name();
		}
		else if (current_type == type_callext)
		{
			Callext* operat = dynamic_cast<Callext*> (body_of_function[i]);
			operat->action(stack);
			current_index = i + 1;
			is_extern = true;
			return operat->get_name();
		}
		else if (current_type == type_goto)
		{
			Goto* operat = dynamic_cast<Goto*> (body_of_function[i]);
			operat->action(this->body_of_function, stack, i);
		}
		else if (current_type == type_ifeq)
		{
			Ifeq* operat = dynamic_cast<Ifeq*> (body_of_function[i]);
			operat->action(this->body_of_function, stack, i);
		}
		else if (current_type == type_ifgr)
		{
			Ifgr* operat = dynamic_cast<Ifgr*> (body_of_function[i]);
			operat->action(this->body_of_function, stack, i);
		}
		else if (current_type == type_return)
		{
			Return* operat = dynamic_cast<Return*> (body_of_function[i]);
			operat->action(stack);
			return "";
		}
		else
		{
			body_of_function[i]->action(stack);
		}


	}
	//exeption not return
}