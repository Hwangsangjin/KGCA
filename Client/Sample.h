#pragma once

#include "Core.h"
#include "Object2D.h"
#include "Player2D.h"

class Sample : public Core
{
private:
	POINT _pos{ 0, 0 };
	std::vector<Object*> _objects;

	Object2D* _sky = nullptr;
	Object2D* _mountain = nullptr;
	Object2D* _cloud = nullptr;
	Object2D* _ground = nullptr;
	Object2D* _net = nullptr;
	Player2D* _player = nullptr;
	Object2D* _ball = nullptr;

public:
	Sample() = default;
	virtual ~Sample() = default;

	// 초기화
	virtual HRESULT Init() final;
	// 프레임 계산
	virtual HRESULT Frame() final;
	// 렌더
	virtual HRESULT Render() final;
	// 메모리 해제
	virtual HRESULT Release() final;

	// 게임 오브젝트 추가
	void AddObject(Object* object);
};

