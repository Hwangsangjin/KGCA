#pragma once

class Window
{
private:
	RECT _rtWindow;			// ������ ����
	RECT _rtClient;			// Ŭ���̾�Ʈ ����

public:
	// �ʱ�ȭ
	HRESULT Init(const IWND& iWnd);
	// ������
	HRESULT Frame();
	// ����
	HRESULT Render();
	// �޸� ����
	HRESULT Release();

	// ������ ����
	HRESULT InitWindow(const IWND& iWnd);
	// ������ ��ġ�� ȭ�� �߾����� �̵�
	void CenterWindow();

	// ������ �ڵ�
	 HWND GetHWND();

	// ������ ���ν���
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

