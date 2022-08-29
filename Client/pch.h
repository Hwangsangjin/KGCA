// pch.h: �̸� �����ϵ� ��� �����Դϴ�.
// �Ʒ� ������ ������ �� ���� �����ϵǾ�����, ���� ���忡 ���� ���� ������ ����մϴ�.
// �ڵ� ������ �� ���� �ڵ� �˻� ����� �����Ͽ� IntelliSense ���ɿ��� ������ ��Ĩ�ϴ�.
// �׷��� ���⿡ ������ ������ ���� �� ������Ʈ�Ǵ� ��� ��� �ٽ� �����ϵ˴ϴ�.
// ���⿡ ���� ������Ʈ�� ������ �߰����� ������. �׷��� ������ ���ϵ˴ϴ�.

#ifndef PCH_H
#define PCH_H

// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#define WIN32_LEAN_AND_MEAN

// ���⿡ �̸� �������Ϸ��� ��� �߰�
#include <assert.h>
#include <Windows.h>
#include <d3d11.h>
#include <dxerr.h>
#include <dxgi.h>
#include <d3dcompiler.h>

struct WindowInfo
{
	HINSTANCE hInstance;	// �ν��Ͻ� �ڵ�
	HWND hWnd;				// ������ �ڵ�
	int nCmdShow;			// ������ ��Ʈ�� ����
	const TCHAR* title;		// Ÿ��Ʋ
	RECT bound;				// ������ ����
	RECT client;			// Ŭ���̾�Ʈ ����
	UINT width;				// Ŭ���̾�Ʈ ���� ���� ũ��
	UINT height;			// Ŭ���̾�Ʈ ���� ���� ũ��
};

#endif //PCH_H
