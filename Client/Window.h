#pragma once

class Window
{
public:
	// ������ ����
	WindowInfo _info;

	// ������
	Window();
	// �Ҹ���
	~Window() {}

	// ������ ����
	HRESULT InitWindow(const WindowInfo& info);
	// ������ ��ġ�� ȭ�� �߾����� �̵�
	void CenterWindow(const WindowInfo& info);
	// �ʱ�ȭ
	HRESULT Init(const WindowInfo& info);
	// ������ ���
	HRESULT Frame();
	// ����
	HRESULT Render();
	// �޸� �Ҹ� �� ��ü ����
	HRESULT Release();
	// ������ ���ν���
	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
};

