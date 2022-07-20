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

// 생성자
template<typename T>
LinkedList<T>::LinkedList()
{
	// 초기 노드의 갯수
	count = 0;

	//// 머리와 꼬리 생성
	head = new Node<T>{ T(), nullptr, nullptr };
	tail = new Node<T>{ T(), nullptr, nullptr };

	//// 머리의 다음 노드를 꼬리에 연결
	//// 꼬리의 이전 노드를 머리에 연결
	head->next = tail;
	tail->prev = head;
}

// 소멸자
template<typename T>
LinkedList<T>::~LinkedList()
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
template<typename T>
void LinkedList<T>::insert(const Iterator& iterator, const T& value)
{
	// 반복자의 위치를 노드에 전달
	Node<T>* node = iterator.ptr;

	// 새로운 노드를 생성하고 기존 노드와 연결
	Node<T>* newNode = new Node<T>{ value, node->prev, node };

	// 기존 노드의 다음 노드를 새로 생성한 노드로 변경
	newNode->prev->next = newNode;
	// 기존 노드의 이전 노드를 새로 생성한 노드로 변경
	newNode->next->prev = newNode;

	// 노드 갯수 증가
	count++;
}

// 노드를 앞에 추가
template<typename T>
void LinkedList<T>::push_front(const T& value)
{
	// 머리의 다음 위치를 전달
	insert(begin(), value);
}

// 노드를 뒤에 추가
template<typename T>
void LinkedList<T>::push_back(const T& value)
{
	// 꼬리의 위치를 전달
	insert(end(), value);
}

// 노드 삭제
template<typename T>
void LinkedList<T>::erase(const Iterator& iterator)
{
	// 반복자의 위치를 노드에 전달
	Node<T>* node = iterator.ptr;

	// 삭제할 노드의 이전 노드와 다음 노드를 연결
	node->prev->next = node->next;
	node->next->prev = node->prev;

	// 삭제할 노드 메모리 해제
	delete node;

	// 노드 갯수 감소
	count--;
}

// 가장 앞의 노드를 삭제
template<typename T>
void LinkedList<T>::pop_front()
{
	// 노드가 비어있지 않다면
	if (!empty())
	{
		// 머리의 다음 노드를 삭제
		erase(begin());
	}
}

// 가장 뒤의 노드를 삭제
template<typename T>
void LinkedList<T>::pop_back()
{
	// 노드가 비어있지 않다면
	if (!empty())
	{
		// 꼬리의 이전 노드를 삭제
		erase(--end());
	}
}

// 모든 노드 삭제
template<typename T>
void LinkedList<T>::clear()
{
	// 삭제할 임시 노드 생성
	Node<T>* temp = nullptr;
	// 머리의 다음 노드부터 이동할 노드 생성
	Node<T>* current = head->next;

	// 현재 노드가 꼬리가 아닌 동안
	while (current != tail)
	{
		// 임시 노드에 현재 노드로 설정
		temp = current;
		// 현재 노드를 다음 노드로 변경
		current = current->next;
		// 임시 노드 삭제
		delete temp;

		// 노드 갯수 감소
		count--;
	}

	// 머리의 다음 노드를 꼬리에 연결
	// 꼬리의 이전 노드를 머리에 연결
	head->next = tail;
	tail->prev = head;
}

// 노드가 비었는지 확인
template<typename T>
bool LinkedList<T>::empty() const
{
	return count == 0;
}

// 노드의 갯수
template<typename T>
int LinkedList<T>::size() const
{
	return count;
}
