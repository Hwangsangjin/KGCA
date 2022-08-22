#pragma once

#include "Object.h"

class Node
{
public:
	int _iDepth;
	bool _bLeaf;
	Rect _rect;

	std::vector<Node*> _pChild;
	std::vector<Node*> _pObjects;
	std::vector<Object*> _pStaticObjects;
	std::vector<Object*> _pDynamicObjects;

	Node(Node* pParent, Rect rect);
	virtual ~Node();

	void CreateChildNode(Node* pParent);
};

