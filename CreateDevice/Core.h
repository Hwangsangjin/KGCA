#pragma once

#include "Window.h"

class Core : public Window
{
private:
	// ���� �÷���
	bool _isRun = true;

	// �ھ� �Լ�
	HRESULT CInit();
	HRESULT CFrame();
	HRESULT CPreRender();
	HRESULT CRender();
	HRESULT CPostRender();
	HRESULT CRelease();

public:
	Core() = default;
	virtual ~Core() = default;

	// �ʱ�ȭ
	virtual HRESULT Init() override;
	// ������
	virtual HRESULT Frame() override;
	// ����
	virtual HRESULT Render() override;
	// ������
	virtual HRESULT Release() override;
	// ����
	virtual HRESULT Run() override;
};

