#include "pch.h"
#include "Quadtree.h"
#include "Object3D.h"
#include "Map.h"
#include "Frustum.h"
#include "Camera.h"

Node::Node(Node* pParent, class Map* pMap, DWORD leftTop, DWORD rightTop, DWORD rightBottom, DWORD leftBottom, DWORD x, DWORD y)
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

    CreateIndexBuffer(pMap, x, y);
}

Node::~Node()
{
    SAFE_RELEASE(_pIndexBuffer);

    for (int i = 0; i < _pChild.size(); i++)
    {
        SAFE_DELETE(_pChild[i]);
    }
}

void Node::CreateChildNode(Node* pParent, class Map* pMap, DWORD x, DWORD y)
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

    _pChild[0] = new Node(pParent, pMap, leftTop, topCenter, leftCenter, center, x, y);
    _pChild[1] = new Node(pParent, pMap, topCenter, rightTop, center, rightCenter, x, y);
    _pChild[2] = new Node(pParent, pMap, leftCenter, center, leftBottom, bottomCenter, x, y);
    _pChild[3] = new Node(pParent, pMap, center, rightCenter, bottomCenter, rightBottom, x, y);
}

void Node::CreateIndexData(Map* pMap, DWORD x, DWORD y)
{
    DWORD leftTop = _corner[0];
    DWORD rightTop = _corner[1];
    DWORD leftBottom = _corner[2];
    DWORD rightBottom = _corner[3];
    DWORD width = rightTop - leftTop;
    DWORD height = (leftBottom - leftTop) / x;
    DWORD cells = width * height;
    _indices.resize(cells * 2 * 3);
    int index = 0;

    _box._min._x = pMap->_vertices[leftTop].position._x;
    _box._min._y = 100000.0f;
    _box._min._z = pMap->_vertices[leftBottom].position._z;
    _box._max._x = pMap->_vertices[rightTop].position._x;
    _box._max._y = -100000.0f;
    _box._max._z = pMap->_vertices[leftTop].position._z;

    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            _indices[index + 0] = leftTop + j + (i * x);
            _indices[index + 1] = _indices[index + 0] + 1;
            _indices[index + 2] = leftTop + j + ((i + 1) * x);

            _indices[index + 3] = _indices[index + 2];
            _indices[index + 4] = _indices[index + 1];
            _indices[index + 5] = _indices[index + 2] + 1;

            for (DWORD dwVertex = 0; dwVertex < 6; dwVertex++)
            {
                if (_box._min._y > pMap->_vertices[_indices[index + dwVertex]].position._y)
                {
                    _box._min._y = pMap->_vertices[_indices[index + dwVertex]].position._y;
                }

                if (_box._max._y < pMap->_vertices[_indices[index + dwVertex]].position._y)
                {
                    _box._max._y = pMap->_vertices[_indices[index + dwVertex]].position._y;
                }
            }

            index += 6;
        }
    }

    _face = _indices.size() / 3;
    _box._center = (_box._min + _box._max) * 0.5f;
    _box._axis[0] = { 1.0f, 0.0f, 0.0f };
    _box._axis[1] = { 0.0f, 1.0f, 0.0f };
    _box._axis[2] = { 0.0f, 0.0f, 1.0f };
    _box._extent[0] = _box._max._x - _box._center._x;
    _box._extent[1] = _box._max._y - _box._center._y;
    _box._extent[2] = _box._max._z - _box._center._z;
}

HRESULT Node::CreateIndexBuffer(Map* pMap, DWORD x, DWORD y)
{
    CreateIndexData(pMap, x, y);
    D3D11_BUFFER_DESC       bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(DWORD) * _indices.size();
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &_indices.at(0);
    HR(pMap->_pd3dDevice->CreateBuffer(
        &bd, // 버퍼 할당
        &sd, // 초기 할당된 버퍼를 체우는 CPU메모리 주소
        &_pIndexBuffer));

    return TRUE;
}

Quadtree::~Quadtree()
{
    SAFE_DELETE(_pRootNode);
}

HRESULT Quadtree::Init()
{
    return TRUE;
}

HRESULT Quadtree::Frame()
{
    _pDrawLeafNodes.clear();
    VisibleNode(_pRootNode);

    return TRUE;
}

HRESULT Quadtree::Render()
{
    for (auto& node : _pDrawLeafNodes)
    {
        _pMap->PreRender();
        _pMap->_pImmediateContext->IASetIndexBuffer(node->_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
        _pMap->_pImmediateContext->DrawIndexed(node->_face * 3, 0, 0);
    }

    return TRUE;
}

HRESULT Quadtree::Release()
{
    SAFE_RELEASE(_pCamera);
    SAFE_RELEASE(_pMap);

    return TRUE;
}

HRESULT Quadtree::CreateTree(Camera* pMainCamera, Map* pMap, int maxDepth)
{
    _pCamera = pMainCamera;
    _pMap = pMap;
    _maxDepth = maxDepth;
    _pRootNode = new Node(nullptr, _pMap, 0, pMap->_x - 1, pMap->_x * (pMap->_y - 1), pMap->_x * pMap->_y - 1, pMap->_y, pMap->_x);

    BuildTree(_pRootNode);

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
        _pLeafNodes.push_back(pNode);

        return E_FAIL;
    }

    pNode->CreateChildNode(pNode, _pMap, _pMap->_x, _pMap->_y);

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
    Node* pFindNode = FindNode(_pRootNode, pObject);
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

Node* Quadtree::VisibleNode(Node* pNode)
{
    CULLING_POSITION result = _pCamera->_frustum.ClassifyBOX(pNode->_box);
    if (result == CULLING_POSITION::FRONT)
    {
        _pDrawLeafNodes.push_back(pNode);

        return pNode;
    }

    if (result == CULLING_POSITION::SPANNING)
    {
        if (pNode->_isLeaf)
        {
            _pDrawLeafNodes.push_back(pNode);
        }
        else
        {
            for (size_t i = 0; i < 4; i++)
            {
                VisibleNode(pNode->_pChild[i]);
            }
        }
    }
    
    return nullptr;
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
