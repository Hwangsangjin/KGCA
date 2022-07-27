#pragma once

// ����
template <typename T>
class Stack
{
private:
	// ���
	template <typename T>
	struct Node
	{
		T data;
		Node<T>* next;
	};

	size_t count;
	Node<T>* topNode;

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
	topNode = new Node<T>{ T(), nullptr };
}

// �Ҹ���
template <typename T>
Stack<T>::~Stack()
{
	// ž ��� ����
	delete topNode;
}

// ��� �߰�
template <typename T>
void Stack<T>::push(const T& value)
{
	// ���ο� ��带 �����ϰ� ž ���� ����
	Node<T>* newNode = new Node<T>{ value, topNode };

	// ž ��带 ���� ������ ���� ����
	topNode = newNode;

	// ��� ���� ����
	count++;
}

// ��� ����
template <typename T>
void Stack<T>::pop()
{
	// ž ��尡 ������ ����
	if (topNode->next == nullptr)
	{
		return;
	}

	// �ӽ� ��带 �����ϰ� ž ���� ����
	Node<T>* temp = topNode;
	// ž ��带 ���� ���� ����
	topNode = topNode->next;

	// ž ��� �޸� ����
	delete temp;

	// ��� ���� ����
	count--;
}

// ž ���
template <typename T>
const T& Stack<T>::top() const
{
	return topNode->data;
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
