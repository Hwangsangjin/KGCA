#include "pch.h"
#include "Quadtree.h"
#include "Object3D.h"
#include "Map.h"

Node::Node(Node* pParent, DWORD leftTop, DWORD rightTop, DWORD rightBottom, DWORD leftBottom)
{
    if (pParent)
    {
        _depth = pParent->_depth + 1;
    }

    _corner[0] = leftTop;
    _corner[1] = rightTop;
    _corner[2] = rightBottom;
    _corner[3] = leftBottom;

    _isLeaf = false;

    _pChild.resize(4);
}

Node::~Node()
{
    for (int i = 0; i < _pChild.size(); i++)
    {
        delete _pChild[i];
        _pChild[i] = nullptr;
    }
}

void Node::CreateChildNode(Node* pParent)
{
    DWORD leftTop = pParent->_corner[0];
    DWORD rightTop = pParent->_corner[1];
    DWORD leftBottom = pParent->_corner[2];
    DWORD rightBottom = pParent->_corner[3];

    DWORD topCenter = (leftTop + rightTop) / 2;
    DWORD rightCenter = (rightBottom + rightTop) / 2;
    DWORD bottomCenter = (leftBottom + rightBottom) / 2;
    DWORD leftCenter = (leftBottom + leftTop) / 2;

    DWORD center = (rightTop + leftTop + rightBottom + leftBottom) / 4;

    _pChild[0] = new Node(pParent, leftTop, topCenter, leftCenter, center);
    _pChild[1] = new Node(pParent, topCenter, rightTop, center, rightCenter);
    _pChild[2] = new Node(pParent, leftCenter, center, leftBottom, bottomCenter);
    _pChild[3] = new Node(pParent, center, rightCenter, bottomCenter, rightBottom);
}

HRESULT Quadtree::CreateTree(Map* pMap, int maxDepth)
{
    _pMap = pMap;
    _maxDepth = maxDepth;
    _rootNode = new Node(nullptr, 0, pMap->_x - 1, pMap->_x * (pMap->_y - 1), pMap->_x * pMap->_y - 1);

    BuildTree(_rootNode);

    return TRUE;
}

HRESULT Quadtree::BuildTree(Node* pNode)
{
    if (!pNode)
    {
        return E_FAIL;
    }

    if (FAILED(IsSubDivide(pNode)))
    {
        pNode->_isLeaf = true;
        return E_FAIL;
    }

    pNode->CreateChildNode(pNode);

    BuildTree(pNode->_pChild[0]);
    BuildTree(pNode->_pChild[1]);
    BuildTree(pNode->_pChild[2]);
    BuildTree(pNode->_pChild[3]);

    return TRUE;
}

HRESULT Quadtree::IsSubDivide(Node* pNode)
{
    if ((pNode->_corner[1] - pNode->_corner[0] == 1))
    {
        return E_FAIL;
    }

    if (pNode->_depth < _maxDepth)
    {
        return TRUE;
    }

    return E_FAIL;
}

HRESULT Quadtree::AddObject(Object3D* pObject)
{
    Node* pFindNode = FindNode(_rootNode, pObject);
    if (pFindNode)
    {
        pFindNode->_pDynamicObjects.push_back(pObject);

        return TRUE;
    }

    return E_FAIL;
}

Node* Quadtree::FindNode(Node* pNode, Object3D* pObject)
{
    for (size_t i = 0; i < 4; i++)
    {
        if (pNode->_pChild[i])
        {

        }
    }

    return pNode;
}

void Quadtree::Reset(Node* pNode)
{
    if (!pNode)
    {
        return;
    }

    pNode->_pDynamicObjects.clear();

    Reset(pNode->_pChild[0]);
    Reset(pNode->_pChild[1]);
    Reset(pNode->_pChild[2]);
    Reset(pNode->_pChild[3]);
}
