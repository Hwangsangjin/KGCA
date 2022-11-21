#pragma once

#include "Window.h"

class Core : public Window
{
private:
	// ���� �÷���
	bool is_Running_ = true;

public:
	// ������, �Ҹ���
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
	virtual HRESULT CreateResource() override;
	virtual HRESULT DeleteResource() override;

	// �ھ� �Լ�
	HRESULT CoreInit();
	HRESULT CoreFrame();
	HRESULT CorePreRender();
	HRESULT CoreRender();
	HRESULT CorePostRender();
	HRESULT CoreRelease();
};

