#pragma once

#include "Core.h"
#include "Title.h"
#include "InGame.h"

class Sample : public Core
{
private:
	Scene* _pScene = nullptr;
	Title* _pTitle = nullptr;
	InGame* _pInGame = nullptr;

public:
	Sample() = default;
	virtual ~Sample() = default;

	// 초기화
	virtual HRESULT Init() override;
	// 프레임 계산
	virtual HRESULT Frame() override;
	// 렌더
	virtual HRESULT Render() override;
	// 메모리 해제
	virtual HRESULT Release() override;
};

