#pragma once

#include "Window.h"

class Application : public Window
{
public:
	// �ʱ�ȭ
	bool Init();
	// �ǽð� ���
	bool Frame();
	// �ǽð� ������
	bool Render();
	// �Ҹ� �� ����
	bool Release();
};

