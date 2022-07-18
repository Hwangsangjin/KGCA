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
	// ��尡 ������� �ʴٸ�
	while (!empty())
	{
		// ž ��� ����
		pop();
	}

	// ž ��� ����
	delete head;
}

// ��� �߰�
void Stack::push(int value)
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
int Stack::top() const
{
	return head->data;
}

// ����� ����
int Stack::size() const
{
	return count;
}

// ��尡 ������� Ȯ��
bool Stack::empty() const
{
	return count == 0;
}
