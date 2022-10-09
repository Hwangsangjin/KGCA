#pragma once

#include "SDL/SDL.h"
#include <unordered_map>
#include <string>
#include <vector>

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);

private:
	// 게임 루프를 위한 헬퍼 함수
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	// 로드된 텍스처 맵
	std::unordered_map<std::string, SDL_Texture*> _textures;

	// 게임의 모든 액터
	std::vector<class Actor*> _actors;
	// 보류중인 액터
	std::vector<class Actor*> _pendingActors;

	// 그려진 모든 스프라이트 컴포넌트
	std::vector<class SpriteComponent*> _sprites;

	// SDL이 생성한 윈도우
	SDL_Window* _window;
	// 2D 렌더러
	SDL_Renderer* _renderer;
	// 게임 시작 이후 틱의 수
	Uint32 _ticksCount;
	// 게임이 계속 실행돼야 하는지를 판단
	bool _isRunning;
	// 지금 액터를 업데이트 중인지 추적
	bool _updatingActors;

	// 게임 특정
	class SpaceShip* _spaceShip;	// 플레이어의 우주선
};

