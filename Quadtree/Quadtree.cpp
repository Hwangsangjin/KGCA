#include <iostream>
#include <vector>
#include <queue>

class Object
{
public:
    float _x;
    float _y;
    float _w;
    float _h;

    Object()
    {
        _x = 20 + (rand() % 80);
        _y = 20 + (rand() % 80);
        _w = 10.0f + (rand() % 10);
        _h = 10.0f + (rand() % 10);
    }

    void SetPosition(float x, float y, float w, float h)
    {
        _x = x;
        _y = y;
        _w = w;
        _h = h;
    }
};

class Node
{
public:
    float _x;
    float _y;
    float _w;
    float _h;
    int _depth;
    std::vector<Object*> _objects;
    Node* _pChild[4];
    Node* _pParent;

    Node(Node* pParent, float x, float y, float w, float h)
    {
        _x = x;
        _y = y;
        _w = w;
        _h = h;
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
class Quadtree
{
public:
    Node* _pRootNode;

    std::vector<Object*> Collision(Object* pObject);
    void Create(float w, float h);
    Node* CreateNode(Node* pParent, float x, float y, float w, float h);
    void Buildtree(Node* pNode);
    void AddObject(Object* pObject);
    Node* FindNode(Node* pNode, Object* pObject);
    bool RectToInRect(Node* pNode, Object* pObject);
    int RectToRect(Node* pNode, Object* pObject);
    int RectToRect(Object* pDestObject, Object* pSrcObject);
    void GetCollisitionObject(Node* pNode, Object* pObject, std::vector<Object*>& list);

    ~Quadtree()
    {
        delete _pRootNode;
    }
};

void Quadtree::Create(float w, float h)
{
    _pRootNode = CreateNode(nullptr, 0, 0, w, h);
    Buildtree(_pRootNode);
}

void Quadtree::Buildtree(Node* pNode)
{
    if (pNode->_depth >= 2)
    {
        return;
    }

    if (pNode == nullptr)
    {
        return;
    }

    float x, y, w, h;
    x = pNode->_x;
    y = pNode->_y;
    w = pNode->_w / 2.0f;
    h = pNode->_h / 2.0f;

    pNode->_pChild[0] = CreateNode(pNode, x, y, w, h);
    x = pNode->_x + w;
    y = pNode->_y;

    pNode->_pChild[1] = CreateNode(pNode, x, y, w, h);
    x = pNode->_x;
    y = pNode->_y + h;

    pNode->_pChild[2] = CreateNode(pNode, x, y, w, h);
    x = pNode->_x + w;
    y = pNode->_y + h;

    pNode->_pChild[3] = CreateNode(pNode, x, y, w, h);

    for (int i = 0; i < 4; i++)
    {
        Buildtree(pNode->_pChild[i]);
    }
}

Node* Quadtree::CreateNode(Node* pParent, float x, float y, float w, float h)
{
    Node* pNode = new Node(pParent, x, y, w, h);
    return pNode;
}

// 1번 : 완전히 포함하는 노드에 추가
// 2번 : 걸쳐만 있어도 노드에 추가
void Quadtree::AddObject(Object* pObject)
{
    Node* pFindNode = FindNode(_pRootNode, pObject);
    if (pFindNode != nullptr)
    {
        pFindNode->_objects.push_back(pObject);
    }
}
Node* Quadtree::FindNode(Node* pNode, Object* pObject)
{
    do
    {
        for (int i = 0; i < 4; i++)
        {
            if (pNode->_pChild[i] != nullptr)
            {
                bool in = RectToInRect(pNode->_pChild[i], pObject);
                if (in > 0)
                {
                    g_Queue.push(pNode->_pChild[i]);
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
bool Quadtree::RectToInRect(Node* pNode, Object* pObject)
{
    //  |             |
    if (pNode->_x <= pObject->_x)
    {
        if ((pNode->_x + pNode->_w) >= pObject->_x + pObject->_w)
        {
            if (pNode->_y <= pObject->_y)
            {
                if ((pNode->_y + pNode->_h) >= pObject->_y + pObject->_h)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

int Quadtree::RectToRect(Node* pNode, Object* pObject)
{
    // 0 : 완전제외(0)
    // 1 : 완전포함(1) -> 걸쳐져 있는 상태(2)
    // x1(10)----30------x2(40)
    float x1 = pNode->_x;
    float y1 = pNode->_y;
    float x2 = pNode->_x + pNode->_w;
    float y2 = pNode->_y + pNode->_h;

    float z1 = pObject->_x;
    float w1 = pObject->_y;
    float z2 = pObject->_x + pObject->_w;
    float w2 = pObject->_y + pObject->_h;

    // 합집합
    float minX;
    float minY;
    float maxX;
    float maxY;
    minX = x1 < z1 ? x1 : z1;
    minY = y1 < w1 ? y1 : w1;
    maxX = x2 < z2 ? x2 : z2;
    maxY = y2 < w2 ? y2 : w2;

    // 가로 판정
    if ((pNode->_w + pObject->_w) >= (maxX - minX))
    {
        // 세로 판정
        if ((pNode->_h + pObject->_h) >= (maxY - minY))
        {
            // 교집합
            return 1;
        }
    }

    return 0;
}

int Quadtree::RectToRect(Object* pDestObject, Object* pObject)
{
    // 0 : 완전제외(0)
    // 1 : 완전포함(1) -> 걸쳐져 있는 상태(2)
    // x1(10)----30------x2(40)
    float x1 = pDestObject->_x;
    float y1 = pDestObject->_y;
    float x2 = pDestObject->_x + pDestObject->_w;
    float y2 = pDestObject->_y + pDestObject->_h;

    float z1 = pObject->_x;
    float w1 = pObject->_y;
    float z2 = pObject->_x + pObject->_w;
    float w2 = pObject->_y + pObject->_h;

    // 합집합
    float minX;
    float minY;
    float maxX;
    float maxY;
    minX = x1 < z1 ? x1 : z1;
    minY = y1 < w1 ? y1 : w1;
    maxX = x2 > z2 ? x2 : z2;
    maxY = y2 > w2 ? y2 : w2;

    // 가로 판정
    if ((pDestObject->_w + pObject->_w) >= (maxX - minX))
    {
        // 세로 판정
        if ((pDestObject->_h + pObject->_h) >= (maxY - minY))
        {
            // 교집합
            return 1;
        }
    }

    return 0;
}

std::vector<Object*> Quadtree::Collision(Object* pObject)
{
    std::vector<Object*> list;
    GetCollisitionObject(this->_pRootNode, pObject, list);

    return list;
};

void Quadtree::GetCollisitionObject(Node* pNode, Object* pSrcObject, std::vector<Object*>& list)
{
    if (pNode == nullptr)
    {
        return;
    }

    for (int i = 0; i < pNode->_objects.size(); i++)
    {
        if (RectToRect(pNode->_objects[i], pSrcObject))
        {
            list.push_back(pNode->_objects[i]);
        }
    }

    if (pNode->_pChild[0] == nullptr)
    {
        for (int i = 0; i < 4; i++)
        {
            if (RectToRect(pNode->_pChild[i], pSrcObject))
            {
                GetCollisitionObject(pNode->_pChild[i], pSrcObject, list);
            }
        }
    }
}

int main()
{
    Object player;
    player.SetPosition(10, 10, 30, 30);
    Quadtree quadtree;
    quadtree.Create(100.0f, 100.0f);

    for (int i = 0; i < 100; i++)
    {
        Object* pObject = new Object;
        quadtree.AddObject(pObject);
    }

    std::vector<Object*> list = quadtree.Collision(&player);
    if (!list.empty())
    {
        for (int i = 0; i < list.size(); i++)
        {
            std::cout << list[i]->_x << " " << list[i]->_y << std::endl;
        }
    }
}
