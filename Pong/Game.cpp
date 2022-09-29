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
    _paddleDir2 = 0;
    
    if (state[SDL_SCANCODE_W])
    {
        _paddleDir -= 1;
    }

    if (state[SDL_SCANCODE_S])
    {
        _paddleDir += 1;
    }

    if (state[SDL_SCANCODE_UP])
    {
        _paddleDir2 -= 1;
    }

    if (state[SDL_SCANCODE_DOWN])
    {
        _paddleDir2 += 1;
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

    // �е��� ���⿡ ���� ��ġ ������Ʈ
    if (_paddleDir != 0)
    {
        _paddlePos.y += _paddleDir * 300.0f * deltaTime;

        // �е��� ȭ�� ������ ��������� ��������!
        if (_paddlePos.y < (paddleH / 2.0f + thickness))
        {
            _paddlePos.y = paddleH / 2.0f + thickness;
        }
        else if (_paddlePos.y > (600.0f - paddleH / 2.0f - thickness))
        {
            _paddlePos.y = 600.0f - paddleH / 2.0f - thickness;
        }
    }

    if (_paddleDir2 != 0)
    {
        _paddlePos2.y += _paddleDir2 * 300.0f * deltaTime;

        // �е��� ȭ�� ������ ��������� ��������!
        if (_paddlePos2.y < (paddleH / 2.0f + thickness))
        {
            _paddlePos2.y = paddleH / 2.0f + thickness;
        }
        else if (_paddlePos2.y > (600.0f - paddleH / 2.0f - thickness))
        {
            _paddlePos2.y = 600.0f - paddleH / 2.0f - thickness;
        }
    }

    // ���� �ӵ��� ���� ��ġ ������Ʈ
    _ballPos.x += _ballVel.x * deltaTime;
    _ballPos.y += _ballVel.y * deltaTime;

    // ���� y ��ġ�� �е��� y ��ġ ������ �� ���밪
    float diff = _paddlePos.y - _ballPos.y;
    diff = (diff > 0.0f) ? diff : -diff;

    float diff2 = _paddlePos2.y - _ballPos.y;
    diff2 = (diff2 > 0.0f) ? diff2 : -diff2;

    // ���� �е�� �浹�ϴ� ���
    if (
        // y ���� ����� �۰�
        diff <= paddleH / 2.0f &&
        // ���� �ùٸ� x ��ġ�� �ְ�
        _ballPos.x < 25.0f && _ballPos.x >= 20.0f &&
        // ���� �������� �̵��ϰ� �ִٸ�
        _ballVel.x < 0.0f)
    {
        _ballVel.x *= -1.0f;
    }
    else if (
        // y ���� ����� �۰�
        diff2 <= paddleH / 2.0f &&
        // ���� �ùٸ� x ��ġ�� �ְ�
        _ballPos.x > 775.0f && _ballPos.x <= 780.0f &&
        // ���� �������� �̵��ϰ� �ִٸ�
        _ballVel.x > 0.0f)
    {
        _ballVel.x *= -1.0f;
    }
    // ���� ȭ�� ������ ������ ���(���� ����)
    else if (_ballPos.x <= 0.0f || _ballPos.x >= 800.0f)
    {
        _isRunning = false;
    }

    // ���� ��� ���� �浹�ϴ� ���
    if (_ballPos.y <= thickness && _ballVel.y < 0.0f)
    {
        _ballVel.y *= -1.0f;
    }
    // ���� �ϴ� ���� �浹�ϴ� ���
    else if (_ballPos.y >= (600 - thickness) && _ballVel.y > 0.0f)
    {
        _ballVel.y *= -1.0f;
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

    // �е�
    SDL_Rect paddle
    {
        static_cast<int>(_paddlePos.x),
        static_cast<int>(_paddlePos.y - paddleH / 2),
        thickness,
        static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(_pRenderer, &paddle);

    SDL_Rect paddle2
    {
        static_cast<int>(_paddlePos2.x),
        static_cast<int>(_paddlePos2.y - paddleH / 2),
        thickness,
        static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(_pRenderer, &paddle2);

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
    _paddlePos2.x = 775.0f;
    _paddlePos2.y = 600.0f / 2.0f;
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
