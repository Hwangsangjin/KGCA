#pragma once

#include "Device.h"

class Window : public Device
{
private:
	HWND _hWnd;		// ������ �ڵ�
	RECT _rtWindow;	// ������ ����
	RECT _rtClient;	// Ŭ���̾�Ʈ ����

public:
	Window();
	virtual ~Window() = default;

	// �ʱ�ȭ
	virtual HRESULT Init() override;
	// ������ ���
	virtual HRESULT Frame() override;
	// ����
	virtual HRESULT Render() override;
	// �޸� ����
	virtual HRESULT Release() override;
	// ����
	virtual HRESULT Run();

	// ������ ����
	HRESULT SetWindow(HINSTANCE hInstance, const WCHAR* title, UINT width, UINT height);
	// ������ ��ġ�� ȭ�� �߾����� �̵�
	void CenterWindow();

	// ������ �ڵ�
	const HWND GetHWND() const;
	// Ŭ���̾�Ʈ ����
	const RECT GetRECT() const;

	// �޽��� ���ν���
	LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

