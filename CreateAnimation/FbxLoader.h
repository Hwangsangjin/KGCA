#pragma once

#include "fbxsdk.h"
#include "FbxObject3D.h"
#include "TextureManager.h"

class FbxLoader
{
private:
	FbxManager* _pFbxManager = nullptr;
	FbxImporter* _pFbxImporter = nullptr;
	FbxScene* _pFbxScene = nullptr;
	FbxNode* _pRootNode = nullptr;
	std::vector<FbxMesh*> _pFbxMeshs;

public:
	std::vector<FbxObject3D*> _pObjects;
	std::vector<FbxObject3D*> _pDrawObjects;
	std::map<FbxNode*, FbxObject3D*> _pObjectMap;

	HRESULT Init();
	HRESULT Frame();
	HRESULT Render();
	HRESULT Release();

	HRESULT Load(C_STR filename);

	void PreProcess(FbxNode* pFbxNode);
	void ParseMesh(FbxMesh* pFbxMesh, FbxObject3D* pObject);
	FbxVector2 ReadUVs(FbxMesh* pFbxMesh, FbxLayerElementUV* pUV, int posIndex, int uvIndex);
	FbxVector4 ReadNormals(FbxMesh* pFbxMesh, FbxLayerElementNormal* pNormal, int posIndex, int colorIndex);
	FbxColor ReadColors(FbxMesh* pFbxMesh, FbxLayerElementVertexColor* pVertexColor, int posIndex, int colorIndex);
	int GetSubMaterialIndex(int polygon, FbxLayerElementMaterial* pMaterial);
	void LoadAnimation(FbxObject3D* pObject);
	MyMatrix ConvertMatrix(FbxAMatrix& fbxMatrix);
	MyMatrix DXConvertMatrix(FbxAMatrix& fbxMatrix);
};

