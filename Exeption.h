#pragma once

#include <string>

class LabelNotFoundException : public std::exception
{
public:
	
	LabelNotFoundException(std::string labelName)
		: _message("There is no label \"" + labelName + "\".\n"){}

	
	virtual ~LabelNotFoundException() noexcept {}

	const char* what() const noexcept
	{
		return _message.c_str();
	}
private:
	const std::string _message;
};

class DivisionByZeroException : public std::exception
{
public:

	DivisionByZeroException(){}
	

	virtual ~DivisionByZeroException() noexcept {}

	const char* what() const noexcept
	{
		return _message.c_str();
	}
private:
	const std::string _message = "Division by zero.\n";
};

class StackIsEmptyException : public std::exception
{
public:

	StackIsEmptyException() {}


	virtual ~StackIsEmptyException() noexcept {}

	const char* what() const noexcept
	{
		return _message.c_str();
	}
private:
	const std::string _message = "There is no element in stack.\n";
};

class FunctionNotFoundException : public std::exception
{
public:

	FunctionNotFoundException(std::string functionName)
		: _message("There is no function \"" + functionName + "\".\n") {}


	virtual ~FunctionNotFoundException() noexcept {}

	const char* what() const noexcept
	{
		return _message.c_str();
	}
private:
	const std::string _message;
};

class SyntaxErrorException : public std::exception
{
public:

	SyntaxErrorException() {}


	virtual ~SyntaxErrorException() noexcept {}

	const char* what() const noexcept
	{
		return _message.c_str();
	}
private:
	const std::string _message = "There is a syntax error.\n";
};

class VarIsEmptyException : public std::exception
{
public:

	VarIsEmptyException() {}


	virtual ~VarIsEmptyException() noexcept {}

	const char* what() const noexcept
	{
		return _message.c_str();
	}
private:
	const std::string _message = "Variable has no value.\n";
};

class NoMainFunctionException : public std::exception
{
public:

	NoMainFunctionException() {}


	virtual ~NoMainFunctionException() noexcept {}

	const char* what() const noexcept
	{
		return _message.c_str();
	}
private:
	const std::string _message = "Function \"main\" is not founded.\n";
};