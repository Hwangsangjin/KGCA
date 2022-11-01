#include "pch.h"
#include "FbxLoader.h"
#include "TextureManager.h"

HRESULT FbxLoader::Init()
{
    _pFbxManager = FbxManager::Create();
    _pFbxImporter = FbxImporter::Create(_pFbxManager, "");
    _pFbxScene = FbxScene::Create(_pFbxManager, "");

    // 단위
    FbxSystemUnit::cm.ConvertScene(_pFbxScene);

    // 기저
    FbxAxisSystem::MayaZUp.ConvertScene(_pFbxScene);

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
    //FbxGeometryConverter converter(_pFbxManager);
    //converter.Triangulate(_pFbxScene, true);

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

    int childCount = pFbxNode->GetChildCount();
    for (size_t i = 0; i < childCount; i++)
    {
        FbxNode* pChild = pFbxNode->GetChild(i);
        PreProcess(pChild);
    }
}

void FbxLoader::ParseMesh(FbxMesh* pFbxMesh)
{
    FbxNode* pNode = pFbxMesh->GetNode();
    FbxObject3D* pObject = new FbxObject3D;

    FbxAMatrix geometry; // 기하(로컬)행렬(초기 정점 위치를 변환할 때 사용)
    FbxVector4 translation = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
    FbxVector4 rotation = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
    FbxVector4 scale = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
    geometry.SetT(translation);
    geometry.SetR(rotation);
    geometry.SetS(scale);

    FbxAMatrix localMatrix = geometry;
    localMatrix = localMatrix.Inverse();
    localMatrix = localMatrix.Transpose();

    // 월드 행렬
    FbxVector4 t;
    if (pNode->LclTranslation.IsValid())
    {
        t = pNode->LclTranslation.Get();
    }

    FbxVector4 r;
    if (pNode->LclRotation.IsValid())
    {
        r = pNode->LclRotation.Get();
    }

    FbxVector4 s;
    if (pNode->LclScaling.IsValid())
    {
        s = pNode->LclScaling.Get();
    }

    FbxAMatrix worldTransform(t, r, s);
    FbxAMatrix worldMatrix = worldTransform;
    worldMatrix = worldMatrix.Inverse();
    worldMatrix = worldMatrix.Transpose();

    // 레이어
    FbxLayerElementUV* pUVs = nullptr;
    FbxLayerElementVertexColor* pVertexColors = nullptr;
    FbxLayerElementNormal* pNormals = nullptr;
    FbxLayerElementMaterial* pMaterials = nullptr;
    FbxLayer* pFbxLayer = pFbxMesh->GetLayer(0);
    if (pFbxLayer->GetUVs())
    {
        pUVs = pFbxLayer->GetUVs();
    }

    if (pFbxLayer->GetVertexColors())
    {
        pVertexColors = pFbxLayer->GetVertexColors();
    }

    //int count = pFbxMesh->GetLayerCount();
    //for (int i = 0; i < count; ++i)
    //{
    //    FbxLayer* pFbxLayer = pFbxMesh->GetLayer(i);
    //    FbxLayerElementVertexColor* temp = pFbxLayer->GetVertexColors();
    //    if (temp != nullptr)
    //    {
    //        pVertexColors = temp;
    //    }
    //}

    if (pFbxLayer->GetNormals())
    {
        pNormals = pFbxLayer->GetNormals();
    }

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
        pObject->_vbDataList.resize(materialCount);
        pObject->_vbTextureList.resize(materialCount);

        for (size_t i = 0; i < materialCount; i++)
        {
            pObject->_vbTextureList[i] = TEXTURE->GetSplitName(textures[i]);
        }
    }

    // 폴리곤
    int polygonCount = pFbxMesh->GetPolygonCount();
    int polygonIndex = 0;

    // 서브 머티리얼
    int subMaterial = 0;

    // 페이스
    int faceCount = 0;

    // 제어점
    FbxVector4* pControlPoints = pFbxMesh->GetControlPoints();

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
            int vertexColor[3] = { 0, face + 2, face + 1 };

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
                FbxVector4 v2 = pControlPoints[vertexIndex];
                DefaultVertex vertex;
                FbxVector4 v = geometry.MultT(v2);
                v = worldTransform.MultT(v);
                vertex.position._x = v.mData[0];
                vertex.position._y = v.mData[2];
                vertex.position._z = v.mData[1];
                vertex.color = Vector4{ 1.0f, 1.0f, 1.0f, 1.0f };

                if (pUVs)
                {
                    FbxVector2 uv = ReadUVs(pFbxMesh, pUVs, cornerIndex[index], uvIndex[index]);
                    vertex.uv._x = uv.mData[0];
                    vertex.uv._y = 1.0f - uv.mData[1];
                }

                if (pVertexColors)
                {
                    FbxColor color = ReadColors(pFbxMesh, pVertexColors, cornerIndex[index], polygonIndex + vertexColor[index]);
                    vertex.color.x = color.mRed;
                    vertex.color.y = color.mGreen;
                    vertex.color.z = color.mBlue;
                    vertex.color.w = 1.0f;
                }

                if (pNormals)
                {
                    FbxVector4 normal = ReadNormals(pFbxMesh, pNormals, cornerIndex[index], polygonIndex + vertexColor[index]);
                    normal = localMatrix.MultT(normal);
                    normal = worldMatrix.MultT(normal);
                    vertex.normal._x = normal.mData[0];
                    vertex.normal._y = normal.mData[2];
                    vertex.normal._z = normal.mData[1];
                }

                if (materialCount <= 1)
                {
                    pObject->_vertices.push_back(vertex);
                }
                else
                {
                    pObject->_vbDataList[subMaterial].push_back(vertex);
                }
            }
        }

        polygonIndex += polygonSize;
    }

    _pDrawObjects.push_back(pObject);
}

