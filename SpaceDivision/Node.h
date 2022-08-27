#pragma once

#include "pch.h"
#include "Object.h"

class Node
{
public:
	int _depth;
	bool _leaf;
	
	virtual ~Node();

	void CreateChildNode(Node* pParent);
};

