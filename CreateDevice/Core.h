#pragma once

#include "Window.h"

class Core : public Window
{
private:
	// 실행 플래그
	bool _isRun = true;

	// 코어 함수
	HRESULT CInit();
	HRESULT CFrame();
	HRESULT CPreRender();
	HRESULT CRender();
	HRESULT CPostRender();
	HRESULT CRelease();

public:
	Core() = default;
	virtual ~Core() = default;

	// 초기화
	virtual HRESULT Init() override;
	// 프레임
	virtual HRESULT Frame() override;
	// 렌더
	virtual HRESULT Render() override;
	// 릴리즈
	virtual HRESULT Release() override;
	// 실행
	virtual HRESULT Run() override;
};

