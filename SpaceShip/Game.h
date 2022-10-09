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
	// ���� ������ ���� ���� �Լ�
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	// �ε�� �ؽ�ó ��
	std::unordered_map<std::string, SDL_Texture*> _textures;

	// ������ ��� ����
	std::vector<class Actor*> _actors;
	// �������� ����
	std::vector<class Actor*> _pendingActors;

	// �׷��� ��� ��������Ʈ ������Ʈ
	std::vector<class SpriteComponent*> _sprites;

	// SDL�� ������ ������
	SDL_Window* _window;
	// 2D ������
	SDL_Renderer* _renderer;
	// ���� ���� ���� ƽ�� ��
	Uint32 _ticksCount;
	// ������ ��� ����ž� �ϴ����� �Ǵ�
	bool _isRunning;
	// ���� ���͸� ������Ʈ ������ ����
	bool _updatingActors;

	// ���� Ư��
	class SpaceShip* _spaceShip;	// �÷��̾��� ���ּ�
};

