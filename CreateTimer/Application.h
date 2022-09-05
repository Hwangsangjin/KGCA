#pragma once

#include "GameCore.h"

class Application : public GameCore
{
public:
	// �ʱ�ȭ
	HRESULT Init(HINSTANCE hInstance, const WCHAR* title, UINT width, UINT height);
	// ������
	HRESULT Frame();
	// ����
	HRESULT Render();
	// ������
	HRESULT Release();
};