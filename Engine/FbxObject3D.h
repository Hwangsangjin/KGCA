#pragma once

#include "Object3D.h"
#include "fbxsdk.h"

struct AnimTrack
{
	UINT frame;
	DxMatrix animMatrix;
	DxMatrix animSelftMatrix;
	DxVector3 t;
	DxQuaternion r;
	DxVector3 s;
};

struct AnimScene
{
	FbxTime::EMode timeMode;
	UINT startFrame;
	UINT endFrame;
	float tickPerFrame;
	float frameSpeed;
};

struct Weight
{
	std::vector<int> indexs;
	std::vector<float> weights;

	Weight()
	{
		indexs.resize(8);
		weights.resize(8);
	}

	void Insert(int bone, float weight)
	{
		for (size_t i = 0; i < indexs.size(); i++)
		{
			if (weight > this->weights[i])
			{
				for (size_t j = 0; j < indexs.size(); j++)
				{
					indexs[j] = indexs[j - 1];
					weights[j] = weights[j - 1];
				}

				indexs[i] = bone;
				weights[i] = weight;

				break;
			}
		}
	}
};

class FbxObject3D : public Object3D
{
public:
	FbxNode* _pFbxNode = nullptr;
	FbxNode* _pFbxParentNode = nullptr;
	FbxObject3D* _pParent = nullptr;

	UINT _boneCount;
	DxMatrix _animMatrix;
	DxMatrix _animControl;
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

	FbxObject3D() {}
	virtual ~FbxObject3D() {}

	virtual HRESULT Init() override;
	virtual HRESULT Frame() override;
	virtual HRESULT Render() override;
	virtual HRESULT Release() override;

	void SetParent(FbxObject3D* pParentNode);

	DxMatrix Interplate(float frame, AnimScene animScene);

	HRESULT LoadTexture(W_STR textureFile);

	virtual void CreateVertexData() override;
	virtual HRESULT CreateVertexBuffer() override;
	virtual HRESULT CreateIndexBuffer() override;

	virtual HRESULT PostRender() override;
};

class FbxSkinningObject3D : public FbxObject3D
{
public:
	// Sub Material
	std::vector<ID3D11Buffer*> _pSubVertexBufferIW;
	std::vector<std::vector<IndexWeightVertex>> _vbDataListIW;
	// Single Model
	std::vector<IndexWeightVertex> _vertexListIW;
	ID3D11Buffer* _pVertexBufferIW;
	// Skinning
	std::vector<Weight> _weights;
	std::map<UINT, DxMatrix> _dxMatrixBindPoseMap;

	BoneBuffer _cbDataBone;
	ID3D11Buffer* _pConstantBufferBone;

	bool _isSkinning = false;

	virtual HRESULT Init() override;
	virtual HRESULT Frame() override;
	virtual HRESULT Render() override;
	virtual HRESULT	Release() override;

	virtual HRESULT CreateConstantBuffer() override;
	virtual HRESULT CreateVertexBuffer() override;
	virtual HRESULT CreateInputLayout() override;

	virtual HRESULT	PostRender() override;
};

