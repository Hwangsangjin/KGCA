#include "pch.h"
#include "Node.h"

Node::Node(Node* pParent, Vector3 vPos, Vector3 vSize)
{
    _box.Set(vPos, vSize);
    _depth = 0;
    _pParent = nullptr;
    if (pParent != nullptr)
    {
        _pParent = pParent;
        _depth = pParent->_depth + 1;
    }
}

Node::~Node()
{
    for (int i = 0; i < _pChild.size(); i++)
    {
        delete _pChild[i];
    }
}
