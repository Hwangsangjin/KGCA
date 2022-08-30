#pragma once

#include "Node.h"
#include "Object.h"

static const int _gMaxChild = 8;
class Octree
{
public:
	Node* _pRootNode;

	void DynamicObjectReset();
	void Create(Vector3 vPos, Vector3 vSize);
	void AddStaticObject(Object* pObject);
	void AddDynamicObject(Object* pObject);
	Node* FindNode(Node* pNode, Object* pObject);
	std::vector<Object*> CollisionQuery(Object* pObject);

	void DynamicReset(Node* pNode);
	bool IsNodeInObject(Node* pNode, Object* pObject);
	bool IsCollision(Object* pDest, Object* pSrc);
	bool IsCollision(Node* pNode, Object* pSrc);
	Node* CreateNode(Node* pParent, Vector3 vPos, Vector3 vSize);
	void Buildtree(Node* pNode);
	void GetCollisitionObject(Node* pNode, Object* pSrcObject, std::vector<Object*>& list);
};

