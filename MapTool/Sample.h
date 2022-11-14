#pragma once

#include "Core.h"

class Sample : public Core
{
private:
	class Scene* _pScene = nullptr;

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

	// 리소스 생성
	virtual HRESULT CreateDXResource() override;
};

