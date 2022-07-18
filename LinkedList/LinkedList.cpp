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

// ������
LinkedList::LinkedList()
{
	// �ʱ� ����� ����
	count = 0;

	// �Ӹ��� ���� ����
	head = new Node{ 0, nullptr, nullptr };
	tail = new Node{ 0, nullptr, nullptr };

	// �Ӹ��� ���� ��带 ������ ����
	// ������ ���� ��带 �Ӹ��� ����
	head->next = tail;
	tail->prev = head;
}

// �Ҹ���
LinkedList::~LinkedList()
{
	// ��尡 ������� �ʴٸ�
	while (!empty())
	{
		// ���� ���� ��� ����
		pop_front();
	}

	// �Ӹ��� ���� ����
	delete head;
	delete tail;
}

// ��� ����
void LinkedList::insert(const Iterator& iterator, const int value)
{
	// �ݺ����� ��ġ�� ��忡 ����
	Node* node = iterator.ptr;

	// ���ο� ��带 �����ϰ� ���� ���� ����
	Node* newNode = new Node{ value, node->prev, node };

	// ���� ����� ���� ��带 ���� ������ ���� ����
	newNode->prev->next = newNode;
	// ���� ����� ���� ��带 ���� ������ ���� ����
	newNode->next->prev = newNode;

	// ��� ���� ����
	count++;
}

// ��带 �տ� �߰�
void LinkedList::push_front(int value)
{
	// �Ӹ��� ���� ��ġ�� ����
	insert(begin(), value);
}

// ��带 �ڿ� �߰�
void LinkedList::push_back(int value)
{
	// ������ ��ġ�� ����
	insert(end(), value);
}

// ��� ����
void LinkedList::erase(const Iterator& iterator)
{
	// �ݺ����� ��ġ�� ��忡 ����
	Node* node = iterator.ptr;

	// ������ ����� ���� ���� ���� ��带 ����
	node->prev->next = node->next;
	node->next->prev = node->prev;
	
	// ������ ��� �޸� ����
	delete node;

	// ��� ���� ����
	count--;
}

// ���� ���� ��带 ����
void LinkedList::pop_front()
{
	// ��尡 ������� �ʴٸ�
	if (!empty())
	{
		// �Ӹ��� ���� ��带 ����
		erase(begin());
	}
}

// ���� ���� ��带 ����
void LinkedList::pop_back()
{
	// ��尡 ������� �ʴٸ�
	if (!empty())
	{
		// ������ ���� ��带 ����
		erase(--end());
	}
}

// ��尡 ������� Ȯ��
bool LinkedList::empty() const
{
	return count == 0;
}

// ����� ����
int LinkedList::size() const
{
	return count;
}
