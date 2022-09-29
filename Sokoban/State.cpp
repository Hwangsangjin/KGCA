#include "State.h"
#include "Image.h"

State::State(const char* stageData, int size)
	: _image(nullptr)
{
	// 크기 측정
	SetSize(stageData, size);

	// 배열 보장
	_objects.SetSize(_width, _height);
	_flags.SetSize(_width, _height);

	// 초기값 설정
	for (size_t y = 0; y < _height; y++)
	{
		for (size_t x = 0; x < _width; x++)
		{
			_objects(x, y) = OBJ_WALL;	// 벽
			_flags(x, y) = false;		// 목표 지점이 아님
		}
	}

	int x = 0;
	int y = 0;

	for (size_t i = 0; i < size; i++)
	{
		Object t;
		bool goal = false;

		switch (stageData[i])
		{
		case '#': t = OBJ_WALL; break;
		case ' ': t = OBJ_SPACE; break;
		case 'o': t = OBJ_BLOCK; break;
		case 'O': t = OBJ_BLOCK; goal = true; break;
		case '.': t = OBJ_SPACE; goal = true; break;
		case 'p': t = OBJ_MAN; break;
		case 'P': t = OBJ_MAN; goal = true; break;
		case '\n': x = 0; ++y; t = OBJ_UNKNOWN; break; // 줄 바꿈
		default: t = OBJ_UNKNOWN; break;
		}

		if (t != OBJ_UNKNOWN)
		{
			_objects(x, y) = t;
			_flags(x, y) = goal;
			x++;
		}
	}

	// 이미지 읽기
	_image = new Image("../../../Resource/Sokoban/Sokoban2.dds");
}

State::~State()
{
	delete _image;
	_image = nullptr;
}

void State::SetSize(const char* stageData, int size)
{
	// 초기화
	_width = _height = 0;

	// 현재 위치
	int x = 0;
	int y = 0;

	for (size_t i = 0; i < size; ++i)
	{
		switch (stageData[i])
		{
		case '#': case ' ': case 'o': case 'O':
		case '.': case 'p': case 'P':
			x++;
			break;
		case '\n':
			y++;
			// 최대 값 업데이트
			_width = (_width > x) ? _width : x;
			_height = (_height > y) ? _height : y;
			x = 0;
			break;
		}
	}
}

void State::DrawCell(int x, int y, ImageID id) const
{
	_image->Draw(x * 32, y * 32, id * 32, 0, 32, 32);
}

void State::Update(char input)
{
	int dx = 0;
	int dy = 0;

	switch (input)
	{
	case 'a': dx = -1; break;	// 왼쪽
	case 'd': dx = 1; break;	// 오른쪽
	case 'w': dy = -1; break;	// 위
	case 's': dy = 1; break;	// 아래
	}

	int w = _width;
	int h = _height;
	Array2D<Object>& o = _objects;

	int x, y;
	bool found = false;

	for (y = 0; y < _height; ++y)
	{
		for (x = 0; x < _width; ++x)
		{
			if (o(x, y) == OBJ_MAN)
			{
				found = true;
				break;
			}
		}

		if (found)
		{
			break;
		}
	}

	int tx = x + dx;
	int ty = y + dy;

	if (tx < 0 || ty < 0 || tx >= w || ty >= h)
	{
		return;
	}

	if (o(tx, ty) == OBJ_SPACE)
	{
		o(tx, ty) = OBJ_MAN;
		o(x, y) = OBJ_SPACE;
	}
	else if (o(tx, ty) == OBJ_BLOCK)
	{
		int tx2 = tx + dx;
		int ty2 = ty + dy;
		if (tx2 < 0 || ty2 < 0 || tx2 >= w || ty2 >= h)
		{
			return;
		}

		if (o(tx2, ty2) == OBJ_SPACE)
		{
			o(tx2, ty2) = OBJ_BLOCK;
			o(tx, ty) = OBJ_MAN;
			o(x, y) = OBJ_SPACE;
		}
	}
}

void State::Draw() const
{
	for (size_t y = 0; y < _height; y++)
	{
		for (size_t x = 0; x < _width; x++)
		{
			Object o = _objects(x, y);
			bool goal = _flags(x, y);

			// 벽을 제외하고 바닥을 그린다.
			if (o != OBJ_WALL)
			{
				if (goal)
				{
					DrawCell(x, y, IMAGE_ID_GOAL);
				}
				else
				{
					DrawCell(x, y, IMAGE_ID_SPACE);
				}
			}

			ImageID id = IMAGE_ID_SPACE;

			switch (o)
			{
			case OBJ_WALL: id = IMAGE_ID_WALL; break;
			case OBJ_BLOCK: id = IMAGE_ID_BLOCK; break;
			case OBJ_MAN: id = IMAGE_ID_PLAYER; break;
			}

			if (id != IMAGE_ID_SPACE)
			{
				DrawCell(x, y, id);
			}
		}
	}
}

bool State::IsCleared() const
{
	for (int y = 0; y < _height; ++y)
	{
		for (int x = 0; x < _width; ++x)
		{
			if (_objects(x, y) == OBJ_BLOCK)
			{
				if (_flags(x, y) == false)
				{
					return false;
				}
			}
		}
	}

	return true;
}