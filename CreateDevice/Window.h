#pragma once

#include "Graphics.h"

class Window
{
private:
	HWND _hWnd;		// ������ �ڵ�
	RECT _rtWindow;	// ������ ����
	RECT _rtClient;	// Ŭ���̾�Ʈ ����

protected:
	Graphics _graphics;

public:
	// ������
	Window();
	// �Ҹ���
	virtual ~Window();

	// �ʱ�ȭ
	virtual HRESULT Init(HINSTANCE hInstance, const WCHAR* title, UINT width, UINT height);
	// ������ ���
	virtual HRESULT Frame();
	// ����
	virtual HRESULT Render();
	// �޸� �Ҹ� �� ����
	virtual HRESULT Release();

	// ������ ����
	HRESULT InitWindow(HINSTANCE hInstance, const WCHAR* title, UINT width, UINT height);
	// ������ ��ġ�� ȭ�� �߾����� �̵�
	void CenterWindow();

	// ������ �ڵ�
	const HWND GetHWND() const;

	// ������ ���ν���
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

