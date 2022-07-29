#include <iostream>
#include <queue>

// 노드
struct Node
{
	int data;
	Node* left;
	Node* right;

	Node(char d) : data(d), left(nullptr), right(nullptr) {}
};

// 이진 탐색 트리
class BinarySearchTree
{
private:
	Node* root = nullptr;

	void insert_impl(Node* current, int value)
	{
		if (value < current->data)
		{
			if (!current->left)
			{
				current->left = new Node(value);
			}
			else
			{
				insert_impl(current->left, value);
			}
		}
		else
		{
			if (!current->right)
			{
				current->right = new Node(value);
			}
			else
			{
				insert_impl(current->right, value);
			}
		}
	}
	Node* find_impl(Node* current, int value)
	{
		if (current == nullptr)
		{
			return nullptr;
		}

		if (value == current->data)
		{
			return current;
		}
		else
		{
			if (value < current->data)
			{
				return find_impl(current->left, value);
			}
			else
			{
				return find_impl(current->right, value);
			}
		}
	}
	void inorder_impl(Node* current)
	{
		if (current != nullptr)
		{
			inorder_impl(current->left);
			std::cout << current->data << " ";
			inorder_impl(current->right);
		}
	}
	// 노드 삭제후, 부모 노드가 포인터가 가리켜야 할 노드의 주소를 반환
	Node* erase_impl(Node* node, int value)
	{
		if (!node)
		{
			return nullptr;
		}

		if (value < node->data)
		{
			node->left = erase_impl(node->left, value);
		}
		else if (value > node->data)
		{
			node->right = erase_impl(node->right, value);
		}
		else
		{
			// 자식 노드가 둘 다 있는 경우
			if (node->left && node->right)
			{
				auto succ = successor(node);
				node->data = succ->data;
				node->right = erase_impl(node->right, succ->data);
			}
			// 자식 노드가 전혀 없거나, 한쪽 자식만 있는 경우
			else
			{
				auto temp = node->left ? node->left : node->right;
				delete node;

				return temp;
			}
		}

		return node;
	}
	// 후속 노드 찾기
	Node* successor(Node* node)
	{
		auto curr = node->right;

		while (curr && curr->left)
		{
			curr = curr->left;
		}

		return curr;
	}

public:
	~BinarySearchTree()
	{
		delete_node(root);
	}

	void insert(int value)
	{
		if (!root)
		{
			root = new Node(value);
		}
		else
		{
			insert_impl(root, value);
		}
	}
	Node* find(int value)
	{
		return find_impl(root, value);
	}
	void inorder()
	{
		inorder_impl(root);
	}

	void erase(int value)
	{
		root = erase_impl(root, value);
	}

	void delete_node(Node* node)
	{
		if (node)
		{
			delete_node(node->left);
			delete_node(node->right);
			delete node;
			node = nullptr;
		}
	}


};

// 전위 순회
void preorder(Node* node)
{
	if (node)
	{
		std::cout << static_cast<char>(node->data) << " ";
		preorder(node->left);
		preorder(node->right);
	}
}

// 중위 순회
void inorder(Node* node)
{
	if (node)
	{
		inorder(node->left);
		std::cout << static_cast<char>(node->data) << " ";
		inorder(node->right);
	}
}

// 후위 순회
void postorder(Node* node)
{
	if (node)
	{
		postorder(node->left);
		postorder(node->right);
		std::cout << static_cast<char>(node->data) << " ";
	}
}

// 레벨 순서 순회
void levelorder(Node* node)
{
	std::queue<Node*> q;
	q.push(node);

	while (!q.empty())
	{
		auto current = q.front();
		q.pop();

		std::cout << current->data << " ";

		if (current->left)
		{
			q.push(current->left);
		}

		if (current->right)
		{
			q.push(current->right);
		}
	}
}

// 노드 삭제
void delete_node(Node* node)
{
	if (node)
	{
		delete_node(node->left);
		delete_node(node->right);
		delete node;
		node = nullptr;
	}
}

int main()
{
	/*
		A
	  B   C
	 D E	F
	*/

	Node* root = new Node('A');
	root->left = new Node('B');
	root->right = new Node('C');
	root->left->left = new Node('D');
	root->left->right = new Node('E');
	root->right->right = new Node('F');

	preorder(root);
	std::cout << std::endl;

	inorder(root);
	std::cout << std::endl;

	postorder(root);
	std::cout << std::endl;

	levelorder(root);
	std::cout << std::endl;

	delete_node(root);

	BinarySearchTree bst;
	bst.insert(10);
	bst.insert(14);
	bst.insert(5);
	bst.insert(7);
	bst.insert(18);
	bst.insert(4);
	bst.insert(6);
	bst.insert(20);
	bst.insert(16);
	bst.inorder();
	std::cout << std::endl;

	if (bst.find(7))
	{
		std::cout << "7 is found" << std::endl;
	}
	else
	{
		std::cout << "7 is not found" << std::endl;
	}

	if (bst.find(15))
	{
		std::cout << "15 is found" << std::endl;
	}
	else
	{
		std::cout << "15 is not found" << std::endl;
	}

	bst.insert(9);
	bst.insert(12);
	bst.inorder();
	std::cout << std::endl;

	bst.erase(4);
	bst.erase(5);
	bst.erase(14);
	bst.inorder();
	std::cout << std::endl;

	bst.insert(15);
	bst.erase(10);
	bst.inorder();
	std::cout << std::endl;

	return 0;
}