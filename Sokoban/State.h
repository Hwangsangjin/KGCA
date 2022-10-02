#pragma once

#include "Array2D.h"

class Image;

class State
{
private:
	class Object;	// 클래스 선언
	int _width;
	int _height;

	Array2D<Object> _objects;
	Array2D<bool> _flags;
	Image* _image;	// 이미지
	int _moveCount;	// 이동 중 카운트

	void SetSize(const char* stageData, int size);

public:
	State(const char* stageData, int size);
	~State();

	void Update(int dx, int dy);
	void Draw() const;
	bool IsCleared() const;
};

