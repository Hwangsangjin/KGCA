#pragma once

// 노드
template <typename T>
struct Node
{
	T data;
	Node* next;
};

// 스택
template <typename T>
class Stack
{
private:
	int count;
	Node* top;

public:
	Stack();
	~Stack();

	void push(const T& value);
	void pop();
	const T& top() const;

	bool empty() const;
	int size() const;
};

// 생성자
template <typename T>
Stack<T>::Stack()
{
	// 초기 노드의 갯수
	count = 0;

	// 탑 노드 생성
	top = new Node<T>{ T(), nullptr };
}

// 소멸자
template <typename T>
Stack<T>::~Stack()
{
	// 탑 노드 삭제
	delete top;
}

// 노드 추가
template <typename T>
void Stack<T>::push(const T& value)
{
	// 새로운 노드를 생성하고 탑 노드와 연결
	Node* newNode = new Node{ value, head };

	// 탑 노드를 새로 생성한 노드로 변경
	head = newNode;

	// 노드 갯수 증가
	count++;
}

// 노드 삭제
template <typename T>
void Stack<T>::pop()
{
	// 탑 노드가 없으면 종료
	if (head->next == nullptr)
	{
		return;
	}

	// 임시 노드를 생성하고 탑 노드로 설정
	Node* temp = head;
	// 탑 노드를 이전 노드로 변경
	head = head->next;

	// 탑 노드 메모리 해제
	delete temp;

	// 노드 갯수 감소
	count--;
}

// 탑 노드
template <typename T>
const T& Stack<T>::top() const
{
	return head->data;
}

// 노드가 비었는지 확인
template <typename T>
bool Stack<T>::empty() const
{
	return count == 0;
}

// 노드의 갯수
template <typename T>
int Stack<T>::size() const
{
	return count;
}
