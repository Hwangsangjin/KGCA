#pragma once

#include "Window.h"
#include "Timer.h"
#include "Write.h"

class Core : public Window
{
private:
	HWND _hWnd;
	RECT _rtClient;

	Timer _timer;
	Write _write;
	IDXGISurface1* _pBackBuffer;

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

