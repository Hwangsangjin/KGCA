#pragma once

#include "Window.h"

class Application : public Window
{
public:
	// �ʱ�ȭ
	HRESULT Init(HINSTANCE hInstance, const WCHAR* title, UINT width, UINT height);
	// �ǽð� ���
	HRESULT Frame();
	// �ǽð� ������
	HRESULT Render();
	// �Ҹ� �� ����
	HRESULT Release();
};