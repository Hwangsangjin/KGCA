#pragma once

#include "Window.h"
#include "Timer.h"
#include "Font.h"
#include "Input.h"

class Core : public Window
{
private:
	// ���� �÷���
	bool _isRun = true;

	// �ھ� �Լ�
	HRESULT CoreInit();
	HRESULT CoreFrame();
	HRESULT CorePreRender();
	HRESULT CoreRender();
	HRESULT CorePostRender();
	HRESULT CoreRelease();

public:
	// ��Ʈ
	Font _font;
	IDXGISurface1* _pBackBuffer;

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

