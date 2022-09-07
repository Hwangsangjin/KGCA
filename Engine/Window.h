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
	// �Ҹ���
	virtual ~Window();

	// �ʱ�ȭ
	virtual HRESULT Init();
	// ������ ���
	virtual HRESULT Frame();
	// ����
	virtual HRESULT Render();
	// �޸� �Ҹ� �� ����
	virtual HRESULT Release();
	// ����
	virtual HRESULT Run();

	// ������ ����
	HRESULT SetWindow(HINSTANCE hInstance, const WCHAR* title, UINT width, UINT height);
	// ������ ��ġ�� ȭ�� �߾����� �̵�
	void CenterWindow();

	// �ν��Ͻ� �ڵ�
	const HINSTANCE GetHINSTANCE() const;

	// ������ �ڵ�
	const HWND GetHWND() const;

	// ������ ���ν���
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

