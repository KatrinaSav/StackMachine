#pragma once
#include<string>
#include"Stack.h"
#include"Variable.h"
#include "Logger.h"
class Operator {
protected:
	Logger* log = NULL;
	void notify(std::string msg);
public:
	Operator(Logger* log) : log(log) {};
	virtual void action(Stack* stack) = 0;
};


class Label : public Operator {
private:
	std::string name;
public:
	Label(std::string name,Logger* log) :Operator(log),name(name) {}
	std::string get_name();
	void action(Stack* stack)  override;
};


class Operator_with_param :public Operator {
protected:
	int constant;
	bool is_var;
	Variable* var = NULL;
public:
	virtual void action(Stack* stack);
	Operator_with_param(int c, Logger* log) :Operator(log),constant(c), is_var(false){}
	Operator_with_param(Variable* var, Logger* log):Operator(log),var(var),is_var(true){}
	Operator_with_param(Logger* log) :Operator(log){}
};

class Operator_with_label : public Operator {
protected:
	std::string name;
	int index = -1;
	void set_index(std::vector<Operator*> func);

public:

	virtual void action(std::vector<Operator*> func, Stack* stack, int& index) = 0;
	Operator_with_label(std::string name, Logger* log):Operator(log), name(name){}
	
};


class Push : public Operator_with_param {

public:
	void action(Stack* stack)  override;
	Push(int c, Logger* log) :Operator_with_param(c, log) {};
	Push(Variable* var, Logger* log): Operator_with_param(var, log) {};
};





class Peek : public Operator_with_param {

public:
	void action(Stack* stack)  override;
	Peek(int c, Logger* log) :Operator_with_param(c, log) {};
	Peek(Variable* var, Logger* log) :Operator_with_param(var, log) {};
};



class Pop : public Operator_with_param {

public:
	void action(Stack* stack)  override;
	Pop(Variable* var, Logger* log) :Operator_with_param(var, log) {};
	Pop(Logger* log) :Operator_with_param(log) {};
};


class Add : public Operator {
public:
	Add(Logger* log) :Operator(log) {};
	void action(Stack* stack)  override;
};


class Div : public Operator {
public:

	Div(Logger* log) :Operator(log) {};
	void action(Stack* stack)  override;
};


class Mul : public Operator {
public:
	Mul(Logger* log) :Operator(log) {};
	void action(Stack* stack)  override;
};

class Return : public Operator {
public:
	Return(Logger* log) :Operator(log) {};
	void action(Stack* stack)  override;
};

class Dup : public Operator {
public:
	Dup(Logger* log) :Operator(log) {};
	void action(Stack* stack)  override;
};



class Sub : public Operator {
public:
	Sub(Logger* log) :Operator(log) {};
	void action(Stack* stack)  override;
};


class Goto : public Operator_with_label {
private:
	void action(Stack* stack)  override;
public:
	Goto(std::string name, Logger* log) :Operator_with_label(name, log) {};
	void action(std::vector<Operator*> func, Stack* stack, int& index)  override;

};

class Ifeq : public Operator_with_label {
private:
	void action(Stack* stack)  override;
public:
	Ifeq(std::string name, Logger* log) :Operator_with_label(name, log) {};

	void action(std::vector<Operator*> func, Stack* stack, int& index)  override;
};


class Ifgr : public Operator_with_label {
private:
	void action(Stack* stack)  override;
public:
	Ifgr(std::string name, Logger* log) :Operator_with_label(name, log) {};

	void action(std::vector<Operator*> func, Stack* stack, int& index)  override;
};

class Call : public Operator {
private:
	std::string name_of_function;
public:
	Call(std::string name, Logger* log): Operator(log), name_of_function(name){};

	std::string get_name();
	
	void action(Stack* stack)  override;
};

class Callext : public Operator {
private:
	std::string name_of_function;
public:
	Callext(std::string name, Logger* log) :Operator(log),name_of_function(name) {};

	std::string get_name();

	void action(Stack* stack)  override;
};

