#include "pch.h"
#include "Scene.h"
#include "Input.h"
#include "DxRT.h"
#include "DxState.h"
#include "Camera.h"
#include "Map.h"
#include "Quadtree.h"
#include "Actor.h"
#include "TextureBox.h"
#include "Cube.h"

HRESULT Scene::Init()
{
	// FBX
	//FbxLoader* pTest = new FbxLoader;
	//if (SUCCEEDED(pTest->Init()))
	//{
	//	pTest->Load("../../Resource/FBX/MultiCameras.fbx");
	//}

	//_pFbxObjects.push_back(pTest);


	FbxLoader* pRyan = new FbxLoader;
	if (SUCCEEDED(pRyan->Init()))
	{
		pRyan->Load("../../Resource/Ryan/Ryan.fbx");
	}

	_pFbxObjects.push_back(pRyan);

	W_STR defaultDir = L"../../Resource/FBX/";
	std::wstring shaderfilename = L"../../Resource/Shader/DefaultObject.hlsl";

	for (auto& fbx : _pFbxObjects)
	{
		for (size_t i = 0; i < fbx->_pDrawObjects.size(); i++)
		{
			MyObject* pObject = fbx->_pDrawObjects[i];
			std::wstring load = defaultDir + pObject->_textureName;
			if (pObject->_dataList.size() == 0)
			{
				pObject->CreateObject(_pd3dDevice, _pImmediateContext, shaderfilename, load);
			}
			else
			{
				for (int j = 0; j < pObject->_dataList.size(); j++)
				{
					MyObject* pSubObject = new MyObject;
					std::wstring subLoad = defaultDir + pObject->_textureList[j];
					if (pObject->_dataList[j].size() != 0)
					{
						pSubObject->_vertices = pObject->_dataList[j];
						pSubObject->CreateObject(_pd3dDevice, _pImmediateContext, shaderfilename, subLoad);
						pObject->_pDrawChild.push_back(pSubObject);
					}
				}
			}
		}
	}

	// ����Ʈ
	int width = rtClient.right / 5;
	int height = rtClient.bottom / 4;
	for (int i = 0; i < 4; i++)
	{
		_viewport[i].Width = width;
		_viewport[i].Height = height;
		_viewport[i].TopLeftX = rtClient.right - width;
		_viewport[i].TopLeftY = height * i;
		_viewport[i].MinDepth = 0.0f;
		_viewport[i].MaxDepth = 1.0f;
	}

	// ��
	_pMap = new Map;
	_pMap->Customize(256 + 1, 256 + 1);
	_pMap->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/DefaultObject.hlsl", L"../../../Resource/Map/Map.png");
	
	// ���̾�
	_pRyan = new Actor;
	_pRyan->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/DefaultObject.hlsl", L"../../../Resource/Ryan/Ryan.png");
	_pRyan->_world.Translation(0.0f, 0.0f, 0.0f);
	AddObject(_pRyan);
	
	// �ڽ�
	_pBox = new TextureBox;
	_pBox->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/DefaultObject.hlsl", L"../../../Resource/Box/Box.png");
	_pBox->_world.Translation(9.0f, 1.0f, 0.0f);
	AddObject(_pBox);
	
	_pBox2 = new TextureBox;
	_pBox2->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/DefaultObject.hlsl", L"../../../Resource/Box/Box.png");
	_pBox2->_world.Translation(10.0f, 1.0f, 2.0f);
	AddObject(_pBox2);
	
	// ť��
	_pCube = new Cube;
	_pCube->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Shape.hlsl", L"");
	_pCube->_world.Translation(-10.0f, 1.0f, 0.0f);
	AddObject(_pCube);

	// ���� ī�޶�
	_pMainCamera = new CameraDebug;
	_pMainCamera->CreateView(MyVector3(0.0f, 5.0f, -30.0f), MyVector3(0.0f, 0.0f, 0.0f), MyVector3(0.0f, 1.0f, 0.0f));
	_pMainCamera->CreateProjection(1.0f, 10000.0f, PI_DIVISION_4, RESOLUTION_RATIO);
	
	// ž ��
	MyVector3 position = MyVector3(0.0f, 10.0f, -0.1f);
	MyVector3 up(0.0f, 0.0f, 0.0f);
	_pCamera[0] = new Camera;
	_pCamera[0]->CreateView(position, _pRyan->_position, up);
	// ����Ʈ ��
	position = MyVector3(0.0f, 0.0f, -10.0f);
	_pCamera[1] = new Camera;
	_pCamera[1]->CreateView(position, _pRyan->_position, up);
	// ���̵� ��
	position = MyVector3(10.0f, 0.0f, 0.0f);
	_pCamera[2] = new Camera;
	_pCamera[2]->CreateView(position, _pRyan->_position, up);
	// ���� ��
	position = MyVector3(10.0f, 10.0f, -10.0f);
	_pCamera[3] = new Camera;
	_pCamera[3]->CreateView(position, _pRyan->_position, up);
	
	for (size_t i = 0; i < 4; i++)
	{
		_pCamera[i]->CreateProjection(1.0f, 100.0f, PI_DIVISION_4, (float)_viewport[i].Width / (float)_viewport[i].Height);
	}
	
	// ����Ʈ�� �°� ī�޶� ����
	for (size_t i = 0; i < 4; i++)
	{
		_pCamera[i]->SetObjectView(MyVector3{ -2.0f, -2.0f, -2.0f }, MyVector3{ 2.0f, 2.0f, 2.0f });
	}

	// ����Ʈ��
	_quadtree.CreateTree(_pMainCamera, _pMap);

	return TRUE;
}

