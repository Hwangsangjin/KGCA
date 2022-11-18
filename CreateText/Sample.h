#pragma once

#include "Window.h"

class Sample : public Window
{
public:
	// �ؽ�Ʈ
	Microsoft::WRL::ComPtr<class Text> _pText;

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
};

