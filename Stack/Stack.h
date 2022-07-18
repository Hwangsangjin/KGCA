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

	void push(const int value);
	void pop();
	const int top() const;

	bool empty() const;
	int size() const;
};
