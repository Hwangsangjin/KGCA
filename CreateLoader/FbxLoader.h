#pragma once

#include "fbxsdk.h"
#include "Object3D.h"
#include "TextureManager.h"

class FbxObject3D : public Object3D
{
public:
	std::vector<ID3D11Buffer*> _pSubVertexBuffer;
	std::vector<Texture*> _pSubTexture;
	std::vector<std::vector<DefaultVertex>> _vbDataList;
	std::vector<W_STR> _vbTextureList;

	void  CreateVertexData()
	{
	}
	HRESULT CreateVertexBuffer()
	{
		if (_vbDataList.size() > 0)
		{
			for (size_t i = 0; i < _vbDataList.size(); i++)
			{
				_pSubVertexBuffer.push_back(DX::CreateVertexBuffer(_pd3dDevice, &_vbDataList[i].at(0), _vbDataList[i].size(), sizeof(DefaultVertex)));
			}
		}
		else
		{
			Object3D::CreateVertexBuffer();
		}

		return TRUE;
	}
	HRESULT CreateIndexBuffer()
	{
		return TRUE;
	}

	HRESULT LoadTexture(W_STR filename)
	{
		if (_vbTextureList.size() > 0)
		{
			W_STR defaultDir = L"../../Resource/FBX/";
			_pSubTexture.resize(_vbTextureList.size());

			for (size_t i = 0; i < _vbTextureList.size(); i++)
			{
				W_STR loadFile = defaultDir + _vbTextureList[i];
				_pSubTexture[i] = TEXTURE->Load(loadFile);
			}
		}
		else
		{
			_pTexture = TEXTURE->Load(filename);
			if (_pTexture)
			{
				_pShaderResourceView = _pTexture->_pShaderResourceView;

				return TRUE;
			}
		}

		return E_FAIL;
	}

	HRESULT PostRender()
	{
		if (!_pIndexBuffer)
		{
			if (_vbDataList.size() > 0)
			{
				for (size_t i = 0; i < _pSubVertexBuffer.size(); i++)
				{
					UINT stride = sizeof(DefaultVertex);
					UINT offset = 0;
					_pImmediateContext->IASetVertexBuffers(0, 1, &_pSubVertexBuffer[i], &stride, &offset);
					_pImmediateContext->PSSetShaderResources(0, 1, &_pSubTexture[i]->_pShaderResourceView);

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

	HRESULT Release()
	{
		Object3D::Release();

		for (size_t i = 0; i < _pSubVertexBuffer.size(); i++)
		{
			if (_pSubVertexBuffer[i])
			{
				_pSubVertexBuffer[i]->Release();
			}
		}

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
	std::vector<FbxObject3D*> _pDrawObjects;

	HRESULT Init();
	HRESULT Frame();
	HRESULT Render();
	HRESULT Release();

	HRESULT Load(C_STR filename);

	void PreProcess(FbxNode* pFbxNode);
	void ParseMesh(FbxMesh* pFbxMesh);
	FbxVector2 ReadUVs(FbxMesh* pFbxMesh, FbxLayerElementUV* pUV, int posIndex, int uvIndex);
	FbxVector4 ReadNormals(FbxMesh* pFbxMesh, FbxLayerElementNormal* pNormal, int posIndex, int colorIndex);
	FbxColor ReadColors(FbxMesh* pFbxMesh, FbxLayerElementVertexColor* pVertexColor, int posIndex, int colorIndex);
	int GetSubMaterialIndex(int polygon, FbxLayerElementMaterial* pMaterial);
};

