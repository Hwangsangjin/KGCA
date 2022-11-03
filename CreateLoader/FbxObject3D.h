#pragma once

#include "Object3D.h"

class FbxObject3D : public Object3D
{
public:
	class FbxNode* _pFbxNode = nullptr;
	class FbxNode* _pFbxParentNode = nullptr;
	class FbxObject3D* _pParent = nullptr;

	std::vector<FbxObject3D*> _pFbxChilds;
	std::vector<ID3D11Buffer*> _pSubVertexBuffer;
	std::vector<Texture*> _pSubTexture;
	std::vector<std::vector<DefaultVertex>> _vbDataList;
	std::vector<W_STR> _vbTextureList;

	virtual HRESULT Init() override;
	virtual HRESULT Frame() override;
	virtual HRESULT Render() override;
	virtual HRESULT Release() override;

	void SetParent(FbxObject3D* pParentNode);

	void CreateVertexData();
	HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();

	HRESULT LoadTexture(W_STR textureFile);

	HRESULT PostRender();
};


