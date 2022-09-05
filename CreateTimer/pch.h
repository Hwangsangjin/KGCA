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

#include "MathModule.h"

#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"

#include <chrono>

#endif //PCH_H
