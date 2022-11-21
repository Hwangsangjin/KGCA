#pragma once

#include "Device.h"

class Window : public Device
{
protected:
	HWND hWnd_ = nullptr;				// ������ �ڵ�
	RECT window_rect_ = { 0, 0, 0, 0 };	// ������ ����
	RECT client_rect_ = { 0, 0, 0, 0 };	// Ŭ���̾�Ʈ ����

public:
	// ������, �Ҹ���
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

	// ������ �ڵ�
	void SetHandle(HWND hWnd);

	// ������ ��ġ�� ȭ�� �߾����� �̵�
	void CenterWindow();

	// �޽��� ���ν���
	LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

