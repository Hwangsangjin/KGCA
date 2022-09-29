#pragma once

#include "SDL/SDL.h"

// x, y 좌표를 저장하는 구조체
struct Vector2
{
	float x;
	float y;
};

// 게임 클래스
class Game
{
private:
	// SDL이 생성한 윈도우
	SDL_Window* _pWindow;
	// 2D 렌더러
	SDL_Renderer* _pRenderer;
	// 게임 시작 이후 틱의 수
	Uint32 _ticksCount;
	// 게임이 계속 실행돼야 하는지를 판단
	bool _isRunning;

	// 패들의 방향
	int _paddleDir;
	int _paddleDir2;
	// 패들의 위치
	Vector2 _paddlePos;
	Vector2 _paddlePos2;
	// 공의 위치
	Vector2 _ballPos;
	// 공의 속도
	Vector2 _ballVel;

	// 게임 루프를 위한 헬퍼 함수
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

public:
	// 생성자
	Game();
	// 게임 초기화
	bool Initialize();
	// 게임이 끝나기 전까지 게임 루프를 실행
	void RunLoop();
	// 게임 종료
	void Shutdown();
};

