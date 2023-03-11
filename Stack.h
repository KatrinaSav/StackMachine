#pragma once
#include<vector>
#include<fstream>
#include<string>
class Stack {
private:
	struct Node
	{
		int content;
		Node* next;
	};
	Node* top = NULL;
public:
	Stack() {}
	bool is_empty();
	
	void push(int x);
	
	int pop();

	int peek();
	
	void print();

};