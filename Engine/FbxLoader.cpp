#include "pch.h"
#include "FbxLoader.h"
#include "TextureManager.h"
#include "Timer.h"

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
    SAFE_RELEASE(_pConstantBufferBone);

    for (auto& object : _pDrawObjects)
    {
        object->Release();
        delete object;
        object = nullptr;
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

    FbxAxisSystem SceneAxisSystem = _pFbxScene->GetGlobalSettings().GetAxisSystem();

    // 단위
    FbxSystemUnit::m.ConvertScene(_pFbxScene);
    // 기저(행렬)
    FbxAxisSystem::MayaZUp.ConvertScene(_pFbxScene);

    //FbxGeometryConverter converter(_pFbxManager);
    //converter.Triangulate(_pFbxScene, true);

    InitAnimation();

    _pRootNode = _pFbxScene->GetRootNode();
    PreProcess(_pRootNode);

    for (auto& object : _pObjects)
    {
        if (object->_pFbxParentNode)
        {
            auto data = _pObjectMap.find(object->_pFbxParentNode);
            object->SetParent(data->second);
        }

        FbxMesh* pFbxMesh = object->_pFbxNode->GetMesh();
        if (pFbxMesh)
        {
            ParseMesh(pFbxMesh, object);
        }
    }

    // 애니메이션
    FbxTime time;
    for (FbxLongLong t = _animScene.startFrame; t <= _animScene.endFrame; t++)
    {
        time.SetFrame(t, _animScene.timeMode);
        LoadAnimation(t, time);
    }

    return TRUE;
}

HRESULT FbxLoader::CreateConstantBuffer(ID3D11Device* pd3dDevice)
{
    for (size_t i = 0; i < 255; i++)
    {
        D3DXMatrixIdentity(&_cbDataBone.boneMatrix[i]);
    }

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(BoneBuffer) * 1; // 바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &_cbDataBone;
    HR(pd3dDevice->CreateBuffer(
        &bd, // 버퍼 할당
        &sd, // 초기 할당된 버퍼를 체우는 CPU메모리 주소
        &_pConstantBufferBone))

        return TRUE;
}

void FbxLoader::PreProcess(FbxNode* pFbxNode)
{
    if (pFbxNode && (pFbxNode->GetCamera() || pFbxNode->GetLight()))
    {
        return;
    }

    FbxSkinningObject3D* pObject = new FbxSkinningObject3D;
    std::string name = pFbxNode->GetName();
    pObject->_name = to_mw(name);
    pObject->_pFbxNode = pFbxNode;
    pObject->_pFbxParentNode = pFbxNode->GetParent();
    pObject->_boneCount = _pObjects.size();

    _pObjects.push_back(pObject);
    _pObjectMap.insert(std::make_pair(pFbxNode, pObject));
    _pObjectIndexMap.insert(std::make_pair(pFbxNode, pObject->_boneCount));

    int childCount = pFbxNode->GetChildCount();
    for (size_t i = 0; i < childCount; i++)
    {
        FbxNode* pChild = pFbxNode->GetChild(i);

        // 헬퍼 오브젝트 + 지오메트리 오브젝트
        FbxNodeAttribute::EType type = pChild->GetNodeAttribute()->GetAttributeType();
        if (type == FbxNodeAttribute::eMesh ||
            type == FbxNodeAttribute::eSkeleton ||
            type == FbxNodeAttribute::eNull)
        {
            PreProcess(pChild);
        }
    }
}

