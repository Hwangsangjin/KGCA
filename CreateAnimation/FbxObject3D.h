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

	virtual HRESULT Init() override;
	virtual HRESULT Frame() override;
	virtual HRESULT Render() override;
	virtual HRESULT Release() override;

	void SetParent(FbxObject3D* pParentNode);

	DxMatrix Interplate(float frame, AnimScene animScene);

	void CreateVertexData();
	HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();

	HRESULT LoadTexture(W_STR textureFile);

	HRESULT PostRender();
};


class FbxSkinningObject3D : public FbxObject3D
{
public:
	std::vector<ID3D11Buffer*> _pSubVertexBufferIW;
	std::vector<std::vector<IndexWeightVertex>> _vbDataListIW;
	std::vector<IndexWeightVertex> _vertexListIW;
	ID3D11Buffer* _pVertexBufferIW;

	HRESULT CreateInputLayout()
	{
		if (!_pVertexShaderCode)
		{
			return E_FAIL;
		}

		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT,   0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			{ "INDEX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		UINT NumElements = sizeof(ied) / sizeof(ied[0]);
		HR(_pd3dDevice->CreateInputLayout(
			ied,
			NumElements,
			_pVertexShaderCode->GetBufferPointer(),
			_pVertexShaderCode->GetBufferSize(),
			&_pInputLayout));
	}

	HRESULT CreateVertexBuffer()
	{
		FbxObject3D::CreateVertexBuffer();

		if (_vbDataListIW.size() > 0.0f)
		{
			_pSubVertexBufferIW.resize(_vbDataListIW.size());
			for (size_t i = 0; i < _vbDataListIW.size(); i++)
			{
				if (_vbDataListIW[i].size() > 0)
				{
					_pSubVertexBufferIW[i] =
						DX::CreateVertexBuffer(_pd3dDevice,
							&_vbDataListIW[i].at(0),
							_vbDataListIW[i].size(),
							sizeof(IndexWeightVertex));
				}
			}
		}
		else
		{
			Object3D::CreateVertexBuffer();
		}

		return TRUE;
	}

	HRESULT	PostRender()
	{
		if (_pIndexBuffer == nullptr)
		{
			if (_vbDataList.size() > 0)
			{
				for (int i = 0; i < _pSubVertexBuffer.size(); i++)
				{
					if (_vbDataList[i].size() <= 0)
					{
						continue;
					}

					UINT stride[2] = { sizeof(DefaultVertex), sizeof(IndexWeightVertex) }; // 정점1개의 바이트용량
					UINT offset[2] = { 0, 0 }; // 정점버퍼에서 출발지점(바이트)
					//SLOT(레지스터리)
					ID3D11Buffer* buffer[2] = { _pSubVertexBuffer[i],_pSubVertexBufferIW[i] };
					_pImmediateContext->IASetVertexBuffers(0, 2, buffer, stride, offset);

					if (_pSubTexture[i])
					{
						_pImmediateContext->PSSetShaderResources(0, 1, &_pSubTexture[i]->_pShaderResourceView);
					}

					_pImmediateContext->Draw(_vbDataList[i].size(), 0);
				}
			}
			else
			{
				_pImmediateContext->Draw(_vertices.size(), 0);
			}
		}
		else
		{
			_pImmediateContext->DrawIndexed(_face * 3, 0, 0);
		}

		return TRUE;
	}

	HRESULT	Release()
	{
		Object3D::Release();

		//SAFE_RELEASE(_pVertexBufferIW);
		if (_pVertexBufferIW)_pVertexBufferIW->Release();

		for (size_t i = 0; i < _pSubVertexBuffer.size(); i++)
		{
			if (_pSubVertexBuffer[i])
			{
				_pSubVertexBuffer[i]->Release();
				_pSubVertexBufferIW[i]->Release();
			}
		}

		return TRUE;
	}
};

