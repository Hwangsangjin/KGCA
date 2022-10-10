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
    // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        // SDL_Log는 C의 Printf와 같은 문법 사용
        // SDL_GetError()는 C 스타일의 문자열로 에러 메시지를 반환
        SDL_Log("Unable to initalize SDL: %s", SDL_GetError());
        return false;
    }

    // SDL 윈도우 생성
    _window = SDL_CreateWindow(
        "Game",                     // 윈도우 제목
        100,                        // 윈도우의 왼쪽 상단 x 좌표
        100,                        // 윈도우의 왼쪽 상단 y 좌표
        1024,                       // 윈도우 너비
        768,                        // 윈도우 높이
        0                           // 플래그 (0은 어떠한 플래그도 설정되지 않음을 의미)
    );
    if (!_window)
    {
        SDL_Log("Failed to create window : %s", SDL_GetError());
        return false;
    }

    // SDL 렌더러 생성
    _renderer = SDL_CreateRenderer(
        _window,                    // 렌더링을 위해 생성한 윈도우
        -1,                         // 사용할 그래픽카드 선택. -1인 경우 SDL이 알아서 선택
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC    // 플래그 값.가속화 렌더러 사용 여부와 수직 동기화의 활성화 여부 선택
    );
    if (!_renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    // 이미지 초기화
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

    // 우주선의 입력 프로세스
    _spaceShip->ProcessKeyboard(state);
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

    // 다음 프레임을 위해 현재 시간값 저장.
    _ticksCount = SDL_GetTicks();

    // 모든 액터를 업데이트
    _updatingActors = true;
    for (auto actor : _actors)
    {
        actor->Update(deltaTime);
    }
    _updatingActors = false;

    // 대기 중인 액터를 활성 벡터로 이동
    for (auto pending : _pendingActors)
    {
        _actors.emplace_back(pending);
    }
    _pendingActors.clear();

    // 죽은 액터를 임시 벡터에 추가
    std::vector<Actor*> deadActors;
    for (auto actor : _actors)
    {
        if (actor->GetState() == Actor::Dead)
        {
            deadActors.emplace_back(actor);
        }
    }

    // 죽은 액터 제거(활성 벡터에서 추려낸 액터들)
    for (auto actor : deadActors)
    {
        delete actor;
    }
};

void Game::GenerateOutput()
{
    // 렌더러의 배경을 검은색으로 설정
    SDL_SetRenderDrawColor(
        _renderer,
        0,      // R
        0,      // G
        0,      // B
        255     // A
    );

    // 후면 버퍼 지우기
    SDL_RenderClear(_renderer);

    // 모든 스프라이트 컴포넌트 그리기
    for (auto sprite : _sprites)
    {
        sprite->Draw(_renderer);
    }
    
    // 전면 버퍼와 후면 버퍼 교환
    SDL_RenderPresent(_renderer);
}

void Game::LoadData()
{
    // 플레이어의 우주선 생성
    _spaceShip = new SpaceShip(this);
    _spaceShip->SetPosition(Vector2(100.0f, 384.0f));
    _spaceShip->SetScale(1.5f);

    // 배경에 사용할 액터 만들기(하위 클래스가 필요 없음)
    Actor* temp = new Actor(this);
    temp->SetPosition(Vector2(512.0f, 384.0f));

    // 먼 배경 만들기
    BGSpriteComponent* bg = new BGSpriteComponent(temp);
    bg->SetScreenSize(Vector2(1024.0f, 768.0f));
    std::vector<SDL_Texture*> bgtexs = {
        GetTexture("../../../Assets/SpaceShip/Farback01.png"),
        GetTexture("../../../Assets/SpaceShip/Farback02.png")
    };
    bg->SetBGTextures(bgtexs);
    bg->SetScrollSpeed(-100.0f);

    // 가까운 배경 만들기
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
    // 액터 삭제
    // ~Actor 함수가 RemoveActor를 호출하므로 다른 스타일의 루프를 사용
    while (!_actors.empty())
    {
        delete _actors.back();
    }

    // 텍스처 삭제
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
    // 액터를 갱신 중이라면 대기 벡터에 액터를 추가
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
    // 대기중인 액터인 경우
    auto iter = std::find(_pendingActors.begin(), _pendingActors.end(), actor);
    if (iter != _pendingActors.end())
    {
        // 벡터의 끝으로 변경하고 삭제(복사본 지우기)
        std::iter_swap(iter, _pendingActors.end() - 1);
        _pendingActors.pop_back();
    }

    // 게임 액터인 경우
    iter = std::find(_actors.begin(), _actors.end(), actor);
    if (iter != _actors.end())
    {
        // 벡터의 끝으로 변경하고 삭제(복사본 지우기)
        std::iter_swap(iter, _actors.end() - 1);
        _actors.pop_back();
    }
}

void Game::AddSprite(SpriteComponent* sprite)
{
    // 정렬된 벡터에서 삽입해야 할 위치를 찾는다.
    // (자신보다 그리기 순서값이 큰 최초 요소)
    int drawOrder = sprite->GetDrawOrder();
    auto iter = _sprites.begin();
    for (; iter != _sprites.end(); iter++)
    {
        if (drawOrder < (*iter)->GetDrawOrder())
        {
            break;
        }
    }

    // 반복자 위치 앞에 요소를 삽입한다.
    _sprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
    // 그리기 순서로 정렬되어 있기 때문에
    // swap(), pop()을 통해서 삭제 할 수 없다.
    auto iter = std::find(_sprites.begin(), _sprites.end(), sprite);
    _sprites.erase(iter);
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
    // 반환할 texture의 주소값을 담을 변수
    SDL_Texture* texture = nullptr;

    // unordered_map 컨테이너에 저장되어 있는 텍스처를 파일 이름으로 검색
    auto iter = _textures.find(fileName);
    // 파일 이름에 해당하는 텍스처가 존재한다면
    if (iter != _textures.end())
    {
        texture = iter->second;
    }
    else
    {
        // 파일로부터 로딩
        SDL_Surface* surface = IMG_Load(fileName.c_str());
        if (!surface)
        {
            SDL_Log("Failed to load texture file %s", fileName.c_str());
            return nullptr;
        }

        // 텍스처 생성
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
