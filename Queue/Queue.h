#pragma once

#include <LinkedList.h>

// ť
template <typename T>
class Queue
{
private:
	LinkedList<T> list;

public:
	Queue() {}

	void enqueue(const T& e);
	void denqueue();
	const T& front() const;
	
	bool empty() const;
	int size() const;
};

// ��� �߰�
template<typename T>
void Queue<T>::enqueue(const T& e)
{
	list.push_back(e);
}

// ��� ����
template<typename T>
void Queue<T>::denqueue()
{
	list.pop_front();
}

// ù ��° ����� ������
template<typename T>
const T& Queue<T>::front() const
{
	return list.front();
}

// ��尡 ������� Ȯ��
template<typename T>
bool Queue<T>::empty() const
{
	return list.empty();
}

// ����� ����
template<typename T>
int Queue<T>::size() const
{
	return list.size();
}
