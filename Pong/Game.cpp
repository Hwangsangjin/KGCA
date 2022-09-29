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
    // ť�� ������ �̺�Ʈ�� ���� �ִ� ����
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        // SDL_QUIT �̺�Ʈ�� �߻��ϸ� ���� ����
        case SDL_QUIT:
            _isRunning = false;
            break;
        }
    }

    // Ű������ ���� ���
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    // �̽������� Ű�� �����ٸ� ���� ����
    if (state[SDL_SCANCODE_ESCAPE])
    {
        _isRunning = false;
    }

    // W, S Ű�� �������� �е� ���� ������Ʈ
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
    // ������ ������ ���ķ� 16ms�� ����� ������ ���
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), _ticksCount + 16))
        ;

    // ��Ÿ �ð��� ������ ������ ƽ���� ���� ������ ƽ���� ��
    // (�� ������ ��ȯ)
    float deltaTime = (SDL_GetTicks() - _ticksCount) / 1000.0f;

    // �ִ� ��Ÿ �ð������� ����
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    // ���� �������� ���� ƽ�� ������Ʈ
    _ticksCount = SDL_GetTicks();

    // ���⿡ ���� �е� ��ġ ������Ʈ
    if (_paddleDir != 0)
    {
        _paddlePos.y += _paddleDir * 300.0f * deltaTime;

        // �е��� ȭ�� ������ ��������� ��������!
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
    // �������� ����� �Ķ������� ����
    SDL_SetRenderDrawColor(
        _pRenderer,
        0,      // R
        51,     // G
        102,    // B
        255     // A
    );

    // �ĸ� ���� �����
    SDL_RenderClear(_pRenderer);

    // ������Ʈ�� �׸��� ���� ������� ����
    SDL_SetRenderDrawColor(_pRenderer, 255, 255, 255, 255);

    // ��� ��
    SDL_Rect wall
    {
        0,          // ���� ��� x
        0,          // ���� ��� y
        1024,       // �ʺ�
        thickness   // ����
    };
    SDL_RenderFillRect(_pRenderer, &wall);

    // �ϴ� ��
    wall.y = 600 - thickness;
    SDL_RenderFillRect(_pRenderer, &wall);

    // ������ ��
    wall.x = 800 - thickness;
    wall.y = 0;
    wall.w = thickness;
    wall.h = 800;
    SDL_RenderFillRect(_pRenderer, &wall);

    // �е�
    SDL_Rect paddle
    {
        static_cast<int>(_paddlePos.x),
        static_cast<int>(_paddlePos.y - paddleH / 2),
        thickness,
        static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(_pRenderer, &paddle);

    // ��
    SDL_Rect ball
    {
        static_cast<int>(_ballPos.x - thickness / 2),
        static_cast<int>(_ballPos.y - thickness / 2),
        thickness,
        thickness,
    };
    SDL_RenderFillRect(_pRenderer, &ball);

    // ���� ���ۿ� �ĸ� ���� ��ȯ
    SDL_RenderPresent(_pRenderer);
}

bool Game::Initialize()
{
    // SDL �ʱ�ȭ
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0)
    {
        SDL_Log("Unable to initalize SDL: %s", SDL_GetError());
        return false;
    }

    // SDL ������ ����
    _pWindow = SDL_CreateWindow(
        "Game",                     // ������ ����
        100,                        // �������� ���� ��� x ��ǥ
        100,                        // �������� ���� ��� y ��ǥ
        800,                        // ������ �ʺ�
        600,                        // ������ ����
        0                           // �÷���(0�� ��� �÷��׵� �������� ������ �ǹ�)
        );
    if (!_pWindow)
    {
        SDL_Log("Failed to create window : %s", SDL_GetError());
        return false;
    }

    // SDL ������ ����
    _pRenderer = SDL_CreateRenderer(
        _pWindow,                   // �������� ���� ������ ������
        -1,                         // �Ϲ������� -1
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!_pRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    // ������Ʈ ����
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
