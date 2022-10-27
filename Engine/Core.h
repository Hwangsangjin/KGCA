#pragma once

#include "Window.h"
#include "Input.h"
#include "Timer.h"
#include "Font.h"
#include "DxRT.h"
#include "DxState.h"
#include "SoundManager.h"
#include "ShaderManager.h"
#include "SpriteManager.h"
#include "TextureManager.h"

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

protected:
	// ��Ʈ
	Font _font;

	// ���
	Object _background;

	// ����Ÿ��
	DxRT _rendertarget;

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

	// ���ҽ� ����, ����
	virtual HRESULT CreateDXResource() override;
	virtual HRESULT DeleteDXResource() override;
};

