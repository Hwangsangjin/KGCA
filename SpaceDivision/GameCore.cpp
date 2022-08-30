#include "pch.h"
#include "GameCore.h"

GameCore* GameCore::_instance = nullptr;
GameCore* GameCore::Instance()
{
	if (_instance == nullptr)
	{
		_instance = new GameCore;
	}

	return _instance;
}

bool GameCore::Init()
{
	_player.Init();
	_player.SetPosition(Vector3(50, 50, 50), Vector3(50, 50, 50));
	_tree.Create(Vector3(0, 0, 0), Vector3(100, 100, 0));

	for (int i = 0; i < 10; i++)
	{
		std::string name = std::to_string(i);
		name += " Wall ";

		Object* pObject = new Wall(name);

		_objectList.insert(std::make_pair(i, pObject));
		_tree.AddStaticObject(pObject);
	}

	for (int i = 0; i < 10; i++)
	{
		std::string name = std::to_string(i);
		name += " Enemy ";

		Object* pObject = new Enemy(name);
   
		pObject->_name = name;
		_npcList.insert(std::make_pair(i, pObject));
		_objectList.insert(std::make_pair(10 + i, pObject));
		_tree.AddDynamicObject(pObject);
	}
	return true;
}

bool GameCore::Frame(float elapsedTime, float gameTime)
{
	_tree.DynamicObjectReset();

	for (auto object : _npcList)
	{
		Object* pObject = object.second;
		pObject->Frame(elapsedTime, gameTime);
		_tree.AddDynamicObject(pObject);
	}

	_player.Frame(elapsedTime, gameTime);
	_drawList = _tree.CollisionQuery(&_player);

	return false;
}

bool GameCore::Render()
{
	std::cout << "Player " << _player._box.vMin.x << ", " << _player._box.vMin.y << ", " << _player._box.vMin.z << std::endl;

	if (!_drawList.empty())
	{
		for (int i = 0; i < _drawList.size(); i++)
		{
			std::cout << _drawList[i]->_name << " " << _drawList[i]->_box.vMin.x << ", " << _drawList[i]->_box.vMin.y << ", " << _drawList[i]->_box.vMin.z << std::endl;
		}
	}

	return false;
}

bool GameCore::Release()
{
	for (auto object : _objectList)
	{
		delete object.second;
	}
	_objectList.clear();
	_npcList.clear();

	//if (_instance == nullptr)
	//{
	//	return false;
	//}

	//delete _instance;
	//_instance = nullptr;

	return true;
}

bool GameCore::Run()
{
	Init();
	float  gameTimer = 0.0f;
	float  elapsedTime = 10;
	while (gameTimer < 10.0f)
	{
		Frame(elapsedTime / 1000.0f, gameTimer);
		Render();
		Sleep(elapsedTime);
		system("cls");
		gameTimer += elapsedTime / 1000.0f;
	}
	Release();
	return true;
}
