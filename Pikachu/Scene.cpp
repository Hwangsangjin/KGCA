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

void Scene::AddEffect(Object2D* pObject)
{
	Effect* pEffect = new Effect;

	pEffect->_pSprite = SPRITE->GetPtr(L"rtBallEffect");

	pEffect->_effectTimer = 0.0f;
	RECT rt = pEffect->_pSprite->_uvs[0];
	pEffect->_rect.x1 = rt.left;
	pEffect->_rect.y1 = rt.top;
	pEffect->_rect.w = rt.right;
	pEffect->_rect.h = rt.bottom;

	pEffect->_index = 0;
	pEffect->_lifeTime = 0.2f;
	pEffect->_position = { pObject->_collision.cx , pObject->_collision.cy + pObject->_rect.h / HALF };
	pEffect->_step = pEffect->_lifeTime / pEffect->_pSprite->_uvs.size();
	pEffect->_maxIndex = pEffect->_pSprite->_uvs.size();

	pEffect->_pSprite->SetRect(pEffect->_rect);
	pEffect->_pSprite->SetPosition(pEffect->_position);

	pEffect->_collision = pEffect->_pSprite->_collision;
	pEffect->_collision.x1 = pEffect->_position.x;
	pEffect->_collision.y1 = pEffect->_position.y;

	_pEffects.push_back(pEffect);
}
