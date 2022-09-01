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
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

struct IWND
{
	HINSTANCE hInstance;	// �ν��Ͻ� �ڵ�
	int nCmdShow;			// ������ ��Ʈ�� ����
	const WCHAR* title;		// Ÿ��Ʋ
	UINT width;				// Ŭ���̾�Ʈ ���� ���� ũ��
	UINT height;			// Ŭ���̾�Ʈ ���� ���� ũ��
};

extern HWND hWnd;			// ������ �ڵ�
extern IWND iWnd;			// ������ ����

#endif //PCH_H
