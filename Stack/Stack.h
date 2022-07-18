#pragma once

class Stack
{
private:
	struct Node
	{
		int data;
		Node* next;
	};

	int count;
	Node* head;

public:
	Stack();
	~Stack();

	void push(int value);
	void pop();

	int top() const;

	int size() const;

	bool empty() const;
};