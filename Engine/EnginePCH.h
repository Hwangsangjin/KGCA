#pragma once

// header
#include <Windows.h>
#include <cassert>
#include <string>
#include <d3d11.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
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
#include <wrl.h>
#include "DxMath.h"

// lib
#pragma comment (lib, "d3d11")
#pragma comment (lib, "dxgi")
#pragma comment (lib, "d2d1")
#pragma comment (lib, "dwrite")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "DirectXTK")
#pragma comment(lib, "fmod_vc")
#pragma comment(lib, "libfbxsdk-md")
#pragma comment(lib, "libxml2-md")
#pragma comment(lib, "zlib-md")

// extern
extern HWND g_handle;
extern RECT g_client_rect;

// using
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

// typedef
typedef std::basic_string<TCHAR> T_STR;
typedef std::basic_string<char> C_STR;
typedef std::basic_string<wchar_t> W_STR;
typedef std::vector<std::basic_string<TCHAR>> TCHAR_STRING_VECTOR;
typedef std::vector<DWORD> DWORD_VECTOR;

// string convert
static std::wstring to_mw(const std::string& src)
{
	USES_CONVERSION;
	return std::wstring(A2W(src.c_str()));
};

static std::string to_wm(const std::wstring& src)
{
	USES_CONVERSION;
	return std::string(W2A(src.c_str()));
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
#define GRAVITY				9.8f
#define FRICTION			0.9f
#define COEFFICIENT			0.9f

#define PI					3.141592654f
#define PI_DIVISION_2		1.570796327f
#define	PI_DIVISION_4		0.785398163f

#define DEGREE_TO_RADIAN(x)	(x * (PI / 180.0f))
#define RADIAN_TO_DEGREE(x)	(x * (180.0f / PI))
