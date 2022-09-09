#pragma once

#include "Core.h"

class Sample : public Core
{
public:
	Sample() = default;
	virtual ~Sample() = default;

	// 초기화
	virtual HRESULT Init() final;
	// 프레임
	virtual HRESULT Frame() final;
	// 렌더
	virtual HRESULT Render() final;
	// 릴리즈
	virtual HRESULT Release() final;

	POINT pos;
};

