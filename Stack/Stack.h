#pragma once

#include <LinkedList.h>

// ����
template <typename T>
class Stack
{
private:
	LinkedList<T> list;

public:
	Stack() {}

	void push(const T& e);
	void pop();
	const T& top() const;

	bool empty() const;
	int size() const;
};

// ��� �߰�
template <typename T>
void Stack<T>::push(const T& e)
{
	list.push_back(e);
}

// ��� ����
template <typename T>
void Stack<T>::pop()
{
	list.pop_back();
}

// ������ ����� ������
template <typename T>
const T& Stack<T>::top() const
{
	return list.back();
}

// ��尡 ������� Ȯ��
template <typename T>
bool Stack<T>::empty() const
{
	return list.empty();
}

// ����� ����
template <typename T>
int Stack<T>::size() const
{
	return list.size();
}
