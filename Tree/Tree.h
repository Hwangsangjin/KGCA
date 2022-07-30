#include <iostream>

// ���� Ž�� Ʈ��
class BinarySearchTree
{
private:
	// ���
	struct Node
	{
		int data;
		Node* left;
		Node* right;

		Node(char d) : data(d), left(nullptr), right(nullptr) {}
	};

	Node* root = nullptr;

	// ���� ����
	void insert_impl(Node* current, int value)
	{
		// ���� �Ϸ��� �����Ͱ� ���� ����� �����ͺ��� ���� ���
		if (value < current->data)
		{
			// ���� ����� ���� �ڽ��� ����ִ� ���
			if (!current->left)
			{
				// ���ο� ���� ��� ����
				current->left = new Node(value);
			}
			// ���� ����� ���� �ڽ��� �ִ� ���
			else
			{
				// ���� ����� ���� �ڽĺ��� �����͸� ������ ���� ã�Ƽ� �߰�
				insert_impl(current->left, value);
			}
		}
		// ���� �Ϸ��� �����Ͱ� ���� ����� �����ͺ��� ū ���
		else
		{
			// ���� ����� ������ �ڽ��� ����ִ� ���
			if (!current->right)

			{	// ���ο� ������ ��� ����
				current->right = new Node(value);
			}
			// ���� ����� ������ �ڽ��� �ִ� ���
			else
			{
				// ���� ����� ������ �ڽĺ��� �����͸� ������ ���� ã�Ƽ� �߰�
				insert_impl(current->right, value);
			}
		}
	}
	// Ž�� ����
	Node* find_impl(Node* current, int value)
	{
		// ���� ��尡 ����ִ� ���
		if (current == nullptr)
		{
			// �������� ��ȯ
			return nullptr;
		}

		// ã�� ���� ���� ����� �����Ϳ� ���� ���
		if (value == current->data)
		{
			// ���� ����� ������ ��ȯ
			return current;
		}
		else
		{
			// ã�� ���� ���� ����� ������ ���� ���� ���
			if (value < current->data)
			{
				// ���� ����� ���� �ڽĺ��� �����͸� Ž��
				return find_impl(current->left, value);
			}
			// ã�� ���� ���� ����� ������ ���� ū ���
			else
			{
				// ���� ����� ������ �ڽĺ��� �����͸� Ž��
				return find_impl(current->right, value);
			}
		}
	}
	// ���� ��ȸ ��� ����
	void inorder_impl(Node* current)
	{
		// ���� ��尡 �����ϴ� ���
		if (current)
		{
			// ���� ����� ���� �ڽ� ��ȸ
			inorder_impl(current->left);
			// ���� ����� ������ ���
			std::cout << current->data << " ";
			// ���� ����� ������ �ڽ� ��ȸ
			inorder_impl(current->right);
		}
	}

	// ��� ���� �� �θ� ��尡 �����Ͱ� �����Ѿ� �� ����� �ּҸ� ��ȯ
	Node* erase_impl(Node* node, int value)
	{
		// ��尡 ���� ���
		if (!node)
		{
			// �������� ��ȯ
			return nullptr;
		}

		// �����Ϸ��� ���� ���� ����� Ű�� ���� ���� ���
		if (value < node->data)
		{
			// ���� ���� Ʈ���� �̵��ؼ� ����
			node->left = erase_impl(node->left, value);
		}
		// �����Ϸ��� ���� ���� ����� Ű�� ���� ū ���
		else if (value > node->data)
		{
			// ������ ���� Ʈ���� �̵��ؼ� ����
			node->right = erase_impl(node->right, value);
		}
		else
		{
			// �ڽ� ��尡 �� �� �ִ� ���
			if (node->left && node->right)
			{
				// ���� ����� �ļ� ��带 ����
				auto succ = successor(node);
				// ���� ����� ������ ���� �ļ� ����� ������ ������ ����
				node->data = succ->data;
				// ���� ����� ������ �ڽĺ��� �ļ� ��带 ã�Ƽ� ����
				node->right = erase_impl(node->right, succ->data);
			}
			// �ڽ� ��尡 ���� ���ų�, ���� �ڽĸ� �ִ� ���
			else
			{
				// ���� ����� ���� �ڽ��� �ִ� ��� ���� �ڽ� ����� �����͸� ��ȯ
				// ���� ��� ������ �ڽ� ����� �����͸� ��ȯ
				// �� �� ���� ��� �������� ��ȯ
				auto temp = node->left ? node->left : node->right;
				delete node;

				return temp;
			}
		}

		// ���� ��尡 �������� ���� ���
		return node;
	}
	// �ļ� ��� ã��
	Node* successor(Node* node)
	{
		// ���� ����� ������ �ڽ� ��带 ����
		auto curr = node->right;
		// ���� ����� ���� �ڽ��� �������Ͱ� �ƴҶ� ����
		while (curr && curr->left)
		{
			curr = curr->left;
		}
		// ���� ����� ������ ��ȯ
		return curr;
	}

public:
	// �Ҹ���
	~BinarySearchTree()
	{
		delete_node(root);
	}

	// ���ο� ������ �߰�
	void insert(int value)
	{
		// ���� ��Ʈ ��尡 �������� ���� ���
		if (!root)
		{
			// ��� ��ü ����
			root = new Node(value);
		}
		// ��Ʈ ��尡 �����ϴ� ���
		else
		{
			// ��Ʈ ������ �����͸� ������ ���� ã�Ƽ� �߰�
			insert_impl(root, value);
		}
	}

	// ������ Ž��
	Node* find(int value)
	{
		return find_impl(root, value);
	}

	// ���� ��ȸ ���
	void inorder()
	{
		inorder_impl(root);
	}

	// ���� ��ȸ ������� ��� ����
	void delete_node(Node* node)
	{
		// ��尡 �ִ� ���
		if (node)
		{
			// ����� ���� �ڽ� ����
			delete_node(node->left);
			// ����� ������ �ڽ� ����
			delete_node(node->right);

			// ��� �޸� ���� �� ��������
			delete node;
			node = nullptr;
		}
	}

	// ������ ����
	void erase(int value)
	{
		root = erase_impl(root, value);
	}
};
