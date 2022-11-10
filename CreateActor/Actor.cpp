#include "pch.h"
#include "Actor.h"
#include "Shape.h"
#include "Timer.h"
#include "FbxData.h"

HRESULT Actor::Init()
{
	//_pDirectionLine = new ShapeDirectionLine;
	//_pDirectionLine->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Shape.hlsl", L"");

	return TRUE;
}

HRESULT Actor::Frame()
{
	return TRUE;
}

HRESULT Actor::Render(ID3D11DeviceContext* pImmediateContext)
{
	//_pDirectionLine->Render();

	pImmediateContext->VSSetConstantBuffers(1, 1, &_pConstantBufferAnimBone);
	for (size_t iMesh = 0; iMesh < _pFbxData->_pDrawObjects.size(); iMesh++)
	{
		if (_pFbxData->_pDrawObjects[iMesh]->_isSkinned)
		{
			pImmediateContext->VSSetConstantBuffers(1, 1, &_pConstantBufferSkinBone[iMesh]);
		}

		_pFbxData->_pDrawObjects[iMesh]->SetMatrix(&_world, &_view, &_projection);
		_pFbxData->_pDrawObjects[iMesh]->Render();
	}

	return TRUE;
}

HRESULT Actor::Release()
{
	if (_pDirectionLine)
	{
		_pDirectionLine->Release();
		delete _pDirectionLine;
		_pDirectionLine = nullptr;
	}

	SAFE_RELEASE(_pConstantBufferAnimBone);
	
	for (auto& bone : _pConstantBufferSkinBone)
	{
		SAFE_RELEASE(bone);
	}

	return TRUE;
}

//HRESULT Actor::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
//{
//	_pd3dDevice = pd3dDevice;
//	_pImmediateContext = pImmediateContext;
//
//	return TRUE;
//}

HRESULT Actor::CreateConstantBuffer(ID3D11Device* pd3dDevice)
{
	for (size_t iBone = 0; iBone < 255; iBone++)
	{
		D3DXMatrixIdentity(&_cbDataBone.boneMatrix[iBone]);
	}

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(BoneBuffer) * 1;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &_cbDataBone;
	HR(pd3dDevice->CreateBuffer(&bd, &sd, &_pConstantBufferAnimBone));

	_pConstantBufferSkinBone.resize(_pFbxData->_pDrawObjects.size());
	_cbDrawGeometry.resize(_pFbxData->_pDrawObjects.size());

	for (size_t iMesh = 0; iMesh < _pFbxData->_pDrawObjects.size(); iMesh++)
	{
		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = &_cbDataBone;
		HR(pd3dDevice->CreateBuffer(&bd, &sd, &_pConstantBufferSkinBone[iMesh]));
	}

	return TRUE;
}

void Actor::UpdateAnimation(ID3D11DeviceContext* pImmediateContext)
{
	_animFrame = _animFrame + _animSpeed * _animScene.frameSpeed * DELTA_TIME;
	if (_animFrame > _animScene.endFrame || _animFrame < _animScene.startFrame)
	{
		_animFrame = min(_animFrame, _animScene.endFrame);
		_animFrame = max(_animFrame, _animScene.startFrame);

		if (_animFrame == _animScene.endFrame)
		{
			_animFrame = _animScene.startFrame;
		}
	}

	if (_currentAction.isLoop)
	{
		if (_animFrame >= _currentAction.endFrame)
		{
			_animFrame = _currentAction.startFrame;
		}
	}
	else
	{
		if (_animFrame >= _currentAction.endFrame)
		{
			_animFrame = _currentAction.startFrame;
		}
	}

	if (_pFbxActionData)
	{
		_pFbxActionData->UpdateSkeleton(pImmediateContext, _animFrame, _cbDataBone);
		_pFbxData->UpdateSkinning(pImmediateContext, _cbDataBone, _cbDrawGeometry);
	}
	else
	{
		_pFbxData->UpdateSkeleton(pImmediateContext, _animFrame, _cbDataBone);
		_pFbxActionData->UpdateSkinning(pImmediateContext, _cbDataBone, _cbDrawGeometry);
	}

	for (size_t iBone = 0; iBone < _pConstantBufferSkinBone.size(); iBone++)
	{
		pImmediateContext->UpdateSubresource(_pConstantBufferSkinBone[iBone], 0, nullptr, &_cbDrawGeometry[iBone], 0, 0);
	}

	for (size_t iBone = 0; iBone < _pFbxData->_pDrawObjects.size(); iBone++)
	{
		D3DXMatrixTranspose(&_cbDataBone.boneMatrix[iBone], &_cbDataBone.boneMatrix[iBone]);
	}

	pImmediateContext->UpdateSubresource(_pConstantBufferAnimBone, 0, nullptr, &_cbDataBone, 0, 0);
}

void Actor::SetMatrix(DxMatrix* pWorld, DxMatrix* pView, DxMatrix* pProjection)
{
	if (pWorld)
	{
		_world = *pWorld;
	}

	if (pView)
	{
		_view = *pView;
	}

	if (pProjection)
	{
		_projection = *pProjection;
	}

	DxMatrix lineWorld;
	D3DXMatrixScaling(&lineWorld, 2.0f, 2.0f, 2.0f);
	lineWorld = lineWorld * _world;

	if (_pDirectionLine)
	{
		_pDirectionLine->SetMatrix(&lineWorld, pView, pProjection);
	}
}
