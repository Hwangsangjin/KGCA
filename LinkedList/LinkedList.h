#pragma once

class LinkedList
{
private:
	struct Node
	{
		int data;
		Node* prev;
		Node* next;
	};

	class Iterator
	{
	private:
		Node* ptr;

	public:
		Iterator() : ptr(nullptr) {}
		Iterator(Node* node) : ptr(node) {}

		int& operator*()
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

	int count;
	Node* head;
	Node* tail;

public:
	LinkedList();
	~LinkedList();

	Iterator begin() const { return Iterator(head->next); }
	Iterator end() const { return Iterator(tail); }

	void insert(const Iterator& iterator, const int value);
	void push_front(int value);
	void push_back(int value);

	Iterator find(const int now) const
	{
		Node* current = head->next;

		while (current->data != now && current != tail)
		{
			current = current->next;
		}

		return current;
	}

	void erase(const Iterator& iterator);
	void pop_front();
	void pop_back();

	bool empty() const;

	int size() const;
};