#include "pch.h"
#include "Octree.h"
#include <queue>

void Octree::DynamicObjectReset()
{
	DynamicReset(_pRootNode);
}

void Octree::Create(Vector3 vPos, Vector3 vSize)
{
	_pRootNode = CreateNode(nullptr, vPos, vSize);
	Buildtree(_pRootNode);
}

void Octree::AddStaticObject(Object* pObject)
{
	Node* pFindNode = FindNode(_pRootNode, pObject);
	if (pFindNode != nullptr)
	{
		pFindNode->_staticObjects.push_back(pObject);
	}
}

void Octree::AddDynamicObject(Object* pObject)
{
	Node* pFindNode = FindNode(_pRootNode, pObject);
	if (pFindNode != nullptr)
	{
		pFindNode->_dynamicObjects.push_back(pObject);
	}
}

Node* Octree::FindNode(Node* pNode, Object* pObject)
{
    std::queue<Node*> g_Queue;
    do
    {
        for (int iNode = 0; iNode < pNode->_pChild.size(); iNode++)
        {
            if (pNode->_pChild[iNode] != nullptr)
            {
                bool bIn = IsNodeInObject(pNode->_pChild[iNode], pObject);
                if (bIn)
                {
                    g_Queue.push(pNode->_pChild[iNode]);
                    break;
                }
            }
        }
        if (g_Queue.empty()) break;
        pNode = g_Queue.front();
        g_Queue.pop();
    }
    while (pNode);

    return pNode;
}

std::vector<Object*> Octree::CollisionQuery(Object* pObject)
{
    std::vector<Object*> list;
    GetCollisitionObject(_pRootNode, pObject, list);
    return list;
}

void Octree::DynamicReset(Node* pNode)
{
    if (pNode == nullptr) return;
    pNode->_dynamicObjects.clear();
    for (int i = 0; i < pNode->_pChild.size(); i++)
    {
        DynamicReset(pNode->_pChild[i]);
    }
}

bool Octree::IsNodeInObject(Node* pNode, Object* pObject)
{
    return Collision::BoxToInBox(pNode->_box, pObject->_box);
}

bool Octree::IsCollision(Object* pDest, Object* pSrc)
{
    if (Collision::SphereToSphere(pDest->_sphere, pSrc->_sphere))
    {
        if (Collision::BoxToBox(pDest->_box, pSrc->_box))
        {
            return true;
        }
    }

    return false;
}

bool Octree::IsCollision(Node* pNode, Object* pSrc)
{
    if (Collision::BoxToBox(pNode->_box, pSrc->_box))
    {
        return true;
    }

    return false;
}

Node* Octree::CreateNode(Node* pParent, Vector3 vPos, Vector3 vSize)
{
    Node* pNode = new Node(pParent, vPos, vSize);
    pNode->_pChild.resize(_gMaxOctreeChild);
    return pNode;
}

void Octree::Buildtree(Node* pNode)
{
    if (pNode->_depth >= 3) return;
    if (pNode == nullptr) return;

    Vector3 pos;
    Vector3 size;

    pos = pNode->_box._vMin;
    size = pNode->_box._vSize / 2.0f;
    pNode->_pChild[0] = CreateNode(pNode, pos, size);
    pos._x = pNode->_box._vMin._x + size._x;
    pNode->_pChild[1] = CreateNode(pNode, pos, size);
    pos._x = pNode->_box._vMin._x;
    pos._y = pNode->_box._vMin._y + size._y;
    pNode->_pChild[2] = CreateNode(pNode, pos, size);
    pos._x = pNode->_box._vMin._x + size._x;
    pos._y = pNode->_box._vMin._y + size._y;
    pNode->_pChild[3] = CreateNode(pNode, pos, size);

    pos._x = pNode->_box._vMin._x;
    pos._y = pNode->_box._vMin._y;
    pos._z = pNode->_box._vMin._z + size._z;
    pNode->_pChild[4] = CreateNode(pNode, pos, size);
    pos._x = pNode->_box._vMin._x + size._x;
    pos._y = pNode->_box._vMin._y;
    pNode->_pChild[5] = CreateNode(pNode, pos, size);
    pos._x = pNode->_box._vMin._x;
    pos._y = pNode->_box._vMin._y + size._y;
    pNode->_pChild[6] = CreateNode(pNode, pos, size);
    pos._x = pNode->_box._vMin._x + size._x;
    pos._y = pNode->_box._vMin._y + size._y;
    pNode->_pChild[7] = CreateNode(pNode, pos, size);

    for (int i = 0; i < pNode->_pChild.size(); i++)
    {
        Buildtree(pNode->_pChild[i]);
    }
}

void Octree::GetCollisitionObject(Node* pNode, Object* pSrcObject, std::vector<Object*>& list)
{
    if (pNode == nullptr) return;

    for (int i = 0; i < pNode->_staticObjects.size(); i++)
    {
        if (IsCollision(pNode->_staticObjects[i], pSrcObject))
        {
            list.push_back(pNode->_staticObjects[i]);
        }
    }
    for (int i = 0; i < pNode->_dynamicObjects.size(); i++)
    {
        if (IsCollision(pNode->_dynamicObjects[i], pSrcObject))
        {
            list.push_back(pNode->_dynamicObjects[i]);
        }
    }
    if (pNode->_pChild[0] != nullptr)
    {
        for (int i = 0; i < pNode->_pChild.size(); i++)
        {
            if (IsCollision(pNode->_pChild[i], pSrcObject))
            {
                GetCollisitionObject(pNode->_pChild[i], pSrcObject, list);
            }
        }
    }
}
