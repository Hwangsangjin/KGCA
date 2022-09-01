#pragma once

#include "Window.h"

class Application
{
private:
	Window _window;

public:
	// �ʱ�ȭ
	HRESULT Init(const WindowInfo& gInfo);
	// �ǽð� ���
	HRESULT Frame();
	// �ǽð� ������
	HRESULT Render();
	// �Ҹ� �� ����
	HRESULT Release();
};