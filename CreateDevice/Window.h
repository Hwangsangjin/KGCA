#pragma once

class Window
{
private:
	HINSTANCE _hInstance;	// �ν��Ͻ� �ڵ�
	HWND _hWnd;				// ������ �ڵ�
	RECT _rtWindow;			// ������ ����
	RECT _rtClient;			// Ŭ���̾�Ʈ ����

public:
	// �ʱ�ȭ
	HRESULT Init(const WindowInfo& gInfo);
	// ������
	HRESULT Frame();
	// ����
	HRESULT Render();
	// �޸� ����
	HRESULT Release();

	// ������
	Window();

	// ������ ����
	HRESULT InitWindow(const WindowInfo& gInfo);
	// ������ ��ġ�� ȭ�� �߾����� �̵�
	void CenterWindow();

	// �޽��� ���ν���
	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
};
