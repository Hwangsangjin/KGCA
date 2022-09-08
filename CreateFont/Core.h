#pragma once

#include "Window.h"
#include "Timer.h"
#include "Font.h"

class Core : public Window
{
private:
	// ���� �÷���
	bool _isRun = true;

	// ��Ʈ
	Font _font;
	IDXGISurface1* _pBackBuffer;

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

