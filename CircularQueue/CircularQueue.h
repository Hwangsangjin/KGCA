#pragma once

#include <iostream>

#define MAX_QUEUE 10

// 환형 큐
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

// 생성자
template<typename T>
inline CircularQueue<T>::CircularQueue(int sz)
{
	arr = new T[sz];
	front_idx = 0;
	rear_idx = -1;
	count = 0;
	capacity = sz;
}

// 소멸자
template<typename T>
inline CircularQueue<T>::~CircularQueue()
{
	delete[] arr;
}

// 원소 추가
template<typename T>
inline void CircularQueue<T>::enqueue(const T& e)
{
	// 용량이 찼으면 오버플로우 발생
	if (full())
	{
		std::cout << "Overflow error!" << std::endl;
		return;
	}

	rear_idx = (rear_idx + 1) % capacity;
	arr[rear_idx] = e;
	count++;
}

// 원소 삭제
template<typename T>
inline void CircularQueue<T>::dequeue()
{
	// 원소가 없으면 언더플로우 발생
	if (empty())
	{
		std::cout << "Underflow error!" << std::endl;
		return;
	}

	front_idx = (front_idx + 1) % capacity;
	count--;
}

// 가장 앞의 원소 확인
template<typename T>
inline const T& CircularQueue<T>::front() const
{
	return arr[front_idx];
}

// 원소가 비었는지 확인
template<typename T>
inline bool CircularQueue<T>::empty() const
{
	return count == 0;
}

// 용량이 찼는지 확인
template<typename T>
inline int CircularQueue<T>::full() const
{
	return count == capacity;
}

// 원소의 갯수
template<typename T>
inline int CircularQueue<T>::size() const
{
	return count;
}
