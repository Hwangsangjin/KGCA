#pragma once

#include <windows.h>

class Window
{
public:
	HINSTANCE _hInstance;	// �ν��Ͻ� �ڵ�
	HWND _hWnd;				// ������ �ڵ�
	RECT bound;	// ������ ����
	RECT _client;	// Ŭ���̾�Ʈ ����
	UINT _width;		// Ŭ���̾�Ʈ ���� ���� ũ��
	UINT _height;	// Ŭ���̾�Ʈ ���� ���� ũ��

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
	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
};

