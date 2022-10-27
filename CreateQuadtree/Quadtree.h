#pragma once

struct Node
{
	int _depth;
	bool _isLeaf;
	DWORD _corner[4];

	std::vector<Node*> _pChild;
	std::vector<class Object3D*> _pStaticObjects;
	std::vector<class Object3D*> _pDynamicObjects;

	Node(Node* pParent, DWORD leftTop, DWORD rightTop, DWORD rightBottom, DWORD leftBottom);
	virtual ~Node();

	void CreateChildNode(Node* pParent);
};

class Quadtree
{
public:
	Node* _rootNode;
	int _maxDepth;
	class Map* _pMap = nullptr;

	HRESULT CreateTree(Map* pMap, int maxDepth = 2);
	HRESULT BuildTree(Node* pNode);
	HRESULT IsSubDivide(Node* pNode);
	HRESULT AddObject(Object3D* pObject);
	Node* FindNode(Node* pNode, Object3D* pObject);
	void Reset(Node* pNode);
};

