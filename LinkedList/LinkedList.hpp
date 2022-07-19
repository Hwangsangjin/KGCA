#include "LinkedList.h"

// ������
template<typename T>
LinkedList<T>::LinkedList()
{
	// �ʱ� ����� ����
	count = 0;

	//// �Ӹ��� ���� ����
	head = new Node<T>{ T(), nullptr, nullptr };
	tail = new Node<T>{ T(), nullptr, nullptr };

	//// �Ӹ��� ���� ��带 ������ ����
	//// ������ ���� ��带 �Ӹ��� ����
	head->next = tail;
	
	tail->prev = head;
}

// �Ҹ���
template<typename T>
LinkedList<T>::~LinkedList()
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
template<typename T>
void LinkedList<T>::insert(const Iterator& iterator, const T& value)
{
	// �ݺ����� ��ġ�� ��忡 ����
	Node<T>* node = iterator.ptr;

	// ���ο� ��带 �����ϰ� ���� ���� ����
	Node<T>* newNode = new Node<T>{ value, node->prev, node };

	// ���� ����� ���� ��带 ���� ������ ���� ����
	newNode->prev->next = newNode;
	// ���� ����� ���� ��带 ���� ������ ���� ����
	newNode->next->prev = newNode;

	// ��� ���� ����
	count++;
}

// ��带 �տ� �߰�
template<typename T>
void LinkedList<T>::push_front(const T& value)
{
	// �Ӹ��� ���� ��ġ�� ����
	insert(begin(), value);
}

// ��带 �ڿ� �߰�
template<typename T>
void LinkedList<T>::push_back(const T& value)
{
	// ������ ��ġ�� ����
	insert(end(), value);
}

// ��� ����
template<typename T>
void LinkedList<T>::erase(const Iterator& iterator)
{
	// �ݺ����� ��ġ�� ��忡 ����
	Node<T>* node = iterator.ptr;

	// ������ ����� ���� ���� ���� ��带 ����
	node->prev->next = node->next;
	node->next->prev = node->prev;

	// ������ ��� �޸� ����
	delete node;

	// ��� ���� ����
	count--;
}

// ���� ���� ��带 ����
template<typename T>
void LinkedList<T>::pop_front()
{
	// ��尡 ������� �ʴٸ�
	if (!empty())
	{
		// �Ӹ��� ���� ��带 ����
		erase(begin());
	}
}

// ���� ���� ��带 ����
template<typename T>
void LinkedList<T>::pop_back()
{
	// ��尡 ������� �ʴٸ�
	if (!empty())
	{
		// ������ ���� ��带 ����
		erase(--end());
	}
}

// ��� ��� ����
template<typename T>
void LinkedList<T>::clear()
{
	// ������ �ӽ� ��� ����
	Node<T>* temp = nullptr;
	// �Ӹ��� ���� ������ �̵��� ��� ����
	Node<T>* current = head->next;

	// ���� ��尡 ������ �ƴ� ����
	while (current != tail)
	{
		// �ӽ� ��忡 ���� ���� ����
		temp = current;
		// ���� ��带 ���� ���� ����
		current = current->next;
		// �ӽ� ��� ����
		delete temp;

		// ��� ���� ����
		count--;
	}

	// �Ӹ��� ���� ��带 ������ ����
	// ������ ���� ��带 �Ӹ��� ����
	head->next = tail;
	tail->prev = head;
}

// ��尡 ������� Ȯ��
template<typename T>
bool LinkedList<T>::empty() const
{
	return count == 0;
}

// ����� ����
template<typename T>
int LinkedList<T>::size() const
{
	return count;
}