FbxVector2 FbxLoader::ReadUVs(FbxMesh* pFbxMesh, FbxLayerElementUV* pUV, int posIndex, int uvIndex)
{
    FbxVector2 uv;
    FbxLayerElement::EMappingMode mode = pUV->GetMappingMode();
    switch (mode)
    {
    case FbxLayerElementUV::eByControlPoint:
        switch (pUV->GetReferenceMode())
        {
        case FbxLayerElementUV::eDirect:
            uv = pUV->GetDirectArray().GetAt(posIndex);
            break;
        case FbxLayerElementUV::eIndexToDirect:
            int index = pUV->GetIndexArray().GetAt(posIndex);
            uv = pUV->GetDirectArray().GetAt(index);
            break;
        }
        break;
    case FbxLayerElementUV::eByPolygonVertex:
        switch (pUV->GetReferenceMode())
        {
        case FbxLayerElementUV::eDirect:
        case FbxLayerElementUV::eIndexToDirect:
            uv = pUV->GetDirectArray().GetAt(uvIndex);
            break;
        }
        break;
    }

    return uv;
}

FbxVector4 FbxLoader::ReadNormals(FbxMesh* pFbxMesh, FbxLayerElementNormal* pNormal, int posIndex, int colorIndex)
{
    FbxVector4 normal(1.0f, 1.0f, 1.0f, 1.0f);
    FbxLayerElement::EMappingMode mode = pNormal->GetMappingMode();
    switch (mode)
    {
    case FbxLayerElementUV::eByControlPoint:
        switch (pNormal->GetReferenceMode())
        {
        case FbxLayerElementUV::eDirect:
            normal = pNormal->GetDirectArray().GetAt(posIndex);
            break;
        case FbxLayerElementUV::eIndexToDirect:
            int index = pNormal->GetIndexArray().GetAt(posIndex);
            normal = pNormal->GetDirectArray().GetAt(index);
            break;
        }
        break;
    case FbxLayerElementUV::eByPolygonVertex:
        switch (pNormal->GetReferenceMode())
        {
        case FbxLayerElementUV::eDirect:
            normal = pNormal->GetDirectArray().GetAt(colorIndex);
            break;
        case FbxLayerElementUV::eIndexToDirect:
            int index = pNormal->GetIndexArray().GetAt(colorIndex);
            normal = pNormal->GetDirectArray().GetAt(index);
            break;
        }
        break;
    }

    return normal;
}

FbxColor FbxLoader::ReadColors(FbxMesh* pFbxMesh, FbxLayerElementVertexColor* pVertexColor, int posIndex, int colorIndex)
{
    FbxColor color(1.0f, 1.0f, 1.0f, 1.0f);
    FbxLayerElement::EMappingMode mode = pVertexColor->GetMappingMode();
    switch (mode)
    {
    case FbxLayerElement::eByControlPoint:
        switch (pVertexColor->GetReferenceMode())
        {
        case FbxLayerElementUV::eDirect:
            color = pVertexColor->GetDirectArray().GetAt(posIndex);
            break;
        case FbxLayerElementUV::eIndexToDirect:
            int index = pVertexColor->GetIndexArray().GetAt(posIndex);
            color = pVertexColor->GetDirectArray().GetAt(index);
            break;
        }
        break;
    case FbxLayerElement::eByPolygonVertex:
        switch (pVertexColor->GetReferenceMode())
        {
        case FbxLayerElementUV::eDirect:
            color = pVertexColor->GetDirectArray().GetAt(colorIndex);
            break;
        case FbxLayerElementUV::eIndexToDirect:
            int index = pVertexColor->GetIndexArray().GetAt(colorIndex);
            color = pVertexColor->GetDirectArray().GetAt(index);
            break;
        }
        break;
    }

    return color;
}

int FbxLoader::GetSubMaterialIndex(int polygon, FbxLayerElementMaterial* pMaterial)
{
    int subMaterial = 0;
    if (pMaterial)
    {
        switch (pMaterial->GetMappingMode())
        {
        case FbxLayerElement::eByPolygon:
            // 매핑 정보가 배열에 저장되는 방식
            switch (pMaterial->GetReferenceMode())
            {
            case FbxLayerElement::eIndex:
                subMaterial = polygon;
                break;
            case FbxLayerElement::eIndexToDirect:
                subMaterial = pMaterial->GetIndexArray().GetAt(polygon);
                break;
            }
            break;
        }
    }

    return subMaterial;
}
