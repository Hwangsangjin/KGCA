#include "pch.h"
#include "FbxObject3D.h"
#include "fbxsdk.h"
#include "TextureManager.h"

HRESULT FbxObject3D::Init()
{
	Object3D::Init();

	return TRUE;
}

HRESULT FbxObject3D::Frame()
{
	Object3D::Frame();

	return TRUE;
}

HRESULT FbxObject3D::Render()
{
	Object3D::Render();

	return TRUE;
}

HRESULT FbxObject3D::Release()
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

void FbxObject3D::SetParent(FbxObject3D* pParentNode)
{
	pParentNode->_pFbxChilds.push_back(this);
	_pParent = pParentNode;
}

void FbxObject3D::CreateVertexData()
{
}

HRESULT FbxObject3D::CreateVertexBuffer()
{
	if (_vbDataList.size() > 0)
	{
		_pSubVertexBuffer.resize(_vbDataList.size());
		for (size_t i = 0; i < _vbDataList.size(); i++)
		{
			if (_vbDataList[i].size() > 0)
			{
				_pSubVertexBuffer[i] = DX::CreateVertexBuffer(_pd3dDevice, &_vbDataList[i].at(0), _vbDataList[i].size(), sizeof(DefaultVertex));
			}
		}
	}
	else
	{
		Object3D::CreateVertexBuffer();
	}

	return TRUE;
}

HRESULT FbxObject3D::CreateIndexBuffer()
{
	return TRUE;
}

HRESULT FbxObject3D::LoadTexture(W_STR textureFile)
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
		_pTexture = TEXTURE->Load(textureFile);
		if (_pTexture)
		{
			_pShaderResourceView = _pTexture->_pShaderResourceView;

			return TRUE;
		}
	}

	return E_FAIL;
}

HRESULT FbxObject3D::PostRender()
{
	if (!_pIndexBuffer)
	{
		if (_vbDataList.size() > 0)
		{
			for (size_t i = 0; i < _pSubVertexBuffer.size(); i++)
			{
				if (_vbDataList[i].size() <= 0)
				{
					continue;
				}

				UINT stride = sizeof(DefaultVertex);
				UINT offset = 0;
				_pImmediateContext->IASetVertexBuffers(0, 1, &_pSubVertexBuffer[i], &stride, &offset);

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
