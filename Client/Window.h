#pragma once

#include <windows.h>

class Window
{
public:
	HINSTANCE _hInstance;	// �ν��Ͻ� �ڵ�
	HWND _hWnd;				// ������ �ڵ�
	DWORD _dwWindowStyle;	// ������ ��Ÿ��
	RECT _rcWindowBounds;	// ������ ����
	RECT _rcWindowClient;	// Ŭ���̾�Ʈ ����
	UINT _iWindowWidth;		// Ŭ���̾�Ʈ ���� ���� ũ��
	UINT _iWindowHeight;	// Ŭ���̾�Ʈ ���� ���� ũ��

	// ������
	Window();
	// �Ҹ���
	virtual ~Window() {}

	// ������ ����
	bool InitWindow(HINSTANCE hInstance, int nCmdShow, const TCHAR* strWindowTitle);
	// ������ ��ġ�� ȭ�� �߾����� �̵�
	void CenterWindow(HWND hwnd);
	// �ʱ�ȭ
	virtual bool Init();
	// ������ ���
	virtual bool Frame();
	// ����
	virtual bool Render();
	// �޸� �Ҹ� �� ��ü ����
	virtual bool Release();
	// ����
	virtual bool Run();
	// ������ ���ν���
	virtual LRESULT WndProc(HWND, UINT, WPARAM, LPARAM);
};

