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
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>

// lib
#pragma comment (lib, "d3d11")
#pragma comment (lib, "dxgi")
#pragma comment (lib, "d2d1")
#pragma comment (lib, "dwrite")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "DirectXTK.lib")

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
	Vector3 position;
	Vector4 color;
	Vector2 uv;
};

struct Rect
{
    float  x1;
    float  y1;
    float  w;
    float  h;
    float  x2;//x+w
    float  y2;//y+h
    float  cx;
    float  cy;
    bool   operator == (Rect& dest)
    {
        if (fabs(x1 - dest.x1) < FLT_EPSILON)
        {
            if (fabs(y1 - dest.y1) < FLT_EPSILON)
            {
                if (fabs(w - dest.w) < FLT_EPSILON)
                {
                    if (fabs(h - dest.h) < FLT_EPSILON)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    Rect() = default;
    Rect(float x, float y, float z, float w)
    {
        Set(x, y, z, w);
    }

    void Set(float x, float y, float z, float w)
    {
        this->x1 = x;
        this->y1 = y;
        this->w = z;
        this->h = w;
        x2 = x + w;
        y2 = y + h;
        cx = (x + x2) / 2.0f;
        cy = (y + y2) / 2.0f;
    }
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
#define TEXTURE				GET_SINGLE(TextureManager)
