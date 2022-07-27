#pragma once

#include <LinkedList.h>

// 큐
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

// 노드 추가
template<typename T>
inline void Queue<T>::enqueue(const T& e)
{
	list.push_back(e);
}

// 노드 삭제
template<typename T>
inline void Queue<T>::denqueue()
{
	list.pop_front();
}

// 첫 번째 노드의 데이터
template<typename T>
inline const T& Queue<T>::front() const
{
	return list.front();
}

// 노드가 비었는지 확인
template<typename T>
inline bool Queue<T>::empty() const
{
	return list.empty();
}

// 노드의 갯수
template<typename T>
inline int Queue<T>::size() const
{
	return list.size();
}
