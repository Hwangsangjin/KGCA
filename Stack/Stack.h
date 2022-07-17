#pragma once

struct Node
{
	int data;
	Node* next;
};

class Stack
{
private:
	int count;
	Node* head;

public:
	Stack();
	~Stack();

	void push(int value);
	void pop();

	int top();

	int size();
	bool empty();
};