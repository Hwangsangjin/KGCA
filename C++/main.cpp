#include <iostream>
#include <Tree.h>

int main()
{
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