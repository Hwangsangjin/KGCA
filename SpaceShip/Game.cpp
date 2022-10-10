#include "Game.h"
#include "SDL/SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "SpaceShip.h"
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"

Game::Game()
    : _window(nullptr)
    , _renderer(nullptr)
    , _isRunning(true)
    , _updatingActors(false)
{
}

bool Game::Initialize()
{
    // SDL �ʱ�ȭ
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        // SDL_Log�� C�� Printf�� ���� ���� ���
        // SDL_GetError()�� C ��Ÿ���� ���ڿ��� ���� �޽����� ��ȯ
        SDL_Log("Unable to initalize SDL: %s", SDL_GetError());
        return false;
    }

    // SDL ������ ����
    _window = SDL_CreateWindow(
        "Game",                     // ������ ����
        100,                        // �������� ���� ��� x ��ǥ
        100,                        // �������� ���� ��� y ��ǥ
        1024,                       // ������ �ʺ�
        768,                        // ������ ����
        0                           // �÷��� (0�� ��� �÷��׵� �������� ������ �ǹ�)
    );
    if (!_window)
    {
        SDL_Log("Failed to create window : %s", SDL_GetError());
        return false;
    }

    // SDL ������ ����
    _renderer = SDL_CreateRenderer(
        _window,                    // �������� ���� ������ ������
        -1,                         // ����� �׷���ī�� ����. -1�� ��� SDL�� �˾Ƽ� ����
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC    // �÷��� ��.����ȭ ������ ��� ���ο� ���� ����ȭ�� Ȱ��ȭ ���� ����
    );
    if (!_renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    // �̹��� �ʱ�ȭ
    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }

    LoadData();

    _ticksCount = SDL_GetTicks();

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

    // ���ּ��� �Է� ���μ���
    _spaceShip->ProcessKeyboard(state);
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

    // ���� �������� ���� ���� �ð��� ����.
    _ticksCount = SDL_GetTicks();

    // ��� ���͸� ������Ʈ
    _updatingActors = true;
    for (auto actor : _actors)
    {
        actor->Update(deltaTime);
    }
    _updatingActors = false;

    // ��� ���� ���͸� Ȱ�� ���ͷ� �̵�
    for (auto pending : _pendingActors)
    {
        _actors.emplace_back(pending);
    }
    _pendingActors.clear();

    // ���� ���͸� �ӽ� ���Ϳ� �߰�
    std::vector<Actor*> deadActors;
    for (auto actor : _actors)
    {
        if (actor->GetState() == Actor::Dead)
        {
            deadActors.emplace_back(actor);
        }
    }

    // ���� ���� ����(Ȱ�� ���Ϳ��� �߷��� ���͵�)
    for (auto actor : deadActors)
    {
        delete actor;
    }
};

void Game::GenerateOutput()
{
    // �������� ����� ���������� ����
    SDL_SetRenderDrawColor(
        _renderer,
        0,      // R
        0,      // G
        0,      // B
        255     // A
    );

    // �ĸ� ���� �����
    SDL_RenderClear(_renderer);

    // ��� ��������Ʈ ������Ʈ �׸���
    for (auto sprite : _sprites)
    {
        sprite->Draw(_renderer);
    }
    
    // ���� ���ۿ� �ĸ� ���� ��ȯ
    SDL_RenderPresent(_renderer);
}

