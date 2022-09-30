#pragma once

#include "Scene.h"

class InGame : public Scene
{
public: 
	uint64 _netTimer;
	uint64 _playerTimer;
	uint64 _enemyTimer;

	// 초기화
	virtual HRESULT Init() override;
	// 프레임 계산
	virtual HRESULT Frame() override;
	// 렌더
	virtual HRESULT Render() override;
	// 메모리 해제
	virtual HRESULT Release() override;
};

