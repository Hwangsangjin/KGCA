#pragma once

// ���
template <typename T>
struct Node
{
	T data;
	Node* next;
};

// ����
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

// ������
template <typename T>
Stack<T>::Stack()
{
	// �ʱ� ����� ����
	count = 0;

	// ž ��� ����
	top = new Node<T>{ T(), nullptr };
}

// �Ҹ���
template <typename T>
Stack<T>::~Stack()
{
	// ž ��� ����
	delete top;
}

// ��� �߰�
template <typename T>
void Stack<T>::push(const T& value)
{
	// ���ο� ��带 �����ϰ� ž ���� ����
	Node* newNode = new Node{ value, head };

	// ž ��带 ���� ������ ���� ����
	head = newNode;

	// ��� ���� ����
	count++;
}

// ��� ����
template <typename T>
void Stack<T>::pop()
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
template <typename T>
const T& Stack<T>::top() const
{
	return head->data;
}

// ��尡 ������� Ȯ��
template <typename T>
bool Stack<T>::empty() const
{
	return count == 0;
}

// ����� ����
template <typename T>
int Stack<T>::size() const
{
	return count;
}