void Game::LoadData()
{
    // �÷��̾��� ���ּ� ����
    _spaceShip = new SpaceShip(this);
    _spaceShip->SetPosition(Vector2(100.0f, 384.0f));
    _spaceShip->SetScale(1.5f);

    // ��濡 ����� ���� �����(���� Ŭ������ �ʿ� ����)
    Actor* temp = new Actor(this);
    temp->SetPosition(Vector2(512.0f, 384.0f));

    // �� ��� �����
    BGSpriteComponent* bg = new BGSpriteComponent(temp);
    bg->SetScreenSize(Vector2(1024.0f, 768.0f));
    std::vector<SDL_Texture*> bgtexs = {
        GetTexture("../../../Assets/SpaceShip/Farback01.png"),
        GetTexture("../../../Assets/SpaceShip/Farback02.png")
    };
    bg->SetBGTextures(bgtexs);
    bg->SetScrollSpeed(-100.0f);

    // ����� ��� �����
    bg = new BGSpriteComponent(temp, 50);
    bg->SetScreenSize(Vector2(1024.0f, 768.0f));
    bgtexs = {
        GetTexture("../../../Assets/SpaceShip/Stars.png"),
        GetTexture("../../../Assets/SpaceShip/Stars.png")
    };
    bg->SetBGTextures(bgtexs);
    bg->SetScrollSpeed(-200.0f);
}

void Game::UnloadData()
{
    // ���� ����
    // ~Actor �Լ��� RemoveActor�� ȣ���ϹǷ� �ٸ� ��Ÿ���� ������ ���
    while (!_actors.empty())
    {
        delete _actors.back();
    }

    // �ؽ�ó ����
    for (auto texture : _textures)
    {
        SDL_DestroyTexture(texture.second);
    }
    _textures.clear();
}

void Game::Shutdown()
{
    UnloadData();
    IMG_Quit();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
    // ���͸� ���� ���̶�� ��� ���Ϳ� ���͸� �߰�
    if (_updatingActors)
    {
        _pendingActors.emplace_back(actor);
    }
    else
    {
        _actors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor* actor)
{
    // ������� ������ ���
    auto iter = std::find(_pendingActors.begin(), _pendingActors.end(), actor);
    if (iter != _pendingActors.end())
    {
        // ������ ������ �����ϰ� ����(���纻 �����)
        std::iter_swap(iter, _pendingActors.end() - 1);
        _pendingActors.pop_back();
    }

    // ���� ������ ���
    iter = std::find(_actors.begin(), _actors.end(), actor);
    if (iter != _actors.end())
    {
        // ������ ������ �����ϰ� ����(���纻 �����)
        std::iter_swap(iter, _actors.end() - 1);
        _actors.pop_back();
    }
}

void Game::AddSprite(SpriteComponent* sprite)
{
    // ���ĵ� ���Ϳ��� �����ؾ� �� ��ġ�� ã�´�.
    // (�ڽź��� �׸��� �������� ū ���� ���)
    int drawOrder = sprite->GetDrawOrder();
    auto iter = _sprites.begin();
    for (; iter != _sprites.end(); iter++)
    {
        if (drawOrder < (*iter)->GetDrawOrder())
        {
            break;
        }
    }

    // �ݺ��� ��ġ �տ� ��Ҹ� �����Ѵ�.
    _sprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
    // �׸��� ������ ���ĵǾ� �ֱ� ������
    // swap(), pop()�� ���ؼ� ���� �� �� ����.
    auto iter = std::find(_sprites.begin(), _sprites.end(), sprite);
    _sprites.erase(iter);
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
    // ��ȯ�� texture�� �ּҰ��� ���� ����
    SDL_Texture* texture = nullptr;

    // unordered_map �����̳ʿ� ����Ǿ� �ִ� �ؽ�ó�� ���� �̸����� �˻�
    auto iter = _textures.find(fileName);
    // ���� �̸��� �ش��ϴ� �ؽ�ó�� �����Ѵٸ�
    if (iter != _textures.end())
    {
        texture = iter->second;
    }
    else
    {
        // ���Ϸκ��� �ε�
        SDL_Surface* surface = IMG_Load(fileName.c_str());
        if (!surface)
        {
            SDL_Log("Failed to load texture file %s", fileName.c_str());
            return nullptr;
        }

        // �ؽ�ó ����
        texture = SDL_CreateTextureFromSurface(_renderer, surface);
        SDL_FreeSurface(surface);
        if (!texture)
        {
            SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
            return nullptr;
        }

        _textures.emplace(fileName.c_str(), texture);
    }

    return texture;
}
