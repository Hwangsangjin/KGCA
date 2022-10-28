#include "pch.h"
#include "FbxLoader.h"
#include "Object3D.h"

HRESULT FbxLoader::Init()
{
    _pFbxManager = FbxManager::Create();
    _pFbxImporter = FbxImporter::Create(_pFbxManager, "");
    _pFbxScene = FbxScene::Create(_pFbxManager, "");

    return TRUE;
}

HRESULT FbxLoader::Frame()
{
    for (auto& object : _pDrawObjects)
    {
        object->Frame();
    }

    return TRUE;
}

HRESULT FbxLoader::Render()
{
    for (auto& object : _pDrawObjects)
    {
        object->Render();
    }

    return TRUE;
}

HRESULT FbxLoader::Release()
{
    for (auto& object : _pDrawObjects)
    {
        object->Release();
    }

    _pFbxScene->Destroy();
    _pFbxImporter->Destroy();
    _pFbxManager->Destroy();

    return TRUE;
}

HRESULT FbxLoader::Load(C_STR filename)
{
    _pFbxImporter->Initialize(filename.c_str());
    _pFbxImporter->Import(_pFbxScene);
    _pRootNode = _pFbxScene->GetRootNode();
    PreProcess(_pRootNode);

    for (auto& mesh : _pFbxMeshs)
    {
        ParseMesh(mesh);
    }

    return TRUE;
}

void FbxLoader::PreProcess(FbxNode* pFbxNode)
{
    if (!pFbxNode)
    {
        return;
    }

    FbxMesh* pFbxMesh = pFbxNode->GetMesh();
    if (pFbxMesh)
    {
        _pFbxMeshs.push_back(pFbxMesh);
    }

    int count = pFbxNode->GetChildCount();
    for (size_t i = 0; i < count; i++)
    {
        FbxNode* pChild = pFbxNode->GetChild(i);
        PreProcess(pChild);
    }
}

void FbxLoader::ParseMesh(FbxMesh* pFbxMesh)
{
    MyObject* pObject = new MyObject;

    // ·¹ÀÌ¾î
    FbxLayerElementUV* pVertexUVs = nullptr;
    FbxLayer* pFbxLayer = pFbxMesh->GetLayer(0);
    if (pFbxLayer->GetUVs())
    {
        pVertexUVs = pFbxLayer->GetUVs();
    }

    // Æú¸®°ï
    int polygonCount = pFbxMesh->GetPolygonCount();

    // 3Á¤Á¡ -> 1Æú¸®°ï(»ï°¢Çü)
    // 4Á¤Á¡ -> 1Æú¸®°ï(Äõµå)
    int faceCount = 0;

    // Á¦¾îÁ¡
    FbxVector4* pVertexPosition = pFbxMesh->GetControlPoints();

    for (size_t polygon = 0; polygon < polygonCount; polygon++)
    {
        int polygonSize = pFbxMesh->GetPolygonSize(polygon);
        faceCount = polygonSize - 2;
        for (size_t face = 0; face < faceCount; face++)
        {
            int cornerIndex[3];
            cornerIndex[0] = pFbxMesh->GetPolygonVertex(polygon, 0);
            cornerIndex[1] = pFbxMesh->GetPolygonVertex(polygon, face + 2);
            cornerIndex[2] = pFbxMesh->GetPolygonVertex(polygon, face + 1);

            for (size_t index = 0; index < 3; index++)
            {
                int vertexIndex = cornerIndex[index];
                FbxVector4 v = pVertexPosition[vertexIndex];
                Vertex vertex;
                vertex.position._x = v.mData[0];
                vertex.position._y = v.mData[2];
                vertex.position._z = v.mData[1];
                vertex.color = Vector4{ 1.0f, 1.0f, 1.0f, 1.0f };
                FbxVector2 uv = ReadUVs(pFbxMesh, pVertexUVs);
                vertex.uv._x = uv.mData[0];
                vertex.uv._y = 1.0f - uv.mData[1];

                pObject->_vertices.push_back(vertex);
            }
        }
    }

    _pDrawObjects.push_back(pObject);
}

FbxVector2 FbxLoader::ReadUVs(FbxMesh* pFbxMesh, FbxLayerElementUV* pVertexUVs)
{
    FbxVector2 uv;

    return uv;
}
