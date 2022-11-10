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
	for (size_t i = 0; i < _pSubVertexBuffer.size(); i++)
	{
		if (_pSubVertexBuffer[i])
		{
			_pSubVertexBuffer[i]->Release();
			_pSubVertexBuffer[i] = nullptr;
		}
	}
	_pSubVertexBuffer.clear();

	Object3D::Release();

	return TRUE;
}

void FbxObject3D::SetParent(FbxObject3D* pParentNode)
{
	pParentNode->_pFbxChilds.push_back(this);
	_pParent = pParentNode;
}

DxMatrix FbxObject3D::Interpolate(float frame, AnimScene animScene)
{
	DxMatrix identityMatrix;
	D3DXMatrixIdentity(&identityMatrix);
	if (_animTracks.size() == 0)
	{
		return identityMatrix;
	}

	AnimTrack a, b;
	a = _animTracks[max(animScene.startFrame, frame + 0)];
	b = _animTracks[min(animScene.endFrame, frame + 1)];
	if (a.frame == b.frame)
	{
		return _animTracks[frame].animMatrix;
	}

	float t = (frame - a.frame) * (b.frame - a.frame);
	DxVector3 position;
	D3DXVec3Lerp(&position, &a.t, &b.t, t);
	DxVector3 scale;
	D3DXVec3Lerp(&scale, &a.s, &b.s, t);
	DxQuaternion rotation;
	D3DXQuaternionSlerp(&rotation, &a.r, &b.r, t);

	DxMatrix scaleMatrix;
	D3DXMatrixScaling(&scaleMatrix, scale.x, scale.y, scale.z);
	DxMatrix rotationMatrix;
	D3DXMatrixRotationQuaternion(&rotationMatrix, &rotation);

	DxMatrix currentMatrix = scaleMatrix * rotationMatrix;
	currentMatrix._41 = position.x;
	currentMatrix._42 = position.y;
	currentMatrix._43 = position.z;

	return currentMatrix;
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

HRESULT FbxSkinningObject3D::Init()
{
	FbxObject3D::Init();

	return TRUE;
}

HRESULT FbxSkinningObject3D::Frame()
{
	FbxObject3D::Frame();

	return TRUE;
}

HRESULT FbxSkinningObject3D::Render()
{
	FbxObject3D::Render();

	return TRUE;
}

HRESULT FbxSkinningObject3D::Release()
{
	SAFE_RELEASE(_pConstantBufferSkinBone);
	SAFE_RELEASE(_pVertexBufferIW);

	for (size_t i = 0; i < _pSubVertexBufferIW.size(); i++)
	{
		if (_pSubVertexBufferIW[i])
		{
			_pSubVertexBufferIW[i]->Release();
			_pSubVertexBufferIW[i] = nullptr;
		}
	}
	_pSubVertexBufferIW.clear();

	FbxObject3D::Release();

	return TRUE;
}

HRESULT FbxSkinningObject3D::CreateConstantBuffer()
{
	Object3D::CreateConstantBuffer();

	for (size_t i = 0; i < 255; i++)
	{
		D3DXMatrixIdentity(&_cbDataBone.boneMatrix[i]);
	}

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(BoneBuffer) * 1;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &_cbDataBone;
	HR(_pd3dDevice->CreateBuffer(&bd, &sd, &_pConstantBufferSkinBone));

	return TRUE;
}

HRESULT FbxSkinningObject3D::CreateVertexBuffer()
{
	FbxObject3D::CreateVertexBuffer();

	if (_vbDataListIW.size() > 0)
	{
		_pSubVertexBufferIW.resize(_vbDataListIW.size());
		for (size_t i = 0; i < _vbDataListIW.size(); i++)
		{
			if (_vbDataListIW[i].size() > 0)
			{
				_pSubVertexBufferIW[i] = DX::CreateVertexBuffer(_pd3dDevice, &_vbDataListIW[i].at(0), _vbDataListIW[i].size(), sizeof(IndexWeightVertex));
			}
		}
	}
	else
	{
		_pVertexBufferIW = DX::CreateVertexBuffer(_pd3dDevice, &_vertexListIW.at(0), _vertexListIW.size(), sizeof(IndexWeightVertex));
	}

	return TRUE;
}

HRESULT FbxSkinningObject3D::CreateInputLayout()
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

	return TRUE;
}

HRESULT FbxSkinningObject3D::PostRender()
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

				UINT stride[2] = { sizeof(DefaultVertex), sizeof(IndexWeightVertex) };
				UINT offset[2] = { 0, 0 };
				ID3D11Buffer* buffer[2] = { _pSubVertexBuffer[i],_pSubVertexBufferIW[i] };
				_pImmediateContext->IASetVertexBuffers(0, 2, buffer, stride, offset);

				if (_pSubTexture.size() > 0 && _pSubTexture[i])
				{
					_pImmediateContext->PSSetShaderResources(0, 1, &_pSubTexture[i]->_pShaderResourceView);
				}

				_pImmediateContext->Draw(_vbDataList[i].size(), 0);
			}
		}
		else
		{
			UINT stride[2] = { sizeof(DefaultVertex), sizeof(IndexWeightVertex) };
			UINT offset[2] = { 0, 0 };
			ID3D11Buffer* buffer[2] = { _pVertexBuffer,_pVertexBufferIW };
			_pImmediateContext->IASetVertexBuffers(0, 2, buffer, stride, offset);
			_pImmediateContext->Draw(_vertices.size(), 0);
		}
	}
	else
	{
		_pImmediateContext->DrawIndexed(_face * 3, 0, 0);
	}

	return TRUE;
}