#pragma once

#include "Array2D.h"

class Image;

class State
{
private:
	enum Object
	{
		OBJ_SPACE,
		OBJ_WALL,
		OBJ_BLOCK,
		OBJ_MAN,

		OBJ_UNKNOWN
	};

	enum ImageID
	{
		IMAGE_ID_PLAYER,
		IMAGE_ID_WALL,
		IMAGE_ID_BLOCK,
		IMAGE_ID_BLOCK_ON_GOAL,
		IMAGE_ID_GOAL,
		IMAGE_ID_SPACE
	};

	int _width;
	int _height;

	Array2D<Object> _objects;
	Array2D<bool> _flags;
	Image* _image;

	void SetSize(const char* stageData, int size);
	void DrawCell(int x, int y, ImageID id) const;

public:
	State(const char* stageData, int size);
	~State();

	void Update(char input);
	void Draw() const;
	bool IsCleared() const;
};

