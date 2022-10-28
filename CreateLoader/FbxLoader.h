#pragma once

#include "fbxsdk.h"
#include "Object.h"

#pragma comment(lib, "libfbxsdk-md")
#pragma comment(lib, "libxml2-md")
#pragma comment(lib, "zlib-md")

class MyObject : public Object
{
public:
	void  CreateVertexData()
	{
	}
	HRESULT CreateIndexBuffer()
	{
		return TRUE;
	}
};

class FbxLoader
{
private:
	FbxManager* _pFbxManager = nullptr;
	FbxImporter* _pFbxImporter = nullptr;
	FbxScene* _pFbxScene = nullptr;
	FbxNode* _pRootNode = nullptr;
	std::vector<FbxMesh*> _pFbxMeshs;

public:
	std::vector<MyObject*> _pDrawObjects;

	HRESULT Init();
	HRESULT Frame();
	HRESULT Render();
	HRESULT Release();

	HRESULT Load(C_STR filename);

	void PreProcess(FbxNode* pFbxNode);
	void ParseMesh(FbxMesh* pFbxMesh);
	FbxVector2 ReadUVs(FbxMesh* pFbxMesh, FbxLayerElementUV* pVertexUVs);
};

