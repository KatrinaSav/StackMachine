#include "Operator.h"
#include "Exeption.h"


void Operator::notify(std::string msg)
{
	if (this->log != NULL)
	{
		this->log->print_log(msg);
	}
	return;
}
void Label::action(Stack* stack)
{
	return;
}
std::string Label::get_name()
{
	return this->name; 
}

void Operator_with_param::action(Stack* stack)
{
	return;
}

void  Operator_with_label::set_index(std::vector<Operator*> func)
{
	Logger* log = NULL;
	Label* lab = new Label("name", log);
	const type_info& type_label = typeid(*lab);
	delete lab;
	for (int i = 0; i < func.size(); i++)
	{
		if (typeid(*func[i]) == type_label)
		{
			Label* l = dynamic_cast<Label*> (func[i]);
			if (l->get_name() == this->name)
			{
				this->index = i;
			}
		}
	}
	if (index == -1)
	{
		throw LabelNotFoundException(this->name);
	}
}


void Push::action(Stack* stack)
{
	if (this->is_var)
	{
		if (this->var->get_value() == -1)
		{
			throw VarIsEmptyException();
		}
		else
		{
			stack->push(this->var->get_value());
			this->notify("Push " + std::to_string(this->var->get_value()) + "\n");
			return;
		}
	}
	else
	{
		stack->push(this->constant);
		this->notify("Push " + std::to_string(this->constant) + "\n");
		return;
	}
}




void Peek::action(Stack* stack)
{
	
	int x = stack->peek();
	this->var->set_value(x);
	this->notify("Variable "+ this->var->get_name()+" set value " + std::to_string(x) + "\n");
	return;
}



void Pop::action(Stack* stack)
{
	if (this->var == NULL)
	{
		int value = stack->pop();
		this->notify("Pop " + std::to_string(value) + " from the top\n");
		return;
	}
	else
	{
		this->var->set_value(stack->pop());
		this->notify("Pop " + std::to_string(this->var->get_value()) + " from the top and used as value for variable "+ this->var->get_name()+"\n");
		return;
	}
}



void Add::action(Stack* stack)
{
	int a = stack->pop();
	int b = stack->pop();
	stack->push(a + b);
	this->notify("Add " + std::to_string(a) + " to " + std::to_string(b) + ".\n");
	return;
}



void Div::action(Stack* stack)
{
	int b = stack->pop();
	int a = stack->pop();
	if (b == 0)
	{
		throw DivisionByZeroException();
	}
	stack->push(a / b);
	this->notify("Divide " + std::to_string(a) + " on " + std::to_string(b) + ".\n");
	return;
}



void Mul::action(Stack* stack)
{
	int a = stack->pop();
	int b = stack->pop();
	stack->push(a * b);
	this->notify("Multiply " + std::to_string(a) + " with " + std::to_string(b) + ".\n");
	return;
}

void Return::action(Stack* stack)
{
	this->notify("Return from function \n");
	return;
}


void Dup::action(Stack* stack)
{
	int a = stack->peek();
	stack->push(a);
	this->notify("Duplicate " + std::to_string(a) + "\n");
	return;
}

void Sub::action(Stack* stack)
{
	int a = stack->pop();
	int b = stack->pop();
	if (b - a < 0)
		stack->push(0);
	else
		stack->push(b - a);
	this->notify("Substract " + std::to_string(a) + " from " + std::to_string(b) + ".\n");
	return;
}


void Goto::action(std::vector<Operator*> func, Stack* stack, int& index)
{
	if (this->index == -1)
		this->set_index(func);
	index = this->index;

	return;
}
void Goto::action(Stack* stack)
{
	return;
}


void Ifeq::action(std::vector<Operator*> func, Stack* stack, int& index)
{
	if (this->index == -1)
		this->set_index(func);
	int a = stack->pop();
	int b = stack->pop();
	this->notify("Compare number " + std::to_string(a) + " to number " + std::to_string(b) + ".\n");
	if (a == b)
	{
		index = this->index;
		this->notify("Numbers are equal.\n");
	}

	return;

}
void Ifeq::action(Stack* stack)
{
	return;
}

void Ifgr::action(Stack* stack)
{
	return;
}
void Ifgr::action(std::vector<Operator*> func, Stack* stack, int& index)
{
	if (this->index == -1)
		this->set_index(func);
	int a = stack->pop();
	int b = stack->pop();
	this->notify("Compare number " + std::to_string(a) + " to number " + std::to_string(b) + ".\n");
	if (b > a)
	{
		index = this->index;
		this->notify("Greater.\n");
	}
	return;

}

void Call::action(Stack* stack)
{
	this->notify("Call function "+this->get_name()+"\n");
	return;
}
std::string Call::get_name()
{
	return this->name_of_function;
}
void Callext::action(Stack* stack)
{
	this->notify("Call external function " + this->get_name() + "\n");
	return;
}
std::string Callext::get_name()
{
	return this->name_of_function;
}