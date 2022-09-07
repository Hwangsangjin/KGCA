#pragma once

#include "Core.h"

class Sample : public Core
{
public:
	// 초기화
	virtual HRESULT Init() override;
	// 프레임
	virtual HRESULT Frame() override;
	// 렌더
	virtual HRESULT Render() override;
	// 릴리즈
	virtual HRESULT Release() override;
};

