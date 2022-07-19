#pragma once

#include <iostream>

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
public:
	class Iterator
	{
	public:
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
