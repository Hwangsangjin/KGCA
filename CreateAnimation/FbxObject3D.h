#pragma once

#include "Object3D.h"
#include "fbxsdk.h"

struct AnimTrack
{
	UINT frame;
	MyMatrix animMatrix;
	MyMatrix animSelftMatrix;
	MyVector3 t;
	Quaternion r;
	MyVector3 s;
};

struct AnimScene
{
	UINT startFrame;
	UINT endFrame;
	float tickPerFrame;
	float frameSpeed;
};

class FbxObject3D : public Object3D
{
public:
	FbxNode* _pFbxNode = nullptr;
	FbxNode* _pFbxParentNode = nullptr;
	FbxObject3D* _pParent = nullptr;

	AnimScene _animScene;
	float _animFrame = 0.0f;
	float _animInverse = 1.0f;
	float _animSpeed = 1.0f;

	FbxAMatrix _fbxLocalMatrix;

	std::vector<FbxObject3D*> _pFbxChilds;
	std::vector<AnimTrack> _animTracks;
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