void FbxLoader::ParseMesh(FbxMesh* pFbxMesh, FbxSkinningObject3D* pObject)
{
    // 스키닝 정보 확인
    pObject->_isSkinned = ParseMeshSkinning(pFbxMesh, pObject);

    FbxNode* pNode = pFbxMesh->GetNode();

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

    //FbxAMatrix worldTransform = pObject->_fbxLocalMatrix;
    // 최종 월드행렬 = 자신(애니메이션)행렬 * 부모(애니메이션)행렬
    //if (pObject->_pParent)
    //{
    //  worldTransform = pObject->_pParent->_fbxLocalMatrix * pObject->_fbxLocalMatrix;
    //}		
    //FbxAMatrix worldMatrix = worldTransform;
    //worldMatrix = worldMatrix.Inverse();
    //worldMatrix = worldMatrix.Transpose();

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

    std::string fileName;
    int materialCount = pNode->GetMaterialCount();
    std::vector<C_STR> textureNames;
    textureNames.resize(materialCount);

    for (size_t i = 0; i < materialCount; i++)
    {
        FbxSurfaceMaterial* pSurface = pNode->GetMaterial(i);
        if (pSurface)
        {
            auto property = pSurface->FindProperty(FbxSurfaceMaterial::sDiffuse);
            if (property.IsValid())
            {
                //int textureCount = property.GetSrcObjectCount<FbxFileTexture>();
                //for (size_t j = 0; j < textureCount; j++)
                //{
                //    const FbxFileTexture* texture = property.GetSrcObject<FbxFileTexture>(j);
                //    if (texture)
                //    {
                //        fileName = texture->GetFileName();
                //        textureNames[i] = fileName;
                //    }
                //}

                const FbxFileTexture* texture = property.GetSrcObject<FbxFileTexture>();
                if (texture)
                {
                    fileName = texture->GetFileName();
                    textureNames[i] = fileName;
                }
            }
        }
    }

    if (materialCount == 1)
    {
        pObject->_textureName = TEXTURE->GetSplitName(fileName);
    }

    if (materialCount > 1)
    {
        pObject->_vbDataList.resize(materialCount);
        pObject->_vbDataListIW.resize(materialCount);
        pObject->_vbTextureList.resize(materialCount);

        for (size_t i = 0; i < materialCount; i++)
        {
            pObject->_vbTextureList[i] = TEXTURE->GetSplitName(textureNames[i]);
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
                IndexWeightVertex IWVertex;
                FbxVector4 v = geometry.MultT(v2);
                vertex.position.x = v.mData[0];
                vertex.position.y = v.mData[2];
                vertex.position.z = v.mData[1];
                vertex.color = DxVector4{ 1.0f, 1.0f, 1.0f, 1.0f };

                if (pUVs)
                {
                    FbxVector2 uv = ReadUVs(pFbxMesh, pUVs, cornerIndex[index], uvIndex[index]);
                    vertex.uv.x = uv.mData[0];
                    vertex.uv.y = 1.0f - uv.mData[1];
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
                    vertex.normal.x = normal.mData[0];
                    vertex.normal.y = normal.mData[2];
                    vertex.normal.z = normal.mData[1];
                }

                if (!pObject->_isSkinned)
                {
                    IWVertex.index.x = _pObjectIndexMap.find(pNode)->second;
                    IWVertex.index.y = 0;
                    IWVertex.index.z = 0;
                    IWVertex.index.w = 0;

                    IWVertex.weight.x = 1.0f;
                    IWVertex.weight.y = 0.0f;
                    IWVertex.weight.z = 0.0f;
                    IWVertex.weight.w = 0.0f;
                }
                else
                {
                    Weight* pWeight = &pObject->_weights[vertexIndex];
                    IWVertex.index.x = pWeight->indexs[0];
                    IWVertex.index.y = pWeight->indexs[1];
                    IWVertex.index.z = pWeight->indexs[2];
                    IWVertex.index.w = pWeight->indexs[3];

                    IWVertex.weight.x = pWeight->weights[0];
                    IWVertex.weight.y = pWeight->weights[1];
                    IWVertex.weight.z = pWeight->weights[2];
                    IWVertex.weight.w = pWeight->weights[3];
                }

                if (materialCount <= 1)
                {
                    pObject->_vertices.push_back(vertex);
                    pObject->_vertexListIW.push_back(IWVertex);
                }
                else
                {
                    pObject->_vbDataList[subMaterial].push_back(vertex);
                    pObject->_vbDataListIW[subMaterial].push_back(IWVertex);
                }
            }
        }

        polygonIndex += polygonSize;
    }

    _pDrawObjects.push_back(pObject);
}

