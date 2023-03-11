#include "Program.h"
#include "Exeption.h"



Program::Program(Logger* log)
{
	external_functions = new std::map<std::string, std::function<void(Stack*)>>;
	this->log = log;
}
Program::~Program()
{
	delete external_functions;
}
void Program::add_extern_func(std::string functionName, std::function<void(Stack*)> function)
{
	external_functions->insert(std::pair<std::string, std::function<void(Stack*)>>(functionName, function));
	return;
}
bool Program::is_number(std::string S) {
	std::string temp = "0123456789";
	bool answer;
	for (int i = 0; i < S.length(); i++)
	{
		answer = false;
		for (int j = 0; j < temp.length(); j++)
		{
			if (S[i] == temp[j])
				answer = true;
		}
		if (answer == false)
			return false;
	}
	return answer;
}

bool Program::is_token(std::string str) {
	bool exist = false;
	for (int i = 0; i < 6; i++)
	{
		if (str == this->tokens[i])
			exist = true;
	}
	return exist;
}
bool Program::is_token_param(std::string str) {
	bool exist = false;
	for (int i = 0; i < 8; i++)
	{
		if (str == this->tokens_param[i])
			exist = true;
	}
	return exist;
}

void Program::lexer(std::string file) {
	enum state { reading_token, reading_param, searching_function, reading_function, reading_name_of_function, waiting_parant };
	std::fstream f(file);
	bool is_variable;
	std::string current_value;
	std::string current_variable;
	char now;
	bool last_step_pop= false;
	state st = searching_function;
	while (!f.eof())
	{
		f.get(now);
		if (now == '#')
		{
			std::string comment;
			getline(f, comment);
			continue;
		}
		switch (st)
		{
		case reading_token:
		{
			if (now == ' ' || now == '\n')
			{
				if (current_value == "}")
				{
					st = searching_function;
					current_value = "";
					break;
				}
				if (current_value == "pop" && now == '\n')
				{
					Pop* operat = new Pop(log);
					this->all_functions[this->all_functions.size() - 1].add_operator(operat);
					current_value = "";
					current_variable = "";
					st = reading_token;
					break;
				}
				if (current_value == "")
					break;
				bool need_param;
				if (is_token(current_value))
					need_param = false;
				else if (is_token_param(current_value))
					need_param = true;
				else if (current_value[current_value.size() - 1] == ':')
				{
					current_value.erase(current_value.size() - 1, 1);
					Label* operat = new Label(current_value, log);
					this->all_functions[this->all_functions.size() - 1].add_operator(operat);
					current_value = "";
					break;
				}
				else
				{
					throw SyntaxErrorException();
				}
				if (need_param)
				{
					st = reading_param;
				}
				else
				{
					if (current_value == "dup")
					{
						Dup* operat = new Dup(log);
						this->all_functions[this->all_functions.size() - 1].add_operator(operat);
					}
					else if (current_value == "add")
					{
						Add* operat = new Add(log);
						this->all_functions[this->all_functions.size() - 1].add_operator(operat);
					}
					else if (current_value == "sub")
					{
						Sub* operat = new Sub(log);
						this->all_functions[this->all_functions.size() - 1].add_operator(operat);
					}
					else if (current_value == "div")
					{
						Div* operat = new Div(log);
						this->all_functions[this->all_functions.size() - 1].add_operator(operat);
					}
					else if (current_value == "mul")
					{
						Mul* operat = new Mul(log);
						this->all_functions[this->all_functions.size() - 1].add_operator(operat);
					}
					else if (current_value == "return")
					{
						Return* operat = new Return(log);
						this->all_functions[this->all_functions.size() - 1].add_operator(operat);
					}
					current_value = "";
				}
			}
			else
			{
				current_value += now;
			}
		}
		break;
		case reading_param:
		{
			if (now == ' ' && current_variable != "")
			{
				std::string comment;
				getline(f, comment);
				for (int i = 0; i < comment.length(); i++)
				{
					if (comment[i] == ' ')
						continue;
					else if (comment[i] == '#')
						break;
					else 
						throw SyntaxErrorException();
				}
			}
			if (now == '\n' || now == ' ')
			{
				if (current_variable == "")
				{
					throw SyntaxErrorException();
				}
				else if (current_value == "push")
				{
					if (is_number(current_variable))
					{
						Push* operat = new Push(stoi(current_variable), log);
						this->all_functions[this->all_functions.size() - 1].add_operator(operat);
					}
					else
					{
						int check = all_functions[this->all_functions.size() - 1].variable_exist(current_variable);
						if (check == -1)
						{
							Variable* var = new Variable(current_variable);
							this->all_functions[this->all_functions.size() - 1].add_variable(var);
							Push* operat = new Push(var, log);
							this->all_functions[this->all_functions.size() - 1].add_operator(operat);
						}
						else
						{
							Variable* var = this->all_functions[this->all_functions.size() - 1].get_variable(check);
							Push* operat = new Push(var, log);
							this->all_functions[this->all_functions.size() - 1].add_operator(operat);
						}
					}
				}
				else if (current_value == "peek")
				{
					if (is_number(current_variable))
					{
						Peek* operat = new Peek(stoi(current_variable), log);
						this->all_functions[this->all_functions.size() - 1].add_operator(operat);
					}
					else
					{
						int check = all_functions[this->all_functions.size() - 1].variable_exist(current_variable);
						if (check == -1)
						{
							Variable* var = new Variable(current_variable);
							this->all_functions[this->all_functions.size() - 1].add_variable(var);
							Peek* operat = new Peek(var, log);
							this->all_functions[this->all_functions.size() - 1].add_operator(operat);
						}
						else
						{
							Variable* var = this->all_functions[this->all_functions.size() - 1].get_variable(check);
							Peek* operat = new Peek(var, log);
							this->all_functions[this->all_functions.size() - 1].add_operator(operat);
						}
					}

				}
				else if (current_value == "pop")
				{
					int check = all_functions[this->all_functions.size() - 1].variable_exist(current_variable);
						if (check == -1)
						{
							Variable* var = new Variable(current_variable);
							this->all_functions[this->all_functions.size() - 1].add_variable(var);
							Pop* operat = new Pop(var, log);
							this->all_functions[this->all_functions.size() - 1].add_operator(operat);
						}
						else
						{
							Variable* var = this->all_functions[this->all_functions.size() - 1].get_variable(check);
							Pop* operat = new Pop(var, log);
							this->all_functions[this->all_functions.size() - 1].add_operator(operat);
						}
				}
				else if (current_value == "goto")
				{
					Goto* operat = new Goto(current_variable, log);
					this->all_functions[this->all_functions.size() - 1].add_operator(operat);
				}
				else if (current_value == "call")
				{
					Call* operat = new Call(current_variable, log);
					this->all_functions[this->all_functions.size() - 1].add_operator(operat);
				}
				else if (current_value == "ifeq")
				{
					Ifeq* operat = new Ifeq(current_variable, log);
					this->all_functions[this->all_functions.size() - 1].add_operator(operat);
				}
				else if (current_value == "ifgr")
				{
					Ifgr* operat = new Ifgr(current_variable, log);
					this->all_functions[this->all_functions.size() - 1].add_operator(operat);
				}
				else if (current_value == "callext")
				{
				   Callext* operat = new Callext(current_variable, log);
				   this->all_functions[this->all_functions.size() - 1].add_operator(operat);
				}
				current_value = "";
				current_variable = "";
				st = reading_token;
			}
			else
				current_variable += now;
		}
		break;
		case searching_function:
		{
			if (now == ' ')
			{
				if (current_value == "function")
				{
					st = reading_name_of_function;
				}
				else {
					throw SyntaxErrorException();
				}
				current_value = "";
			}
			else if (now == '\n')
				break;
			else {
				current_value += now;
			}
		}
		break;
		case reading_name_of_function:
		{
			if (now == '{')
			{
				st = reading_token;
				current_value = "";

			}
			else if (now == ' ' || now == '\n')
			{
				Function A(current_value,log);
				this->all_functions.push_back(A);
				if (current_value == "main")
					this->index_of_main = this->all_functions.size() - 1;
				st = waiting_parant;
				current_value = "";
			}
			else
			{
				current_value += now;
			}
		}
		break;
		case waiting_parant:
		{
			if (now == '{')
				st = reading_token;
			else
			{
				throw SyntaxErrorException();
			}
		}
		break;
		default:
			break;
		}

	}
	if (st != searching_function)
	{
		throw SyntaxErrorException();
	}
}
int Program::get_index_of_main()
{
	if (this->index_of_main == -1)
	{
		throw NoMainFunctionException();
	}
	else
	return this->index_of_main;
}
void Program::run(int index, Stack* stack) 
{
		int func_index, index_in = 0;
		bool is_extern = false;
		std::string name_of_function = "";
	continue_process:
		name_of_function = all_functions[index].run(index_in, stack,is_extern);
		if (name_of_function == "")
			return;
		else if (is_extern)
		{
			std::function<void(Stack*)> ext_func = find_extern_function(name_of_function);
			ext_func(stack);
			goto continue_process;
		}
		else
		{
			func_index = find_function(name_of_function);
			this->run(func_index, stack);
			goto continue_process;
		}

	
}

int Program::find_function(std::string name_of_function)
{
	for (int i = 0; i < all_functions.size(); i++)
	{
		if (all_functions[i].get_name() == name_of_function)
		{
			return i;
		}
	}
	throw FunctionNotFoundException(name_of_function);
}

std::function<void(Stack*)> Program::find_extern_function(std::string name_of_function)
{
	if (external_functions->find(name_of_function) == external_functions->end())
	{
		
		throw FunctionNotFoundException(name_of_function);
	}

	
	return external_functions->find(name_of_function)->second;
	
	
}