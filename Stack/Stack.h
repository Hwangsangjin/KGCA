#pragma once

#include <LinkedList.h>

// 스택
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

// 노드 추가
template <typename T>
inline void Stack<T>::push(const T& e)
{
	list.push_back(e);
}

// 노드 삭제
template <typename T>
inline void Stack<T>::pop()
{
	list.pop_back();
}

// 마지막 노드의 데이터
template <typename T>
inline const T& Stack<T>::top() const
{
	return list.back();
}

// 노드가 비었는지 확인
template <typename T>
inline bool Stack<T>::empty() const
{
	return list.empty();
}

// 노드의 갯수
template <typename T>
inline int Stack<T>::size() const
{
	return list.size();
}
