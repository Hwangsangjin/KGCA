#include "pch.h"
#include "FbxLoader.h"
#include "Object3D.h"
#include "TextureManager.h"

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

    if (_pFbxImporter)
    {
        _pFbxImporter->Destroy();
        _pFbxImporter = nullptr;
    }

    if (_pFbxManager)
    {
        _pFbxManager->Destroy();
        _pFbxManager = nullptr;
    }

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
    FbxNode* pNode = pFbxMesh->GetNode();
    MyObject* pObject = new MyObject;

    // 레이어
    FbxLayerElementUV* pVertexUVs = nullptr;
    FbxLayerElementVertexColor* pVertexColors = nullptr;
    FbxLayerElementMaterial* pMaterials = nullptr;

    //for (size_t i = 0; i < length; i++)
    //{

    //}

    int num = pFbxMesh->GetLayerCount();
    for (int i = 0; i < num; ++i)
    {
        FbxLayer* pFbxLayer = pFbxMesh->GetLayer(i);
        FbxLayerElementVertexColor* temp = pFbxLayer->GetVertexColors();
        if (temp != nullptr)
        {
            pVertexColors = temp;
            //break;
        }
    }
    
    FbxLayer* pFbxLayer = pFbxMesh->GetLayer(0);
    if (pFbxLayer->GetUVs())
    {
        pVertexUVs = pFbxLayer->GetUVs();
    }

    /*if (pFbxLayer->GetUVs())
    {
        pVertexColors = pFbxLayer->GetVertexColors();
    }*/

    if (pFbxLayer->GetMaterials())
    {
        pMaterials = pFbxLayer->GetMaterials();
    }

    std::string filename;
    int materialCount = pNode->GetMaterialCount();
    std::vector<C_STR> textures;
    textures.resize(materialCount);

    for (size_t i = 0; i < materialCount; i++)
    {
        // 24 이상의 정보가 있다.
        FbxSurfaceMaterial* pSurface = pNode->GetMaterial(i);
        if (pSurface)
        {
            auto property = pSurface->FindProperty(FbxSurfaceMaterial::sDiffuse);
            if (property.IsValid())
            {
                int textureCount = property.GetSrcObjectCount<FbxFileTexture>();
                for (size_t j = 0; j < textureCount; j++)
                {
                    const FbxFileTexture* texture = property.GetSrcObject<FbxFileTexture>(j);
                    filename = texture->GetFileName();
                    textures[i] = filename;
                }
            }
        }
    }

    if (materialCount == 1)
    {
        pObject->_textureName = TEXTURE->GetSplitName(filename);
    }

    if (materialCount > 1)
    {
        pObject->_dataList.resize(materialCount);
        pObject->_textureList.resize(materialCount);

        for (size_t i = 0; i < materialCount; i++)
        {
            pObject->_textureList[i] = TEXTURE->GetSplitName(textures[i]);
        }
    }

    // 폴리곤
    int polygonCount = pFbxMesh->GetPolygonCount();
    int polygonIndex = 0;

    // 머티리얼
    int subMaterial = 0;

    // 3정점 -> 1폴리곤(삼각형)
    // 4정점 -> 1폴리곤(쿼드)
    int faceCount = 0;

    // 제어점
    FbxVector4* pVertexPosition = pFbxMesh->GetControlPoints();

    for (size_t polygon = 0; polygon < polygonCount; polygon++)
    {
        int polygonSize = pFbxMesh->GetPolygonSize(polygon);
        faceCount = polygonSize - 2;

        if (pMaterials)
        {
            subMaterial = GetSubMaterialIndex(polygon, pMaterials);
        }

        for (size_t face = 0; face < faceCount; face++)
        {
            // 정점 컬러 인덱스
            int vertexColor[3] = { 0.0f, face + 2, face + 1 };

            // 정점 인덱스
            int cornerIndex[3];
            cornerIndex[0] = pFbxMesh->GetPolygonVertex(polygon, 0);
            cornerIndex[1] = pFbxMesh->GetPolygonVertex(polygon, face + 2);
            cornerIndex[2] = pFbxMesh->GetPolygonVertex(polygon, face + 1);

            // UV 인덱스
            int uvIndex[3];
            uvIndex[0] = pFbxMesh->GetTextureUVIndex(polygon, 0);
            uvIndex[1] = pFbxMesh->GetTextureUVIndex(polygon, face + 2);
            uvIndex[2] = pFbxMesh->GetTextureUVIndex(polygon, face + 1);

            for (size_t index = 0; index < 3; index++)
            {
                int vertexIndex = cornerIndex[index];
                FbxVector4 v = pVertexPosition[vertexIndex];
                Vertex vertex;
                vertex.position._x = v.mData[0];
                vertex.position._y = v.mData[2];
                vertex.position._z = v.mData[1];
                vertex.color = Vector4{ 1.0f, 1.0f, 1.0f, 1.0f };

                if (pVertexColors)
                {
                    FbxColor color = ReadColors(pFbxMesh, pVertexColors, cornerIndex[index], polygonIndex + vertexColor[index]);
                    vertex.color.x = color.mRed;
                    vertex.color.y = color.mGreen;
                    vertex.color.z = color.mBlue;
                    vertex.color.w = 1.0f;
                }

                if (pVertexUVs)
                {
                    FbxVector2 uv = ReadUVs(pFbxMesh, pVertexUVs, cornerIndex[index], uvIndex[index]);
                    vertex.uv._x = uv.mData[0];
                    vertex.uv._y = 1.0f - uv.mData[1];
                }

                if (materialCount <= 1)
                {
                    pObject->_vertices.push_back(vertex);
                }
                else
                {
                    pObject->_dataList[subMaterial].push_back(vertex);
                }
            }
        }

        polygonIndex += polygonSize;
    }

    _pDrawObjects.push_back(pObject);
}

