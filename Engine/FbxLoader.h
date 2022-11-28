#pragma once

#include "fbxsdk.h"
#include "FbxObject3D.h"
#include "TextureManager.h"

class FbxLoader
{
public:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;

	FbxManager* _pFbxManager = nullptr;
	FbxImporter* _pFbxImporter = nullptr;
	FbxScene* _pFbxScene = nullptr;
	FbxNode* _pRootNode = nullptr;
	std::vector<FbxMesh*> _pFbxMeshs;

	DxMatrix _world;
	DxMatrix _view;
	DxMatrix _projection;

	AnimScene _animScene;
	float _animFrame = 0.0f;
	float _animInverse = 1.0f;
	float _animSpeed = 1.0f;

	BoneBuffer _cbDataBone;
	ID3D11Buffer* _pConstantBufferAnimBone;

	//std::vector<FbxObject3D*> _pObjects;
	std::vector<FbxSkinningObject3D*> _pObjects;
	//std::vector<FbxObject3D*> _pDrawObjects;
	std::vector<FbxSkinningObject3D*> _pDrawObjects;
	//std::map<FbxNode*, FbxObject3D*> _pObjectMap;
	std::map<FbxNode*, FbxSkinningObject3D*> _pObjectMap;
	std::map<FbxNode*, UINT> _pObjectIndexMap;

	HRESULT Init();
	HRESULT Frame();
	HRESULT Render();
	HRESULT Release();

	HRESULT Load(C_STR filename);
	HRESULT SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	HRESULT CreateConstantBuffer(ID3D11Device* pd3dDevice);

	void PreProcess(FbxNode* pFbxNode);
	//void ParseMesh(FbxMesh* pFbxMesh, FbxObject3D* pObject);
	void ParseMesh(FbxMesh* pFbxMesh, FbxSkinningObject3D* pObject);
	bool ParseMeshSkinning(FbxMesh* pFbxMesh, FbxSkinningObject3D* pObject);
	FbxVector2 ReadUVs(FbxMesh* pFbxMesh, FbxLayerElementUV* pUV, int posIndex, int uvIndex);
	FbxVector4 ReadNormals(FbxMesh* pFbxMesh, FbxLayerElementNormal* pNormal, int posIndex, int colorIndex);
	FbxColor ReadColors(FbxMesh* pFbxMesh, FbxLayerElementVertexColor* pVertexColor, int posIndex, int colorIndex);
	int GetSubMaterialIndex(int polygon, FbxLayerElementMaterial* pMaterial);
	//void LoadAnimation(FbxObject3D* pObject);
	void InitAnimation();
	void LoadAnimation(FbxLongLong t, FbxTime time);
	void UpdateAnimation(ID3D11DeviceContext* pImmediateContext);
	void UpdateSkeleton(ID3D11DeviceContext* pImmediateContext, float time, BoneBuffer& cbData);
	void UpdateSkinning(ID3D11DeviceContext* pImmediateContext, BoneBuffer& cbInputData, std::vector<BoneBuffer>& cbOutputData);

	void SetMatrix(DxMatrix* pWorld, DxMatrix* pView, DxMatrix* pProjection);
	DxMatrix ConvertMatrix(FbxAMatrix& fbxMatrix);
	DxMatrix DXConvertMatrix(FbxAMatrix& fbxMatrix);
};

