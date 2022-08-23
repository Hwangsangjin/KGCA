#include <iostream>
#include <windows.h>
#include "Quadtree.h"

int main()
{
	// 쿼드트리
	Quadtree quadtree;

	// 오브젝트
	std::map<int, Object*> objects;

	// 쿼드트리를 생성한 경우
	if (quadtree.Create(Rect(100.0f, 100.0f, 200.0f, 200.0f)))
	{
		// 오브젝트 배치
		for (size_t i = 0; i < 10; i++)
		{
			Object* pNewObject = new Object;
			Rect rect;
			rect.left = cosf(rand()) * 100.0f;
			rect.top = sinf(rand()) * 100.0f;
			rect.right = 10.0f;
			rect.bottom = 10.0f;
			pNewObject->Create(rect);

			// 오브젝트 통합 관리
			objects.insert(std::make_pair(i, pNewObject));
			quadtree.AddObject(pNewObject);
		}
	}

	while (true)
	{
		quadtree.Reset(quadtree._pRootNode);
		for (auto& object : objects)
		{
			Object* pObject = object.second;
			pObject->SetPosition(pObject->_rect.left, pObject->_rect.top);
			quadtree.AddObject(pObject);
		}
		
		Sleep(1000);
	}

	for (auto object : objects)
	{
		Object* pObject = object.second;
		delete pObject;
	}

	objects.clear();

	return 0;
}