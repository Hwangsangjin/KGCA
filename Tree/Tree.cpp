#include <iostream>
#include <queue>

// 노드
struct Node
{
	char data;
	Node* left;
	Node* right;

	Node(char d) : data(d), left(nullptr), right(nullptr) {}
};

// 전위 순회
void preorder(Node* node)
{
	if (node)
	{
		std::cout << node->data << " ";
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
		std::cout << node->data << " ";
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
		std::cout << node->data << " ";
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

	return 0;
}