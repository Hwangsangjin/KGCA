#pragma once

#include "Window.h"
#include <memory>

class Sample : public Window
{
public:
	// ������, �Ҹ���
	Sample() = default;
	virtual ~Sample() = default;

	// �ʱ�ȭ
	virtual HRESULT Init() override;
	// ������ ���
	virtual HRESULT Frame() override;
	// ����
	virtual HRESULT Render() override;
	// �޸� ����
	virtual HRESULT Release() override;

	// ���ҽ� ����, ����
	virtual HRESULT CreateResource() override;
	virtual HRESULT DeleteResource() override;
};

