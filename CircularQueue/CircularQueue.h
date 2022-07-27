#pragma once

#include <iostream>

#define MAX_QUEUE 10

// ȯ�� ť
template <typename T>
class CircularQueue
{
private:
	T* arr;
	int front_idx;
	int rear_idx;
	int count;
	int capacity;

public:
	CircularQueue(int sz = MAX_QUEUE);
	~CircularQueue();

	void enqueue(const T& e);
	void dequeue();

	const T& front() const;

	bool empty() const;
	int full() const;
	int size() const;
};

// ������
template<typename T>
inline CircularQueue<T>::CircularQueue(int sz)
{
	arr = new T[sz];
	front_idx = 0;
	rear_idx = -1;
	count = 0;
	capacity = sz;
}

// �Ҹ���
template<typename T>
inline CircularQueue<T>::~CircularQueue()
{
	delete[] arr;
}

// ���� �߰�
template<typename T>
inline void CircularQueue<T>::enqueue(const T& e)
{
	// �뷮�� á���� �����÷ο� �߻�
	if (full())
	{
		std::cout << "Overflow error!" << std::endl;
		return;
	}

	rear_idx = (rear_idx + 1) % capacity;
	arr[rear_idx] = e;
	count++;
}

// ���� ����
template<typename T>
inline void CircularQueue<T>::dequeue()
{
	// ���Ұ� ������ ����÷ο� �߻�
	if (empty())
	{
		std::cout << "Underflow error!" << std::endl;
		return;
	}

	front_idx = (front_idx + 1) % capacity;
	count--;
}

// ���� ���� ���� Ȯ��
template<typename T>
inline const T& CircularQueue<T>::front() const
{
	return arr[front_idx];
}

// ���Ұ� ������� Ȯ��
template<typename T>
inline bool CircularQueue<T>::empty() const
{
	return count == 0;
}

// �뷮�� á���� Ȯ��
template<typename T>
inline int CircularQueue<T>::full() const
{
	return count == capacity;
}

// ������ ����
template<typename T>
inline int CircularQueue<T>::size() const
{
	return count;
}
