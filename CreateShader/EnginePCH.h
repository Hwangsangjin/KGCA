#pragma once

// header
#include <Windows.h>
#include <assert.h>
#include <string>
#include <d3d11.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <SimpleMath.h>
#include <vector>
#include <map>
#include <d3dcompiler.h>

// lib
#pragma comment (lib, "d3d11")
#pragma comment (lib, "dxgi")
#pragma comment (lib, "d2d1")
#pragma comment (lib, "dwrite")
#pragma comment(lib, "d3dcompiler.lib")

// extern
extern HWND hWnd;
extern RECT rtClient;

// using
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;
using Vector2 = DirectX::XMFLOAT2;
using Vector3 = DirectX::XMFLOAT3;
using Vector4 = DirectX::XMFLOAT4;

// struct
struct Vertex
{
	Vector3 pos;
	Vector4 color;
};

// define
#define CORE
#define GAME_START  int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
#define GAME_WINDOW(s,x,y)  Sample sample; sample.SetWindow(hInstance,L#s,x,y); sample.Run(); return 0;
#define GAME_END    }
#define GAME_RUN(s,x,y) GAME_START GAME_WINDOW(s,x,y) GAME_END

#define HR(todo)					\
	{                               \
		HRESULT hr = (todo);        \
		if(FAILED(hr))              \
		{                           \
			E_FAIL;					\
		}                           \
	}

#define DECLARE_SINGLE(type)		\
private:							\
	type() {}						\
	~type() { Release(); }		    \
                                    \
public:								\
	static type* GetInstance()		\
	{								\
		static type instance;		\
		return &instance;			\
	}								\

#define GET_SINGLE(type)	type::GetInstance()

#define SAFE_RELEASE(A)		{ if (A) { (A)->Release(); (A) = nullptr; } }
#define SAFE_CLEARSTATE(A)	{ if (A) { (A)->ClearState(); } }

#define DELTA_TIME			GET_SINGLE(Timer)->GetDeltaTime()
#define TIMER				GET_SINGLE(Timer)

#define INPUT				GET_SINGLE(Input)

#define SHADER				GET_SINGLE(ShaderManager)
