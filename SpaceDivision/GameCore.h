#pragma once

#include "Octree.h"
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
    Player _player;
    Enemy _enemy;

    std::map<int, Object*> _npcList;
    std::map<int, Object*> _objectList;
    std::vector<Object*>   _drawList;

    static GameCore* Instance();

    bool Init();                                    // 초기화
    bool Frame(float fDeltaTime, float fGameTime);  // 실시간 계산
    bool Render();                                  // 렌더
    bool Release();                                 // 해제
    bool Run();                                     // 실행
};

