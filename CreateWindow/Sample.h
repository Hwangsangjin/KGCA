#pragma once

#include "Window.h"

class Sample : public Window
{
public:
	// �ʱ�ȭ
	HRESULT Init();
	// �ǽð� ���
	HRESULT Frame();
	// �ǽð� ������
	HRESULT Render();
	// �Ҹ� �� ����
	HRESULT Release();
};