FbxColor FbxLoader::ReadColors(FbxMesh* pFbxMesh, FbxLayerElementVertexColor* pVertexColors, int posIndex, int colorIndex)
{
    FbxColor color(1.0f, 1.0f, 1.0f, 1.0f);
    FbxLayerElement::EMappingMode mode = pVertexColors->GetMappingMode();
    switch (mode)
    {
    case FbxLayerElement::eByControlPoint:
    {
        switch (pVertexColors->GetReferenceMode())
        {
        case FbxLayerElementUV::eDirect:
            color = pVertexColors->GetDirectArray().GetAt(posIndex);
            break;
        case FbxLayerElementUV::eIndexToDirect:
            int index = pVertexColors->GetIndexArray().GetAt(posIndex);
            color = pVertexColors->GetDirectArray().GetAt(index);
            break;
        }
    }
    break;
    case FbxLayerElement::eByPolygonVertex:
    {
        switch (pVertexColors->GetReferenceMode())
        {
        case FbxLayerElementUV::eDirect:
            color = pVertexColors->GetDirectArray().GetAt(colorIndex);
            break;
        case FbxLayerElementUV::eIndexToDirect:
            int index = pVertexColors->GetIndexArray().GetAt(colorIndex);
            color = pVertexColors->GetDirectArray().GetAt(index);
            break;
        }
    }
    break;
    }

    return color;
}

FbxVector2 FbxLoader::ReadUVs(FbxMesh* pFbxMesh, FbxLayerElementUV* pVertexUVs, int posIndex, int uvIndex)
{
    FbxVector2 uv;
    FbxLayerElement::EMappingMode mode = pVertexUVs->GetMappingMode();
    switch (mode)
    {
    case FbxLayerElementUV::eByControlPoint:
    {
        switch (pVertexUVs->GetReferenceMode())
        {
        case FbxLayerElementUV::eDirect:
            uv = pVertexUVs->GetDirectArray().GetAt(posIndex);
            break;
        case FbxLayerElementUV::eIndexToDirect:
            int index = pVertexUVs->GetIndexArray().GetAt(posIndex);
            uv = pVertexUVs->GetDirectArray().GetAt(index);
            break;
        }
    }
    case FbxLayerElementUV::eByPolygonVertex:
    {
        switch (pVertexUVs->GetReferenceMode())
        {
        case FbxLayerElementUV::eDirect:
        case FbxLayerElementUV::eIndexToDirect:
            uv = pVertexUVs->GetDirectArray().GetAt(uvIndex);
            break;
        }
    }
    }
    return uv;
}

int FbxLoader::GetSubMaterialIndex(int polygon, FbxLayerElementMaterial* pMaterials)
{
    int subMaterial = 0;
    if (pMaterials)
    {
        switch (pMaterials->GetMappingMode())
        {
        case FbxLayerElement::eByPolygon:
        {
            // 매핑 정보가 배열에 저장되는 방식
            switch (pMaterials->GetReferenceMode())
            {
            case FbxLayerElement::eIndex:
                subMaterial = polygon;
                break;
            case FbxLayerElement::eIndexToDirect:
                subMaterial = pMaterials->GetIndexArray().GetAt(polygon);
                break;
            }
        }
        }
    }

    return subMaterial;
}
