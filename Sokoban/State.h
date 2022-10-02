#pragma once

#include "Array2D.h"

class Image;

class State
{
private:
	class Object;	// Ŭ���� ����
	int _width;
	int _height;

	Array2D<Object> _objects;
	Array2D<bool> _flags;
	Image* _image;	// �̹���
	int _moveCount;	// �̵� �� ī��Ʈ

	void SetSize(const char* stageData, int size);

public:
	State(const char* stageData, int size);
	~State();

	void Update(int dx, int dy);
	void Draw() const;
	bool IsCleared() const;
};

