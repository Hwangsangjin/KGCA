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
	_tree.Create(Vector3(0, 0, 0), Vector3(100, 100, 0));
	_player.SetPosition(Vector3(50, 50, 50), Vector3(50, 50, 50));

	for (int i = 0; i < 10; i++)
	{
		std::string name = std::to_string(i);
		name += " Static";

		Object* pObject = new Object(name);

		_objectList.insert(std::make_pair(i, pObject));
		_tree.AddStaticObject(pObject);
	}

	for (int i = 0; i < 10; i++)
	{
		std::string name = std::to_string(i);
		name += " Dynamic";

		Object* pObject = new Enemy;
   
		pObject->_name = name;
		_npcList.insert(std::make_pair(i, pObject));
		_objectList.insert(std::make_pair(10 + i, pObject));
		_tree.AddDynamicObject(pObject);
	}
	return true;
}

bool GameCore::Frame(float fDeltaTime, float fGameTime)
{
	_tree.DynamicObjectReset();
	for (auto object : _npcList)
	{
		Object* pObject = object.second;
		pObject->Frame(fDeltaTime, fGameTime);
		_tree.AddDynamicObject(pObject);
	}

	_player.Frame(fDeltaTime, fGameTime);
	_drawList = _tree.CollisionQuery(&_player);

	return false;
}

bool GameCore::Render()
{
	std::cout << "Player:"
		<< _player._box._vMin._x << ", " << _player._box._vMin._y << ", "
		<< _player._box._vMin._z << std::endl;
	if (!_drawList.empty())
	{
		for (int i = 0; i < _drawList.size(); i++)
		{
			std::cout << _drawList[i]->_name << ", "
				<< _drawList[i]->_box._vMin._x << ", "
				<< _drawList[i]->_box._vMin._y << ", "
				<< _drawList[i]->_box._vMin._z << std::endl;
		}
	}

	return false;
}

bool GameCore::Release()
{
	if (_instance == nullptr)
	{
		return false;
	}

	delete _instance;
	_instance = nullptr;

	return true;
}

bool GameCore::Run()
{
	Init();
	float  fGameTimer = 0.0f;
	float  fDelay = 10;
	while (fGameTimer < 10.0f)
	{
		Frame(fDelay / 1000.0f, fGameTimer);
		Render();
		Sleep(fDelay);
		system("cls");
		fGameTimer += fDelay / 1000.0f;
	}
	Release();
	return true;
}
