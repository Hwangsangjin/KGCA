#include <iostream>
#include <vector>
#include <queue>

class Object
{
public:
    float  _x;
    float  _y;
    float  _width;
    float  _height;

    Object()
    {
        _x = rand() % 100;
        _y = rand() % 100;
        _width = 2.0f + (rand() % 10);
        _height = 2.0f + (rand() % 10);
    }
};

class Node
{
public:
    float _x;
    float _y;
    float _width;
    float _height;
    int _depth;
    std::vector<Object*>  _objects;
    Node* _pChild[4];
    Node* _pParent;

    Node(Node* pParent, float x, float y, float width, float height)
    {
        _x = x;
        _y = y;
        _width = width;
        _height = height;
        _depth = 0;
        _pParent = nullptr;

        if (pParent != nullptr)
        {
            _pParent = pParent;
            _depth = pParent->_depth + 1;
        }
    }

    ~Node()
    {
        delete _pChild[0];
        delete _pChild[1];
        delete _pChild[2];
        delete _pChild[3];
    }
};

std::queue<Node*> g_Queue;
class TQuadtree
{
public:
    Node* _pRootNode;

    void Create(float width, float height);
    Node* CreateNode(Node* pParent, float x, float y, float width, float height);
    void Buildtree(Node* pNode);
    void AddObject(Object* pObject);
    Node* FindNode(Node* pNode, Object* pObject);
    bool RectToRect(Node* pNode, Object* pObject);

    ~TQuadtree()
    {
        delete _pRootNode;
    }
};

void TQuadtree::Create(float width, float height)
{
    _pRootNode = CreateNode(nullptr, 0, 0, width, height);
    Buildtree(_pRootNode);
}

void TQuadtree::Buildtree(Node* pNode)
{
    if (pNode->_depth >= 2)
    {
        return;
    }

    if (pNode == nullptr)
    {
        return;
    }

    float _x, _y, _w, _h;
    _x = pNode->_x;
    _y = pNode->_y;
    _w = pNode->_width / 2.0f;
    _h = pNode->_height / 2.0f;
    pNode->_pChild[0] = CreateNode(pNode, _x, _y, _w, _h);
    _x = pNode->_x + _w;
    _y = pNode->_y;
    pNode->_pChild[1] = CreateNode(pNode, _x, _y, _w, _h);
    _x = pNode->_x;
    _y = pNode->_y + _h;
    pNode->_pChild[2] = CreateNode(pNode, _x, _y, _w, _h);
    _x = pNode->_x + _w;
    _y = pNode->_y + _h;
    pNode->_pChild[3] = CreateNode(pNode, _x, _y, _w, _h);

    for (int iChild = 0; iChild < 4; iChild++)
    {
        Buildtree(pNode->_pChild[iChild]);
    }
}

Node* TQuadtree::CreateNode(Node* pParent, float x, float y, float width, float height)
{
    Node* pNode = new Node(pParent, x, y, width, height);
    return pNode;
}

// 1번 : 완전히 포함하는 노드에 추가
// 2번 : 걸쳐만 있어도 노드에 추가
void TQuadtree::AddObject(Object* pObject)
{
    Node* pFindNode = FindNode(_pRootNode, pObject);
    if (pFindNode != nullptr)
    {
        pFindNode->_objects.push_back(pObject);
    }
}

Node* TQuadtree::FindNode(Node* pNode, Object* pObject)
{
    do
    {
        for (int iNode = 0; iNode < 4; iNode++)
        {
            if (pNode->_pChild[iNode] != nullptr)
            {
                bool bIn = RectToRect(pNode->_pChild[iNode], pObject);
                if (bIn > 0)
                {
                    g_Queue.push(pNode->_pChild[iNode]);
                    break;
                }
            }
        }

        if (g_Queue.empty())
        {
            break;
        }

        pNode = g_Queue.front();
        g_Queue.pop();
    } while (pNode);

    return pNode;
}

bool TQuadtree::RectToRect(Node* pNode, Object* pObject)
{
    if (pNode->_x <= pObject->_x)
    {
        if ((pNode->_x + pNode->_width) >= pObject->_x + pObject->_width)
        {
            if (pNode->_y <= pObject->_y)
            {
                if ((pNode->_y + pNode->_height) >= pObject->_y + pObject->_height)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

int main()
{
    TQuadtree quadtree;
    quadtree.Create(100.0f, 100.0f);
    for (int i = 0; i < 10; i++)
    {
        Object* pObject = new Object;
        quadtree.AddObject(pObject);
    }
}
