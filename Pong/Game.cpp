#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game()
    : _pWindow(nullptr)
    , _pRenderer(nullptr)
    , _ticksCount(0)
    , _isRunning(true)
    , _paddleDir(0)
{
}

void Game::ProcessInput()
{
    SDL_Event event;
    // 큐에 여전히 이벤트가 남아 있는 동안
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        // SDL_QUIT 이벤트가 발생하면 루프 종료
        case SDL_QUIT:
            _isRunning = false;
            break;
        }
    }

    // 키보드의 상태 얻기
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    // 이스케이프 키를 눌렀다면 루프 종료
    if (state[SDL_SCANCODE_ESCAPE])
    {
        _isRunning = false;
    }

    // W, S 키를 기준으로 패들 방향 업데이트
    _paddleDir = 0;
    
    if (state[SDL_SCANCODE_W])
    {
        _paddleDir -= 1;
    }

    if (state[SDL_SCANCODE_S])
    {
        _paddleDir += 1;
    }
}

void Game::UpdateGame()
{
    // 마지막 프레임 이후로 16ms가 경과할 때까지 대기
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), _ticksCount + 16))
        ;

    // 델타 시간은 마지막 프레임 틱값과 현재 프레임 틱값의 차
    // (초 단위로 변환)
    float deltaTime = (SDL_GetTicks() - _ticksCount) / 1000.0f;

    // 최대 델타 시간값으로 고정
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    // 다음 프레임을 위해 틱값 업데이트
    _ticksCount = SDL_GetTicks();

    // 방향에 따라 패들 위치 업데이트
    if (_paddleDir != 0)
    {
        _paddlePos.y += _paddleDir * 300.0f * deltaTime;

        // 패들이 화면 영역을 벗어나는지를 검증하자!
        if (_paddlePos.y < (paddleH / 2.0f + thickness))
        {
            _paddlePos.y = paddleH / 2.0f + thickness;
        }
        else if (_paddlePos.y > (768.0f - paddleH / 2.0f - thickness))
        {
            _paddlePos.y = 768.0f - paddleH / 2.0f - thickness;
        }
    }
}

void Game::GenerateOutput()
{
    // 렌더러의 배경을 파란색으로 설정
    SDL_SetRenderDrawColor(
        _pRenderer,
        0,      // R
        51,     // G
        102,    // B
        255     // A
    );

    // 후면 버퍼 지우기
    SDL_RenderClear(_pRenderer);

    // 오브젝트를 그리기 위해 흰색으로 설정
    SDL_SetRenderDrawColor(_pRenderer, 255, 255, 255, 255);

    // 상단 벽
    SDL_Rect wall
    {
        0,          // 왼쪽 상단 x
        0,          // 왼쪽 상단 y
        1024,       // 너비
        thickness   // 높이
    };
    SDL_RenderFillRect(_pRenderer, &wall);

    // 하단 벽
    wall.y = 600 - thickness;
    SDL_RenderFillRect(_pRenderer, &wall);

    // 오른쪽 벽
    wall.x = 800 - thickness;
    wall.y = 0;
    wall.w = thickness;
    wall.h = 800;
    SDL_RenderFillRect(_pRenderer, &wall);

    // 패들
    SDL_Rect paddle
    {
        static_cast<int>(_paddlePos.x),
        static_cast<int>(_paddlePos.y - paddleH / 2),
        thickness,
        static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(_pRenderer, &paddle);

    // 공
    SDL_Rect ball
    {
        static_cast<int>(_ballPos.x - thickness / 2),
        static_cast<int>(_ballPos.y - thickness / 2),
        thickness,
        thickness,
    };
    SDL_RenderFillRect(_pRenderer, &ball);

    // 전면 버퍼와 후면 버퍼 교환
    SDL_RenderPresent(_pRenderer);
}

bool Game::Initialize()
{
    // SDL 초기화
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0)
    {
        SDL_Log("Unable to initalize SDL: %s", SDL_GetError());
        return false;
    }

    // SDL 윈도우 생성
    _pWindow = SDL_CreateWindow(
        "Game",                     // 윈도우 제목
        100,                        // 윈도우의 왼쪽 상단 x 좌표
        100,                        // 윈도우의 왼쪽 상단 y 좌표
        800,                        // 윈도우 너비
        600,                        // 윈도우 높이
        0                           // 플래그(0은 어떠한 플래그도 설정되지 않음을 의미)
        );
    if (!_pWindow)
    {
        SDL_Log("Failed to create window : %s", SDL_GetError());
        return false;
    }

    // SDL 렌더러 생성
    _pRenderer = SDL_CreateRenderer(
        _pWindow,                   // 렌더링을 위해 생성한 윈도우
        -1,                         // 일반적으로 -1
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!_pRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    // 오브젝트 설정
    _paddlePos.x = 10.0f;
    _paddlePos.y = 600.0f / 2.0f;
    _ballPos.x = 800.0f / 2.0f;
    _ballPos.y = 600.0f / 2.0f;
    _ballVel.x = -200.0f;
    _ballVel.y = 235.0f;

    return true;
}

void Game::RunLoop()
{
    while (_isRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::Shutdown()
{
    SDL_DestroyRenderer(_pRenderer);
    SDL_DestroyWindow(_pWindow);
    SDL_Quit();
}
