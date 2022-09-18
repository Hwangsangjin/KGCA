#include "pch.h"
#include "Input.h"

HRESULT Input::Init()
{
	ZeroMemory(_keyState, sizeof(DWORD) * 256);

	return TRUE;
}

HRESULT Input::Frame()
{
	::GetCursorPos(&_position);			// 화면 좌표
	::ScreenToClient(hWnd, &_position);	// 클라이언트 화면

    for (size_t i = 0; i < 256; i++)
    {
        SHORT key = ::GetAsyncKeyState(i);  // 비동기 키 상태 
        if (key & 0x8000) // 1000 0000 0000 0000
        {
			if (_keyState[i] == KEY_STATE::NONE || _keyState[i] == KEY_STATE::UP)
			{
				_keyState[i] = KEY_STATE::DOWN;
			}
			else
			{
				_keyState[i] = KEY_STATE::HOLD;
			}
        }
		else
		{
			if (_keyState[i] == KEY_STATE::DOWN || _keyState[i] == KEY_STATE::HOLD)
			{
				_keyState[i] = KEY_STATE::UP;
			}
			else
			{
				_keyState[i] = KEY_STATE::NONE;
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
	return _keyState[key];
}

POINT Input::GetPos()
{
	return _position;
}
