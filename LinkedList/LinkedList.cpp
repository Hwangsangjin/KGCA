#include <iostream>
#include "LinkedList.h"

using namespace std;

int main()
{
	LinkedList ll;
	ll.push_back(10);
	ll.push_back(20);
	ll.push_back(30);

	ll.begin();

	auto it = ll.find(20);
	if (it != ll.end())
	{
		ll.insert(it, 50);
	}

	for (auto& i : ll)
	{
		cout << i << " ";
	}
	cout << endl;

	return 0;
}

// 생성자
LinkedList::LinkedList()
{
	// 초기 노드의 갯수
	count = 0;

	// 머리와 꼬리 생성
	head = new Node{ 0, nullptr, nullptr };
	tail = new Node{ 0, nullptr, nullptr };

	// 머리의 다음 노드를 꼬리에 연결
	// 꼬리의 이전 노드를 머리에 연결
	head->next = tail;
	tail->prev = head;
}

// 소멸자
LinkedList::~LinkedList()
{
	// 노드가 비어있지 않다면
	while (!empty())
	{
		// 가장 앞의 노드 삭제
		pop_front();
	}

	// 머리와 꼬리 삭제
	delete head;
	delete tail;
}

// 노드 삽입
void LinkedList::insert(const Iterator& iterator, const int value)
{
	// 반복자의 위치를 노드에 전달
	Node* node = iterator.ptr;

	// 새로운 노드를 생성하고 기존 노드와 연결
	Node* newNode = new Node{ value, node->prev, node };

	// 기존 노드의 다음 노드를 새로 생성한 노드로 변경
	newNode->prev->next = newNode;
	// 기존 노드의 이전 노드를 새로 생성한 노드로 변경
	newNode->next->prev = newNode;

	// 노드 갯수 증가
	count++;
}

// 노드를 앞에 추가
void LinkedList::push_front(int value)
{
	// 머리의 다음 위치를 전달
	insert(begin(), value);
}

// 노드를 뒤에 추가
void LinkedList::push_back(int value)
{
	// 꼬리의 위치를 전달
	insert(end(), value);
}

// 노드 삭제
void LinkedList::erase(const Iterator& iterator)
{
	// 반복자의 위치를 노드에 전달
	Node* node = iterator.ptr;

	// 삭제할 노드의 이전 노드와 다음 노드를 연결
	node->prev->next = node->next;
	node->next->prev = node->prev;
	
	// 삭제할 노드 메모리 해제
	delete node;

	// 노드 갯수 감소
	count--;
}

// 가장 앞의 노드를 삭제
void LinkedList::pop_front()
{
	// 노드가 비어있지 않다면
	if (!empty())
	{
		// 머리의 다음 노드를 삭제
		erase(begin());
	}
}

// 가장 뒤의 노드를 삭제
void LinkedList::pop_back()
{
	// 노드가 비어있지 않다면
	if (!empty())
	{
		// 꼬리의 이전 노드를 삭제
		erase(--end());
	}
}

// 노드가 비었는지 확인
bool LinkedList::empty() const
{
	return count == 0;
}

// 노드의 갯수
int LinkedList::size() const
{
	return count;
}