bool FbxLoader::ParseMeshSkinning(FbxMesh* pFbxMesh, FbxSkinningObject3D* pObject)
{
    // 리깅 도구(뼈대에 스킨을 붙이는 작업 도구)
    int deformerCount = pFbxMesh->GetDeformerCount(FbxDeformer::eSkin);
    if (deformerCount == 0)
    {
        return false;
    }

    // 메쉬의 정점 갯수와 같아야 한다.
    int controlPointsCount = pFbxMesh->GetControlPointsCount();
    pObject->_weights.resize(controlPointsCount);

    for (size_t i = 0; i < deformerCount; i++)
    {
        FbxDeformer* pDeformer = pFbxMesh->GetDeformer(i, FbxDeformer::eSkin);
        FbxSkin* pSkin = (FbxSkin*)pDeformer;

        // 뼈대가 영향을 미치는 정점 덩어리
        int clusterCount = pSkin->GetClusterCount();
        for (size_t i = 0; i < clusterCount; i++)
        {
            FbxCluster* pCluster = pSkin->GetCluster(i);
            FbxNode* pNode = pCluster->GetLink();
            int boneIndex = _pObjectIndexMap.find(pNode)->second;

            // 뼈대 공간으로 변환하는 행렬이 필요하다.
            FbxAMatrix bindPoseMatrix;
            FbxAMatrix referenceGlobalInitPositionMatrix;
            pCluster->GetTransformLinkMatrix(bindPoseMatrix);
            pCluster->GetTransformMatrix(referenceGlobalInitPositionMatrix);
            FbxAMatrix bindPosePositionMatrix = referenceGlobalInitPositionMatrix.Inverse() * bindPoseMatrix;

            DxMatrix bindPosePositionInvertMatrix = DXConvertMatrix(bindPosePositionMatrix);
            bindPosePositionInvertMatrix = bindPosePositionInvertMatrix.Invert();
            pObject->_dxMatrixBindPoseMap.insert(std::make_pair(boneIndex, bindPosePositionInvertMatrix));

            // 임의의 1개 정점에 영향을 미치는 뼈대의 갯수
            int weightCount = pCluster->GetControlPointIndicesCount();
            int* pIndices = pCluster->GetControlPointIndices();
            double* pWeights = pCluster->GetControlPointWeights();
            for (size_t i = 0; i < weightCount; i++)
            {
                int vertexIndex = pIndices[i];
                float weight = pWeights[i];
                pObject->_weights[vertexIndex].Insert(boneIndex, weight);
            }
        }
    }

    return true;
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

void FbxLoader::InitAnimation()
{
    FbxAnimStack* stackAnim = _pFbxScene->GetSrcObject<FbxAnimStack>(0);
    FbxLongLong s = 0;
    FbxLongLong n = 0;
    FbxTime::EMode timeMode;

    if (stackAnim)
    {
        FbxString takeName = stackAnim->GetName();
        FbxTakeInfo* take = _pFbxScene->GetTakeInfo(takeName);
        FbxTime::SetGlobalTimeMode(FbxTime::eFrames30);
        timeMode = FbxTime::GetGlobalTimeMode();
        FbxTimeSpan localTimeSpan = take->mLocalTimeSpan;
        FbxTime start = localTimeSpan.GetStart();
        FbxTime end = localTimeSpan.GetStop();
        FbxTime duration = localTimeSpan.GetDirection();
        s = start.GetFrameCount(timeMode);
        n = end.GetFrameCount(timeMode);
    }

    _animScene.startFrame = s;
    _animScene.endFrame = n;
    _animScene.frameSpeed = 30.0f;
    _animScene.tickPerFrame = 160.0f;
    _animScene.timeMode = timeMode;
}

void FbxLoader::LoadAnimation(FbxLongLong t, FbxTime time)
{
    for (auto& object : _pObjects)
    {
        FbxNode* pNode = object->_pFbxNode;
        AnimTrack animtrack;
        animtrack.frame = t;
        FbxAMatrix fbxMatrix = pNode->EvaluateGlobalTransform(time);
        animtrack.animMatrix = DXConvertMatrix(fbxMatrix);
        D3DXMatrixDecompose(&animtrack.s, &animtrack.r, &animtrack.t, &animtrack.animMatrix);
        object->_animTracks.push_back(animtrack);
    }
}

HRESULT FbxLoader::UpdateAnimation(ID3D11DeviceContext* pImmediateContext)
{
    _animFrame = _animFrame + _animSpeed * _animScene.frameSpeed * _animInverse * DELTA_TIME;
    if (_animFrame > _animScene.endFrame || _animFrame < _animScene.startFrame)
    {
        _animFrame = min(_animFrame, _animScene.endFrame);
        _animFrame = max(_animFrame, _animScene.startFrame);
        _animInverse *= -1.0f;
    }

    // Object + Skinning
    std::vector<DxMatrix> currentAnimsMatrix;
    for (size_t i = 0; i < _pObjects.size(); i++)
    {
        DxMatrix animMatrix = _pObjects[i]->Interplate(_animFrame, _animScene);
        D3DXMatrixTranspose(&_cbDataBone.boneMatrix[i], &animMatrix);
        currentAnimsMatrix.push_back(animMatrix);
    }
    pImmediateContext->UpdateSubresource(_pConstantBufferBone, 0, nullptr, &_cbDataBone, 0, 0);

    // Skinning
    for (size_t i = 0; i < _pDrawObjects.size(); i++)
    {
        if (_pDrawObjects[i]->_dxMatrixBindPoseMap.size())
        {
            for (size_t j = 0; j < _pObjects.size(); j++)
            {
                auto iter = _pDrawObjects[i]->_dxMatrixBindPoseMap.find(j);
                if (iter != _pDrawObjects[i]->_dxMatrixBindPoseMap.end())
                {
                    DxMatrix bindMatrix = iter->second;
                    DxMatrix animMatrix = bindMatrix * currentAnimsMatrix[j];
                    D3DXMatrixTranspose(&_cbDataBone.boneMatrix[j], &animMatrix);
                }
            }
            
            pImmediateContext->UpdateSubresource(_pDrawObjects[i]->_pConstantBufferBone, 0, nullptr, &_cbDataBone, 0, 0);
        }
    }

    return TRUE;
}

DxMatrix FbxLoader::ConvertMatrix(FbxAMatrix& fbxMatrix)
{
    DxMatrix matrix;
    float* tArray = (float*)(&matrix);
    double* fbxArray = (double*)(&fbxMatrix);

    for (size_t i = 0; i < 16; i++)
    {
        tArray[i] = fbxArray[i];
    }

    return matrix;
}

DxMatrix FbxLoader::DXConvertMatrix(FbxAMatrix& fbxMatrix)
{
    DxMatrix temp = ConvertMatrix(fbxMatrix);
    DxMatrix matrix;

    matrix._11 = temp._11; matrix._12 = temp._13; matrix._13 = temp._12;
    matrix._21 = temp._31; matrix._22 = temp._33; matrix._23 = temp._32;
    matrix._31 = temp._21; matrix._32 = temp._23; matrix._33 = temp._22;
    matrix._41 = temp._41; matrix._42 = temp._43; matrix._43 = temp._42;
    matrix._14 = matrix._24 = temp._34 = 0.0f;
    matrix._44 = 1.0f;

    return matrix;
}
