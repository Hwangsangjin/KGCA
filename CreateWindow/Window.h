#pragma once

class Window
{
public:
	HINSTANCE _hInstance;	// �ν��Ͻ� �ڵ�
	HWND _hWnd;				// ������ �ڵ�
	RECT _rtWindow;			// ������ ����
	RECT _rtClient;			// Ŭ���̾�Ʈ ����

	// ������
	Window();
	// �Ҹ���
	virtual ~Window() {}

	// ������ ����
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, const WCHAR* title, UINT width, UINT height);
	// ������ ��ġ�� ȭ�� �߾����� �̵�
	void CenterWindow(HWND hWnd);
	// �ʱ�ȭ
	virtual HRESULT Init();
	// ������ ���
	virtual HRESULT Frame();
	// ����
	virtual HRESULT Render();
	// �޸� �Ҹ� �� ����
	virtual HRESULT Release();
	// �޽��� ���ν���
	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	// ����
	HRESULT Run();
};

