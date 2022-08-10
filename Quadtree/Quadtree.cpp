#include "Collision.h"
#include <windows.h>

class Object
{
public:
    Rect _rt;
    Circle _circle;

    Object()
    {
        _rt.Set(20 + (rand() % 80), 20 + (rand() % 80), 5.0f + (rand() % 5), 5.0f + (rand() % 5));
        SetCircle(_rt.cx, _rt.cy, _rt.w, _rt.h);
    }

    void SetPosition(float x, float y, float w, float h)
    {
        _rt.Set(x, y, w, h);
        SetCircle(_rt.cx, _rt.cy, _rt.w, _rt.h);
    }

    void   SetCircle(float x, float y, float w, float h)
    {
        _circle.cx = x;
        _circle.cy = y;
        float x1 = w / 2.0f;
        float y1 = h / 2.0f;
        _circle.radius = sqrt(x1 * x1 + y1 * y1);
    }
};

class Node
{
public:
    Rect _rt;
    int _depth;
    std::vector<Object*> _objects;
    Node* _pChild[4];
    Node* _pParent;

    Node(Node* pParent, float x, float y, float w, float h)
    {
        _rt.Set(x, y, w, h);
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
    x = pNode->_rt.x1;
    y = pNode->_rt.y1;
    w = pNode->_rt.w / 2.0f;
    h = pNode->_rt.h / 2.0f;

    pNode->_pChild[0] = CreateNode(pNode, x, y, w, h);
    x = pNode->_rt.x1 + w;
    y = pNode->_rt.y1;

    pNode->_pChild[1] = CreateNode(pNode, x, y, w, h);
    x = pNode->_rt.x1;
    y = pNode->_rt.y1 + h;

    pNode->_pChild[2] = CreateNode(pNode, x, y, w, h);
    x = pNode->_rt.x1 + w;
    y = pNode->_rt.y1 + h;

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
                bool in = Collision::RectToInRect(pNode->_pChild[i]->_rt, pObject->_rt);
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
        if (Collision::RectToRect(pNode->_objects[i]->_rt, pSrcObject->_rt))
        {
            list.push_back(pNode->_objects[i]);
        }
    }

    if (pNode->_pChild[0] == nullptr)
    {
        for (int i = 0; i < 4; i++)
        {
            if (Collision::RectToRect(pNode->_pChild[i]->_rt, pSrcObject->_rt))
            {
                GetCollisitionObject(pNode->_pChild[i], pSrcObject, list);
            }
        }
    }
}

int main()
{
    Object player;
    player.SetPosition(0, 100, 20, 20);
    Quadtree quadtree;
    quadtree.Create(100.0f, 100.0f);
    float distance = 0.0f;

    for (int i = 0; i < 100; i++)
    {
        Object* pObject = new Object;
        quadtree.AddObject(pObject);
    }

    while (true)
    {
        std::vector<Object*> list = quadtree.Collision(&player);
        std::cout << "player : "
            << player._rt.x1 << " " << player._rt.y1 << " "
            << player._rt.x2 << " " << player._rt.y2
            << std::endl;

        if (!list.empty())
        {
            for (int i = 0; i < list.size(); i++)
            {
                std::cout << "object : "
                    << list[i]->_rt.x1 << " " << list[i]->_rt.y1 << " "
                    << list[i]->_rt.x2 << " " << list[i]->_rt.y2
                    << std::endl;
            }
        }

        static float directionX = 10.0f;
        if (rand() % 2 == 0)
        {
            directionX *= -1.0f;
        }

        static float directionY = 10.0f;
        if (rand() % 2 == 0)
        {
            directionY *= -1.0f;
        }

        player._rt.x1 = player._rt.x1 + directionX;
        player._rt.y1 = player._rt.y1 + directionY;

        player._rt.x1 = min(player._rt.x1, 100.0f);
        player._rt.x1 = max(player._rt.x1, 0);
        player._rt.y1 = min(player._rt.y1, 100.0f);
        player._rt.y1 = max(player._rt.y1, 0);

        player.SetPosition(player._rt.x1, player._rt.y1, 30, 30);

        Sleep(1000);
        system("cls");
    }
}
