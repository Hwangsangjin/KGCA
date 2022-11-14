#pragma once

#include "Window.h"
#include "Input.h"
#include "Timer.h"
#include "Writer.h"
#include "DxRT.h"
#include "DxState.h"
#include "SoundManager.h"
#include "ShaderManager.h"
#include "SpriteManager.h"
#include "TextureManager.h"

class Core : public Window
{
public:
	// ���� �÷���
	bool _isRun = true;

	// �ھ� �Լ�
	HRESULT CoreInit();
	HRESULT CoreFrame();
	HRESULT CorePreRender();
	HRESULT CoreRender();
	HRESULT CorePostRender();
	HRESULT CoreRelease();

	// ��Ʈ
	Writer _writer;

	// ���
	Object _background;

	// ����Ÿ��
	DxRT _rendertarget;

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

	// ��
	HRESULT Tool();
};

