#pragma once

#include "Core.h"

class Sample : public Core
{
private:
	POINT _pos{ 0, 0 };
	std::vector<Object*> _objects;

	Object2D* _map = nullptr;
	Object2D* _ground = nullptr;
	Object2D* _net = nullptr;
	Player2D* _player = nullptr;

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

