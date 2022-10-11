#pragma once

#include "Window.h"
#include "Input.h"
#include "Timer.h"
#include "Font.h"
#include "DxState.h"
#include "SoundManager.h"
#include "ShaderManager.h"
#include "SpriteManager.h"
#include "TextureManager.h"

class Core : public Window
{
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

protected:
	// ��Ʈ
	Font _font;

private:
	// �ھ� �Լ�
	HRESULT CoreInit();
	HRESULT CoreFrame();
	HRESULT CorePreRender();
	HRESULT CoreRender();
	HRESULT CorePostRender();
	HRESULT CoreRelease();

	// ���� �÷���
	bool _isRun = true;
};

