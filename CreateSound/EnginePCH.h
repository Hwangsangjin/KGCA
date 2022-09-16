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
#include <list>
#include <map>
#include <d3dcompiler.h>
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>
#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <atlconv.h>
#include <codecvt>
#include <tchar.h>
#include <io.h>

// lib
#pragma comment (lib, "d3d11")
#pragma comment (lib, "dxgi")
#pragma comment (lib, "d2d1")
#pragma comment (lib, "dwrite")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "DirectXTK.lib")
#pragma comment(lib, "fmod_vc")

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

// typedef
typedef std::basic_string<TCHAR> T_STR;
typedef std::basic_string<char> C_STR;
typedef std::basic_string<wchar_t> W_STR;
typedef std::vector<std::basic_string<TCHAR>> TCHAR_STRING_VECTOR;
typedef std::vector<DWORD> DWORD_VECTOR;

// struct
struct Vertex
{
	Vector3 position;
	Vector4 color;
	Vector2 uv;
};

struct Rect
{
	float x;
	float y;
	float w;
	float h;
	Vector2 center;

	bool operator == (Rect& dest)
	{
		if (fabs(x - dest.x) < FLT_EPSILON)
		{
			if (fabs(y - dest.y) < FLT_EPSILON)
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

	Rect() {}
	Rect(float x, float y, float w, float h)
	{
		Set(x, y, w, h);
	}

	void  Set(float x, float y, float w, float h)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->center.x = w / 2.0f;
		this->center.y = h / 2.0f;
	}
};

// String Convert
static std::wstring to_mw(const std::string& _src)
{
	USES_CONVERSION;
	return std::wstring(A2W(_src.c_str()));
};

static std::string to_wm(const std::wstring& _src)
{
	USES_CONVERSION;
	return std::string(W2A(_src.c_str()));
};

static std::wstring mtw(std::string str)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
	return conv.from_bytes(str);
}

static std::string wtm(std::wstring str)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
	return conv.to_bytes(str);
}

static char* GetWtM(WCHAR* data)
{
	char retData[4096] = { 0 };
	// 변형되는 문자열의 크기가 반환된다.
	int iLength = WideCharToMultiByte(CP_ACP, 0,
		data, -1, 0, 0, NULL, NULL);
	int iRet = WideCharToMultiByte(CP_ACP, 0,
		data, -1,  //  소스
		retData, iLength, // 대상
		NULL, NULL);
	return retData;
}

static bool GetWtM(WCHAR* src, char* pDest)
{
	// 변형되는 문자열의 크기가 반환된다.
	int iLength = WideCharToMultiByte(CP_ACP, 0,
		src, -1, 0, 0, NULL, NULL);
	int iRet = WideCharToMultiByte(CP_ACP, 0,
		src, -1,  //  소스
		pDest, iLength, // 대상
		NULL, NULL);
	if (iRet == 0) return false;
	return true;
}

static WCHAR* GetMtW(char* data)
{
	WCHAR retData[4096] = { 0 };
	// 변형되는 문자열의 크기가 반환된다.
	int iLength = MultiByteToWideChar(CP_ACP, 0, data, -1, 0, 0);
	int iRet = MultiByteToWideChar(CP_ACP, 0,
		data, -1,  //  소스
		retData, iLength); // 대상
	return retData;
}

static bool GetMtW(char* pSrc, WCHAR* pDest)
{
	// 변형되는 문자열의 크기가 반환된다.
	int iLength = MultiByteToWideChar(CP_ACP, 0,
		pSrc, -1, 0, 0);
	int iRet = MultiByteToWideChar(CP_ACP, 0,
		pSrc, -1,  //  소스
		pDest, iLength); // 대상		
	if (iRet == 0) return false;
	return true;
}

// define
#define RESOLUTION_X 800
#define RESOLUTION_Y 600
#define HALF         2

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

#define SAFE_DELETE(p)		{ if (p) { delete p; p = nullptr; } }
#define SAFE_RELEASE(p)		{ if (p) { p->Release(); p = nullptr; } }
#define SAFE_CLEARSTATE(p)	{ if (p) { p->ClearState(); } }

#define DELTA_TIME			GET_SINGLE(Timer)->GetDeltaTime()
#define TIMER				GET_SINGLE(Timer)
#define INPUT				GET_SINGLE(Input)

#define SOUND				GET_SINGLE(SoundManager)
#define SHADER				GET_SINGLE(ShaderManager)
#define TEXTURE				GET_SINGLE(TextureManager)

#define RAND(min, max)      (min+((float)max-(float)min)*rand()/(float)RAND_MAX)
