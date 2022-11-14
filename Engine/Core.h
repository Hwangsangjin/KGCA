#pragma once

#include "Window.h"
#include "Input.h"
#include "Timer.h"
#include "Writer.h"
#include "DxRT.h"
#include "DxState.h"
#include "SoundManager.h"
#include "ShaderManager.h"
#include "SpriteManager.h"
#include "TextureManager.h"

class Core : public Window
{
public:
	// 실행 플래그
	bool _isRun = true;

	// 코어 함수
	HRESULT CoreInit();
	HRESULT CoreFrame();
	HRESULT CorePreRender();
	HRESULT CoreRender();
	HRESULT CorePostRender();
	HRESULT CoreRelease();

	// 폰트
	Writer _writer;

	// 배경
	Object _background;

	// 렌더타겟
	DxRT _rendertarget;

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
	virtual HRESULT CreateDXResource() override;
	virtual HRESULT DeleteDXResource() override;

	// 툴
	HRESULT Tool();
};

