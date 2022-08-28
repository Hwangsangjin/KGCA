#pragma once

#include "pch.h"
#include "Object.h"
#include "Collision.h"

struct Node
{
public:
	int _depth;
	Rect _rect;
	Box _box;

	Node* _pParent;
	std::vector<Node*> _pChild;
	std::vector<Object*> _staticObjects;
	std::vector<Object*> _dynamicObjects;

	Node() = default;
	Node(Node* pParent, Vector3 vPos, Vector3 vSize);
	~Node();
};

