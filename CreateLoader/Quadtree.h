#pragma once

#include "Collision.h"

struct Node
{
	int _depth;
	bool _isLeaf;
	DWORD _corner[4];
	DWORD _face;
	CollisionBOX _box;
	std::vector<DWORD> _indices;
	ID3D11Buffer* _pIndexBuffer = nullptr;

	std::vector<Node*> _pChild;
	std::vector<class Object3D*> _pStaticObjects;
	std::vector<class Object3D*> _pDynamicObjects;

	Node(Node* pParent, class Map* pMap, DWORD leftTop, DWORD rightTop, DWORD rightBottom, DWORD leftBottom, DWORD x, DWORD y);
	virtual ~Node();

	void CreateChildNode(Node* pParent, class Map* pMap, DWORD x, DWORD y);
	void CreateIndexData(class Map* pMap, DWORD x, DWORD y);
	HRESULT CreateIndexBuffer(class Map* pMap, DWORD x, DWORD y);
};

class Quadtree
{
public:
	Node* _pRootNode;
	int _maxDepth;
	class Camera* _pCamera = nullptr;
	class Map* _pMap = nullptr;

	std::vector<Node*> _pLeafNodes;
	std::vector<Node*> _pDrawLeafNodes;

	virtual ~Quadtree();

	HRESULT Init();
	HRESULT Frame();
	HRESULT Render();
	HRESULT Release();

	HRESULT CreateTree(Camera* pMainCamera, Map* pMap, int maxDepth = 3);
	HRESULT BuildTree(Node* pNode);
	HRESULT IsSubDivide(Node* pNode);
	HRESULT AddObject(Object3D* pObject);
	Node* FindNode(Node* pNode, Object3D* pObject);
	Node* VisibleNode(Node* pNode);
	void Reset(Node* pNode);
};

