#pragma once

#include "FbxObject3D.h"

struct ActionTable
{
	UINT startFrame;
	UINT endFrame;
	float tickPerFrame;
	float FrameSpeed;
	bool isLoop;

	ActionTable()
	{
		isLoop = false;
	}
};

class Actor
{
public:
	//ID3D11Device* _pd3dDevice = nullptr;
	//ID3D11DeviceContext* _pImmediateContext = nullptr;

	UINT _fbxListIndex;
	class FbxData* _pFbxData = nullptr;
	class FbxData* _pFbxActionData = nullptr;

	std::map<std::wstring, FbxData*> _pFbxDatas;
	std::map<std::wstring, ActionTable> _actions;

	BoneBuffer _cbDataBone;
	std::vector<BoneBuffer> _cbDrawGeometry;

	ID3D11Buffer* _pConstantBufferAnimBone;
	std::vector<ID3D11Buffer*> _pConstantBufferSkinBone;

	DxMatrix _world;
	DxMatrix _view;
	DxMatrix _projection;

	ActionTable _currentAction;
	AnimScene _animScene;
	float _animFrame = 0.0f;
	UINT _startFrame;
	UINT _endFrame;
	float _animInverse = 1.0f;
	float _animSpeed = 1.0f;

	Actor() {}
	virtual ~Actor() {}

	HRESULT Init();
	HRESULT Frame();
	HRESULT Render(ID3D11DeviceContext* pImmediateContext);
	HRESULT Release();

	//HRESULT SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	HRESULT CreateConstantBuffer(ID3D11Device* pd3dDevice);
	void UpdateAnimation(ID3D11DeviceContext* pImmediateContext);
	void SetMatrix(DxMatrix* pWorld, DxMatrix* pView, DxMatrix* pProjection);

	class Shape* _pDirectionLine = nullptr;
};

