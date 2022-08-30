#pragma once

#include "Octree.h"
#include "Wall.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include <map>
#include <windows.h>

class GameCore
{
private:
    static GameCore* _instance;

    GameCore() {}
    ~GameCore() {}

public:
    Octree _tree;
    Wall _wall;
    Player _player;
    Enemy _enemy;

    std::map<int, Object*> _npcList;
    std::map<int, Object*> _objectList;
    std::vector<Object*>   _drawList;

    static GameCore* Instance();

    bool Init();                                    // �ʱ�ȭ
    bool Frame(float elapsedTime, float gameTime);  // �ǽð� ���
    bool Render();                                  // ����
    bool Release();                                 // ����
    bool Run();                                     // ����
};

