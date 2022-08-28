#pragma once

#include "pch.h"
#include "ObjectBase.h"
#include "Collision.h"

struct Node
{
public:
	int _depth;
	Rectangle _rect;
	Box _box;

	Node* _pParent;
	std::vector<Node*> _pChild;
	std::vector<ObjectBase*> _staticObjects;
	std::vector<ObjectBase*> _dynamicObjects;
};

