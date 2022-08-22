#include "Quadtree.h"
#include "Collision.h"

bool Quadtree::Create(Rect rect, int depth)
{
	_iMaxDepth = depth;
	_pRootNode = new Node(nullptr, rect);
	BuildTree(_pRootNode);

	return true;
}

Node* Quadtree::FindNode(Node* pNode, Object* pObject)
{
	for (size_t i = 0; i < 4; i++)
	{
		if (pNode->_pChild[i] != nullptr)
		{
			if (Collision::RectToInRect(pNode->_pChild[i]->_rect, pObject->_rect))
			{
				pNode = FindNode(pNode->_pChild[i], pObject);
				break;
			}
		}
	}

	return pNode;
}

bool Quadtree::AddObject(Object* pObject)
{
	Node* pFindNode = FindNode(_pRootNode, pObject);
	if (pFindNode != nullptr)
	{
		pFindNode->_pDynamicObjects.push_back(pObject);

		return true;
	}

	return false;
}

void Quadtree::Reset(Node* pNode)
{
	if (pNode == nullptr)
	{
		return;
	}

	pNode->_pDynamicObjects.clear();
	Reset(pNode->_pChild[0]);
	Reset(pNode->_pChild[1]);
	Reset(pNode->_pChild[2]);
	Reset(pNode->_pChild[3]);
}

void Quadtree::BuildTree(Node* pNode)
{
	if (pNode == nullptr)
	{
		return;
	}

	if (IsSubDivide(pNode) == false)
	{
		pNode->_bLeaf = true;

		return;
	}

	pNode->CreateChildNode(pNode);

	BuildTree(pNode->_pChild[0]);
	BuildTree(pNode->_pChild[1]);
	BuildTree(pNode->_pChild[2]);
	BuildTree(pNode->_pChild[3]);
}

bool Quadtree::IsSubDivide(Node* pNode)
{
	if (pNode->_iDepth < _iMaxDepth)
	{
		return true;
	}

	return false;
}
