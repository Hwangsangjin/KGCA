#include <iostream>

// 이진 탐색 트리
class BinarySearchTree
{
private:
	// 노드
	struct Node
	{
		int data;
		Node* left;
		Node* right;

		Node(char d) : data(d), left(nullptr), right(nullptr) {}
	};

	Node* root = nullptr;

	// 삽입 구현
	void insert_impl(Node* current, int value)
	{
		// 삽입 하려는 데이터가 현재 노드의 데이터보다 작은 경우
		if (value < current->data)
		{
			// 현재 노드의 왼쪽 자식이 비어있는 경우
			if (!current->left)
			{
				// 새로운 왼쪽 노드 생성
				current->left = new Node(value);
			}
			// 현재 노드의 왼쪽 자식이 있는 경우
			else
			{
				// 현재 노드의 왼쪽 자식부터 데이터를 삽입할 곳을 찾아서 추가
				insert_impl(current->left, value);
			}
		}
		// 삽입 하려는 데이터가 현재 노드의 데이터보다 큰 경우
		else
		{
			// 현재 노드의 오른쪽 자식이 비어있는 경우
			if (!current->right)

			{	// 새로운 오른쪽 노드 생성
				current->right = new Node(value);
			}
			// 현재 노드의 오른쪽 자식이 있는 경우
			else
			{
				// 현재 노드의 오른쪽 자식부터 데이터를 삽입할 곳을 찾아서 추가
				insert_impl(current->right, value);
			}
		}
	}
	// 탐색 구현
	Node* find_impl(Node* current, int value)
	{
		// 현재 노드가 비어있는 경우
		if (current == nullptr)
		{
			// 널포인터 반환
			return nullptr;
		}

		// 찾는 값이 현재 노드의 데이터와 같은 경우
		if (value == current->data)
		{
			// 현재 노드의 포인터 반환
			return current;
		}
		else
		{
			// 찾는 값이 현재 노드의 데이터 보다 작은 경우
			if (value < current->data)
			{
				// 현재 노드의 왼쪽 자식부터 데이터를 탐색
				return find_impl(current->left, value);
			}
			// 찾는 값이 현재 노드의 데이터 보다 큰 경우
			else
			{
				// 현재 노드의 오른쪽 자식부터 데이터를 탐색
				return find_impl(current->right, value);
			}
		}
	}
	// 중위 순회 출력 구현
	void inorder_impl(Node* current)
	{
		// 현재 노드가 존재하는 경우
		if (current)
		{
			// 현재 노드의 왼쪽 자식 순회
			inorder_impl(current->left);
			// 현재 노드의 데이터 출력
			std::cout << current->data << " ";
			// 현재 노드의 오른쪽 자식 순회
			inorder_impl(current->right);
		}
	}

	// 노드 삭제 후 부모 노드가 포인터가 가리켜야 할 노드의 주소를 반환
	Node* erase_impl(Node* node, int value)
	{
		// 노드가 없는 경우
		if (!node)
		{
			// 널포인터 반환
			return nullptr;
		}

		// 삭제하려는 값이 현재 노드의 키값 보다 작은 경우
		if (value < node->data)
		{
			// 왼쪽 서브 트리로 이동해서 삭제
			node->left = erase_impl(node->left, value);
		}
		// 삭제하려는 값이 현재 노드의 키값 보다 큰 경우
		else if (value > node->data)
		{
			// 오른쪽 서브 트리로 이동해서 삭제
			node->right = erase_impl(node->right, value);
		}
		else
		{
			// 자식 노드가 둘 다 있는 경우
			if (node->left && node->right)
			{
				// 현재 노드의 후속 노드를 저장
				auto succ = successor(node);
				// 현재 노드의 데이터 값을 후속 노드의 데이터 값으로 복사
				node->data = succ->data;
				// 현재 노드의 오른쪽 자식부터 후속 노드를 찾아서 삭제
				node->right = erase_impl(node->right, succ->data);
			}
			// 자식 노드가 전혀 없거나, 한쪽 자식만 있는 경우
			else
			{
				// 현재 노드의 왼쪽 자식이 있는 경우 왼쪽 자식 노드의 포인터를 반환
				// 없는 경우 오른쪽 자식 노드의 포인터를 반환
				// 둘 다 없는 경우 널포인터 반환
				auto temp = node->left ? node->left : node->right;
				delete node;

				return temp;
			}
		}

		// 현재 노드가 삭제되지 않은 경우
		return node;
	}
	// 후속 노드 찾기
	Node* successor(Node* node)
	{
		// 현재 노드의 오른쪽 자식 노드를 저장
		auto curr = node->right;
		// 현재 노드의 왼쪽 자식이 널포인터가 아닐때 까지
		while (curr && curr->left)
		{
			curr = curr->left;
		}
		// 현재 노드의 포인터 반환
		return curr;
	}

public:
	// 소멸자
	~BinarySearchTree()
	{
		delete_node(root);
	}

	// 새로운 데이터 추가
	void insert(int value)
	{
		// 현재 루트 노드가 존재하지 않을 경우
		if (!root)
		{
			// 노드 객체 생성
			root = new Node(value);
		}
		// 루트 노드가 존재하는 경우
		else
		{
			// 루트 노드부터 데이터를 삽입할 곳을 찾아서 추가
			insert_impl(root, value);
		}
	}

	// 데이터 탐색
	Node* find(int value)
	{
		return find_impl(root, value);
	}

	// 중위 순회 출력
	void inorder()
	{
		inorder_impl(root);
	}

	// 후위 순회 방식으로 노드 삭제
	void delete_node(Node* node)
	{
		// 노드가 있는 경우
		if (node)
		{
			// 노드의 왼쪽 자식 삭제
			delete_node(node->left);
			// 노드의 오른쪽 자식 삭제
			delete_node(node->right);

			// 노드 메모리 해제 및 널포인터
			delete node;
			node = nullptr;
		}
	}

	// 데이터 삭제
	void erase(int value)
	{
		root = erase_impl(root, value);
	}
};
