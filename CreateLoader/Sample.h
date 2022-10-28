#pragma once

#include "Core.h"
//#include "FbxLoader.h"

class Sample : public Core
{
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

private:
	class Scene* _pScene = nullptr;
	//FbxLoader _fbxLoader;
	//class Camera* _pMainCamera;
};

