#pragma once

#include "Node.h"

class Quadtree
{
public:
	int _iMaxDepth;
	Node* _pRootNode;

	bool Create(Rect rect, int depth = 2);
	Node* FindNode(Node* pNode, Object* pObject);
	bool AddObject(Object* pObject);
	void Reset(Node* pNode);
	void BuildTree(Node* pNode);
	bool IsSubDivide(Node* pNode);
};

