
#include <iostream>
#include"Stack.h"
#include "Exeption.h"

bool Stack::is_empty()
{
	if (top == NULL)
		return true;
	else
		return false;
}
void Stack::push(int x)
{
	Node* n = new Node;
	n->content = x;
	if (is_empty())
	{
		top = n;
		top->next = NULL;
		return;
	}
	else
	{
		n->next = top;
		top = n;
		return;
	}
}
int Stack::pop()
{
	if (this->is_empty())
		throw StackIsEmptyException();
	int info;
	info = top->content;
	Node* buf = top->next;
	delete top;
	top = buf;
	return info;
}
int Stack::peek()
{
	if (this->is_empty())
		throw StackIsEmptyException();
	return top->content;
}
void Stack::print()
{
	Node* n = top;
	while (n != NULL)
	{
		std::cout << n->content << std::endl;
		n = n->next;
	}
	return;
}