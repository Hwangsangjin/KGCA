#pragma once

#include "Window.h"
#include <memory>

class Sample : public Window
{
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

	// 리소스 생성, 삭제
	virtual HRESULT CreateResource() override;
	virtual HRESULT DeleteResource() override;
};

