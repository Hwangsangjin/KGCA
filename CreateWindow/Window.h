#pragma once

#include <Windows.h>
#include <assert.h>

class Window
{
protected:
	HWND _hWnd;		// ������ �ڵ�
	RECT _rtWindow;	// ������ ����
	RECT _rtClient;	// Ŭ���̾�Ʈ ����
	UINT _width;	// Ŭ���̾�Ʈ ���� ���� ũ��
	UINT _height;	// Ŭ���̾�Ʈ ���� ���� ũ��

public:
	Window();
	virtual ~Window() = default;

	// �ʱ�ȭ
	virtual HRESULT Init();
	// ������ ���
	virtual HRESULT Frame();
	// ����
	virtual HRESULT Render();
	// �޸� ����
	virtual HRESULT Release();
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

