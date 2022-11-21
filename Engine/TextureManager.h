#pragma once

#include "Texture.h"

class TextureManager
{
	DECLARE_SINGLE(TextureManager);

private:
	ID3D11Device* device_ = nullptr;
	ID3D11DeviceContext* device_context_ = nullptr;

	std::map<std::wstring, Texture*> _textures;

public:
	// �ʱ�ȭ
	HRESULT Init();
	// ������ ���
	HRESULT Frame();
	// ����
	HRESULT Render();
	// �޸� ����
	HRESULT Release();

	// ����̽� ����
	HRESULT SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

	// �ؽ�ó ���� �ε�
	Texture* Load(std::wstring textureFile);
	// �ؽ�ó ���� �˻�
	Texture* Find(std::wstring textureFile);
	// ���ϸ� ����
	T_STR GetSplitName(std::wstring fullPath);
	T_STR GetSplitName(std::string fullPath);
};

