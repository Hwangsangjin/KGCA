#include "Stack.h"

int main()
{
	Stack s;

	s.push(1);
	s.push(2);
	s.push(3);

	s.pop();
	s.pop();
	s.pop();

	return 0;
}

// 생성자
Stack::Stack()
{
	// 초기 노드의 갯수
	count = 0;

	// 탑 노드 생성
	head = new Node{ 0, nullptr };
}

// 소멸자
Stack::~Stack()
{
	// 노드가 비어있지 않다면
	while (!empty())
	{
		// 탑 노드 삭제
		pop();
	}

	// 탑 노드 삭제
	delete head;
}

// 노드 추가
void Stack::push(int value)
{
	// 새로운 노드를 생성하고 탑 노드와 연결
	Node* newNode = new Node{ value, head };

	// 탑 노드를 새로 생성한 노드로 변경
	head = newNode;

	// 노드 갯수 증가
	count++;
}

// 노드 삭제
void Stack::pop()
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
int Stack::top() const
{
	return head->data;
}

// 노드의 갯수
int Stack::size() const
{
	return count;
}

// 노드가 비었는지 확인
bool Stack::empty() const
{
	return count == 0;
}
