#pragma once

#include "Window.h"
#include "Timer.h"

class Core : public Window
{
private:
	Timer _timer;

	// ���� �÷���
	bool _isRunning = true;

	// �ھ� �Լ�
	HRESULT CoreInit();
	HRESULT CoreFrame();
	HRESULT CorePreRender();
	HRESULT CoreRender();
	HRESULT CorePostRender();
	HRESULT CoreRelease();

public:
	Core() = default;
	virtual ~Core() = default;

	// �ʱ�ȭ
	virtual HRESULT Init() override;
	// ������ ���
	virtual HRESULT Frame() override;
	// ����
	virtual HRESULT Render() override;
	// �޸� ����
	virtual HRESULT Release() override;
	// ����
	virtual HRESULT Run() final;
};

