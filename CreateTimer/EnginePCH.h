#pragma once

#define CORE
#define GAME_START  int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
#define GAME_WINDOW(s,x,y)  Sample sample; sample.SetWindow(hInstance,L#s,x,y); sample.Run(); return 0;
#define GAME_END    }
#define GAME_RUN(s,x,y) GAME_START GAME_WINDOW(s,x,y) GAME_END

#pragma comment (lib, "d3d11")
#pragma comment (lib, "dxgi")

#include <assert.h>
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <string>
#include <d3d11.h>