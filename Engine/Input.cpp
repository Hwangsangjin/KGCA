#include "pch.h"
#include "Input.h"

HRESULT Input::Init()
{
	ZeroMemory(key_state_, sizeof(DWORD) * 256);
	::GetCursorPos(&position_);
	::ScreenToClient(g_handle, &position_);

	return TRUE;
}

HRESULT Input::Frame()
{
	::GetCursorPos(&position_);				// ȭ�� ��ǥ
	::ScreenToClient(g_handle, &position_);	// Ŭ���̾�Ʈ ȭ��

	for (size_t i = 0; i < 256; i++)
	{
		SHORT key = ::GetAsyncKeyState(static_cast<int>(i));  // �񵿱� Ű ���� 
		if (key & 0x8000) // 1000 0000 0000 0000
		{
			if (key_state_[i] == KEY_STATE::NONE || key_state_[i] == KEY_STATE::UP)
			{
				key_state_[i] = KEY_STATE::DOWN;
			}
			else
			{
				key_state_[i] = KEY_STATE::HOLD;
			}
		}
		else
		{
			if (key_state_[i] == KEY_STATE::DOWN || key_state_[i] == KEY_STATE::HOLD)
			{
				key_state_[i] = KEY_STATE::UP;
			}
			else
			{
				key_state_[i] = KEY_STATE::NONE;
			}
		}
	}

	return TRUE;
}

HRESULT Input::Render()
{
	return TRUE;
}

HRESULT Input::Release()
{
	return TRUE;
}

DWORD Input::GetKey(DWORD key)
{
	return key_state_[key];
}

POINT Input::GetPosition()
{
	return position_;
}
