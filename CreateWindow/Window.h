#pragma once

class Window
{
private:
	HINSTANCE _hInstance;	// �ν��Ͻ� �ڵ�
	HWND _hWnd;				// ������ �ڵ�
	RECT _rtWindow;			// ������ ����
	RECT _rtClient;			// Ŭ���̾�Ʈ ����

public:
	// ������
	Window();

	// ������ ����
	HRESULT InitWindow(const IWND& iWnd);
	// ������ ��ġ�� ȭ�� �߾����� �̵�
	void CenterWindow();

	// �ʱ�ȭ
	HRESULT Init(const IWND& iWnd);
	// ������ ���
	HRESULT Frame();
	// ����
	HRESULT Render();
	// �޸� �Ҹ� �� ����
	HRESULT Release();

	// �޽��� ���ν���
	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
};

