#pragma once

template<typename T>
struct Node
{
	T data;
	Node* prev;
	Node* next;
};

template<typename T>
class LinkedList
{
private:
	class Iterator
	{
	private:
		Node<T>* ptr;

	public:
		Iterator() : ptr(nullptr) {}
		Iterator(Node<T>* node) : ptr(node) {}

		T& operator*()
		{
			return ptr->data;
		}

		Iterator& operator++()
		{
			ptr = ptr->next;
			return *this;
		}

		Iterator& operator++(int)
		{
			Iterator temp = *this;
			ptr = ptr->next;
			return temp;
		}

		Iterator& operator--()
		{
			ptr = ptr->prev;
			return *this;
		}

		Iterator& operator--(int)
		{
			Iterator temp = *this;
			ptr = ptr->prev;
			return temp;
		}

		bool operator==(const Iterator& iterator) const
		{
			return ptr == iterator.ptr;
		}

		bool operator!=(const Iterator& iterator) const
		{
			return ptr != iterator.ptr;
		}

		friend class LinkedList;
	};

	size_t count;
	Node<T>* head = nullptr;
	Node<T>* tail = nullptr;

public:
	LinkedList();
	~LinkedList();

	Iterator begin() const { return Iterator(head->next); }
	Iterator end() const { return Iterator(tail); }

	void insert(const Iterator& iterator, const T& value);
	void push_front(const T& value);
	void push_back(const T& value);

	Iterator find(const T& value) const
	{
		Node<T>* current = head->next;

		while (current->data != value && current != tail)
		{
			current = current->next;
		}

		return current;
	}

	void erase(const Iterator& iterator);
	void pop_front();
	void pop_back();
	void clear();

	bool empty() const;

	int size() const;
};

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
