#include "pch.h"
#include "Scene.h"

HRESULT Scene::Init()
{
    return TRUE;
}

HRESULT Scene::Frame()
{
    return TRUE;
}

HRESULT Scene::Render()
{
    return TRUE;
}

HRESULT Scene::Release()
{
    return TRUE;
}

void Scene::CreateScene(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmedtateContext)
{
    _pd3dDevice = pd3dDevice;
    _pImmediateContext = pImmedtateContext;
}

void Scene::AddObject(Object* pObject)
{
    _pObjects.push_back(pObject);
}

void Scene::AddEffect()
{
	Effect* pEffect = new Effect;

	UINT iEffect = 0;
	if (iEffect == 0)
		pEffect->_pSprite = SPRITE->GetPtr(L"rtEffect");

	pEffect->_effectTimer = 0.0f;
	RECT rt = pEffect->_pSprite->_uvs[0];
	pEffect->_rect.x = rt.left;
	pEffect->_rect.y = rt.top;
	pEffect->_rect.w = rt.right;
	pEffect->_rect.h = rt.bottom;

	pEffect->_index = 0;
	pEffect->_lifeTime = 0.2f;

	if (_pBall)
	{
		pEffect->_position = { _pBall->_collision.x + 40.0f, _pBall->_collision.y + 80.0f };
	}

	pEffect->_step = pEffect->_lifeTime / pEffect->_pSprite->_uvs.size();
	pEffect->_maxIndex = pEffect->_pSprite->_uvs.size();

	pEffect->_pSprite->SetRect(pEffect->_rect);
	pEffect->_pSprite->SetPosition(pEffect->_position);

	_pEffects.push_back(pEffect);
}
