#include <iostream>
#include <windows.h>
#include "Quadtree.h"

int main()
{
	// ����Ʈ��
	Quadtree quadtree;

	// ������Ʈ
	std::map<int, Object*> objects;

	// ����Ʈ���� ������ ���
	if (quadtree.Create(Rect(100.0f, 100.0f, 200.0f, 200.0f)))
	{
		// ������Ʈ ��ġ
		for (size_t i = 0; i < 10; i++)
		{
			Object* pNewObject = new Object;
			Rect rect;
			rect.left = cosf(rand()) * 100.0f;
			rect.top = sinf(rand()) * 100.0f;
			rect.right = 10.0f;
			rect.bottom = 10.0f;
			pNewObject->Create(rect);

			// ������Ʈ ���� ����
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