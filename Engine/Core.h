#pragma once

#include "Window.h"

class Core : public Window
{
private:
	// 실행 플래그
	bool is_Running_ = true;

public:
	// 생성자, 소멸자
	Core() = default;
	virtual ~Core() = default;

	// 초기화
	virtual HRESULT Init() override;
	// 프레임 계산
	virtual HRESULT Frame() override;
	// 렌더
	virtual HRESULT Render() override;
	// 메모리 해제
	virtual HRESULT Release() override;
	// 실행
	virtual HRESULT Run() final;

	// 리소스 생성, 삭제
	virtual HRESULT CreateResource() override;
	virtual HRESULT DeleteResource() override;

	// 코어 함수
	HRESULT CoreInit();
	HRESULT CoreFrame();
	HRESULT CorePreRender();
	HRESULT CoreRender();
	HRESULT CorePostRender();
	HRESULT CoreRelease();
};

