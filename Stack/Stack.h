#pragma once

class Stack
{
private:
	struct Node
	{
		int data;
		Node* next;
	};

	int count;
	Node* head;

public:
	Stack();
	~Stack();

	void push(const int value);
	void pop();
	const int top() const;

	bool empty() const;
	int size() const;
};

// ������
Stack::Stack()
{
	// �ʱ� ����� ����
	count = 0;

	// ž ��� ����
	head = new Node{ 0, nullptr };
}

// �Ҹ���
Stack::~Stack()
{
	// ž ��� ����
	delete head;
}

// ��� �߰�
void Stack::push(const int value)
{
	// ���ο� ��带 �����ϰ� ž ���� ����
	Node* newNode = new Node{ value, head };

	// ž ��带 ���� ������ ���� ����
	head = newNode;

	// ��� ���� ����
	count++;
}

// ��� ����
void Stack::pop()
{
	// ž ��尡 ������ ����
	if (head->next == nullptr)
	{
		return;
	}

	// �ӽ� ��带 �����ϰ� ž ���� ����
	Node* temp = head;
	// ž ��带 ���� ���� ����
	head = head->next;

	// ž ��� �޸� ����
	delete temp;

	// ��� ���� ����
	count--;
}

// ž ���
const int Stack::top() const
{
	return head->data;
}

// ��尡 ������� Ȯ��
bool Stack::empty() const
{
	return count == 0;
}

// ����� ����
int Stack::size() const
{
	return count;
}