HRESULT Scene::Frame()
{
	_quadtree.Frame();

	_pMainCamera->Frame();

	for (size_t i = 0; i < 4; i++)
	{
		_pCamera[i]->Frame();
	}

	for (auto& pObject : _pObjects)
	{
		pObject->Frame();
	}

	for (auto& pObject : _pFbxObjects)
	{
		pObject->Frame();
	}

	return TRUE;
}

HRESULT Scene::Render()
{
	_pImmediateContext->OMSetDepthStencilState(DxState::_pDefaultDepthStencil, 0xff);
	_pMap->SetMatrix(nullptr, &_pMainCamera->_view, &_pMainCamera->_projection);
	_quadtree.Render();

	// ������Ʈ
	for (auto& pObject : _pObjects)
	{
		// �������� �ø�
		HRESULT isRender = _pMainCamera->_frustum.ClassifyPoint(pObject->_position);
		if (SUCCEEDED(isRender))
		{
			pObject->SetMatrix(nullptr, &_pMainCamera->_view, &_pMainCamera->_projection);
			//pObject->Render();
		}
	}

	// FBX
	for (int iModel = 0; iModel < _pFbxObjects.size(); iModel++)
	{
		for (int iObj = 0; iObj < _pFbxObjects[iModel]->_pDrawObjects.size(); iObj++)
		{
			MyObject* pObject = _pFbxObjects[iModel]->_pDrawObjects[iObj];
			if (pObject->_pDrawChild.size() == 0)
			{
				MyMatrix world;
				world._41 = 100.0f * iModel;
				pObject->SetMatrix(nullptr,
					&_pMainCamera->_view,
					&_pMainCamera->_projection);
				pObject->Render();
			}
			else
			{
				for (int iSubObj = 0; iSubObj <
					pObject->_pDrawChild.size(); iSubObj++)
				{
					MyObject* pSubObj = pObject->_pDrawChild[iSubObj];
					MyMatrix world;
					world._41 = 100.0f * iModel;
					pSubObj->SetMatrix(nullptr,
						&_pMainCamera->_view,
						&_pMainCamera->_projection);
					pSubObj->Render();
				}
			}

		}
	}

	// ����Ʈ
	D3D11_VIEWPORT oldViewport[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];
	UINT viewports = 1;
	_pImmediateContext->RSGetViewports(&viewports, oldViewport);

	for (size_t i = 0; i < 4; i++)
	{
		_pImmediateContext->RSSetViewports(1, &_viewport[i]);
		_pRyan->SetMatrix(nullptr, &_pCamera[i]->_view, &_pCamera[i]->_projection);
		_pRyan->Render();
	}
	
	_pImmediateContext->RSSetViewports(viewports, oldViewport);
	_pImmediateContext->RSSetState(DxState::_pDefaultRSSolid);

	return TRUE;
}

HRESULT Scene::Release()
{
	_quadtree.Release();

	for (auto& pObject : _pObjects)
	{
		pObject->Release();
		delete pObject;
	}

	for (auto& pObject : _pFbxObjects)
	{
		pObject->Release();
		delete pObject;
	}

	for (int i = 0; i < 4; i++)
	{
		_pCamera[i]->Release();
		delete _pCamera[i];
		_pCamera[i] = nullptr;
	}

	return TRUE;
}

void Scene::CreateScene(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmedtateContext)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pImmedtateContext;
}

void Scene::AddObject(Object* pObject)
{
	_pObjects.push_back(pObject);
}
