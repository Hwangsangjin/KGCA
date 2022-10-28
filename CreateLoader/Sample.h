#pragma once

#include "Core.h"
//#include "FbxLoader.h"

class Sample : public Core
{
public:
	Sample() = default;
	virtual ~Sample() = default;

	// �ʱ�ȭ
	virtual HRESULT Init() override;
	// ������ ���
	virtual HRESULT Frame() override;
	// ����
	virtual HRESULT Render() override;
	// �޸� ����
	virtual HRESULT Release() override;

private:
	class Scene* _pScene = nullptr;
	//FbxLoader _fbxLoader;
	//class Camera* _pMainCamera;
};

