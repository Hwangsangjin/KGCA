#include "Node.h"

Node::Node(Node* pParent, Rect rect)
{
	if (pParent != nullptr)
	{
		_iDepth = pParent->_iDepth + 1;
	}

	_rect = rect;
	_bLeaf = false;
	_pChild.resize(4);
}

Node::~Node()
{
	delete _pChild[0];
	delete _pChild[1];
	delete _pChild[2];
	delete _pChild[3];
	_pChild[0] = nullptr;
	_pChild[1] = nullptr;
	_pChild[2] = nullptr;
	_pChild[3] = nullptr;
}

void Node::CreateChildNode(Node* pParent)
{
	Rect rect = pParent->_rect;
	float halfW = _rect.right / 2.0f;
	float halfH = rect.bottom / 2.0f;
	_pChild[0] = new Node(pParent, { rect.left, rect.top, halfW, halfH });
	_pChild[1] = new Node(pParent, { rect.left + halfW, rect.top, halfW, halfH });
	_pChild[2] = new Node(pParent, { rect.left, rect.top + halfH, halfW, halfH });
	_pChild[3] = new Node(pParent, { rect.left + halfW, rect.top + halfH, halfW, halfH });
}
