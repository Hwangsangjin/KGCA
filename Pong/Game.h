#pragma once

#include "SDL/SDL.h"

// x, y ��ǥ�� �����ϴ� ����ü
struct Vector2
{
	float x;
	float y;
};

// ���� Ŭ����
class Game
{
private:
	// SDL�� ������ ������
	SDL_Window* _pWindow;
	// 2D ������
	SDL_Renderer* _pRenderer;
	// ���� ���� ���� ƽ�� ��
	Uint32 _ticksCount;
	// ������ ��� ����ž� �ϴ����� �Ǵ�
	bool _isRunning;

	// �е��� ����
	int _paddleDir;
	int _paddleDir2;
	// �е��� ��ġ
	Vector2 _paddlePos;
	Vector2 _paddlePos2;
	// ���� ��ġ
	Vector2 _ballPos;
	// ���� �ӵ�
	Vector2 _ballVel;

	// ���� ������ ���� ���� �Լ�
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

public:
	// ������
	Game();
	// ���� �ʱ�ȭ
	bool Initialize();
	// ������ ������ ������ ���� ������ ����
	void RunLoop();
	// ���� ����
	void Shutdown();
};

