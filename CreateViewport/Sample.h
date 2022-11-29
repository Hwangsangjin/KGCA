#pragma once

#include "Core.h"

class Object;

class Sample : public Core
{
private:
	// 오브젝트
	std::unique_ptr<Object> object_;

	// 뷰포트
	D3D11_VIEWPORT viewport_[4];

public:
	// 생성자, 소멸자
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
