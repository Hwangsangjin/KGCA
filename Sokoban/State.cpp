#include "State.h"
#include "Image.h"

// 객체 클래스
class State::Object
{
public:
	enum Type
	{
		OBJ_SPACE,
		OBJ_WALL,
		OBJ_BLOCK,
		OBJ_MAN,

		OBJ_UNKNOWN
	};

	// 칸 그리는 함수
	enum ImageID
	{
		IMAGE_ID_PLAYER,
		IMAGE_ID_WALL,
		IMAGE_ID_BLOCK,
		IMAGE_ID_GOAL,
		IMAGE_ID_SPACE
	};

	Type _type;
	bool _flag;
	int _moveX;
	int _moveY;

	// 기본 생성자
	Object()
		: _type(OBJ_WALL)
		, _flag(false)
		, _moveX(0)
		, _moveY(0)
	{}

	// 스테이지 데이터의 문자로 자신을 초기화
	void Set(char c)
	{
		switch (c)
		{
		case '#': _type = OBJ_WALL; break;
		case ' ': _type = OBJ_SPACE; break;
		case 'o': _type = OBJ_BLOCK; break;
		case 'O': _type = OBJ_BLOCK; _flag = true; break;
		case '.': _type = OBJ_SPACE; _flag = true; break;
		case 'p': _type = OBJ_MAN; break;
		case 'P': _type = OBJ_MAN; _flag = true; break;
		}
	}

	// 배경 그리기
	void DrawBackground(int x, int y, const Image* image) const
	{
		ImageID id = IMAGE_ID_SPACE;

		if (_type == OBJ_WALL)
		{
			DrawCell(x, y, IMAGE_ID_WALL, image);
		}
		else
		{
			if (_flag)
			{
				DrawCell(x, y, IMAGE_ID_GOAL, image);
			}
			else
			{
				DrawCell(x, y, IMAGE_ID_SPACE, image);
			}
		}
	}

	// 전경 그리기
	void DrawForeground(int x, int y, const Image* image, int moveCount) const
	{
		// 움직이는 것은 사람과 상자뿐이다.
		ImageID id = IMAGE_ID_SPACE;	// 전경이 없다는 의미로 사용한다.

		if (_type == OBJ_BLOCK)
		{
			id = IMAGE_ID_BLOCK;
		}
		else if (_type == OBJ_MAN)
		{
			id = IMAGE_ID_PLAYER;
		}

		// 배경이 아니라면 이동을 계산
		if (id != IMAGE_ID_SPACE)
		{
			int dx = _moveX * (32 - moveCount);
			int dy = _moveY * (32 - moveCount);
			image->Draw(x * 32 - dx, y * 32 - dy, id * 32, 0, 32, 32);
		}
	}

	static void DrawCell(int x, int y, int id, const Image* image)
	{
		image->Draw(x * 32, y * 32, id * 32, 0, 32, 32);
	}

	// 이동
	void Move(int dx, int dy, Type replaced)
	{
		_moveX = dx;
		_moveY = dy;
		_type = replaced;
	}
};

State::State(const char* stageData, int size)
	: _image(nullptr)
{
	// 크기 측정
	SetSize(stageData, size);

	// 배열 보장
	_objects.SetSize(_width, _height);

	// 초기값 설정
	int x = 0;
	int y = 0;

	for (size_t i = 0; i < size; i++)
	{
		Object t;
		bool goal = false;

		switch (stageData[i]) {
		case '#': case ' ': case 'o': case 'O':
		case '.': case 'p': case 'P':
			_objects(x, y).Set(stageData[i]);
			++x;
			break;
		case '\n': x = 0; ++y; break;
		}
	}

	// 이미지 읽기
	_image = new Image("../../../Resource/Sokoban/Sokoban.dds");
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

void State::Update(int dx, int dy)
{
	// 이동 중 카운트가 32가 되면
	if (_moveCount == 32)
	{
		// 0으로 되돌리고
		_moveCount = 0;

		// 이동을 초기화
		for (size_t y = 0; y < _height; y++)
		{
			for (size_t x = 0; x < _width; x++)
			{
				_objects(x, y)._moveX = 0;
				_objects(x, y)._moveY = 0;
			}
		}
	}

	// 이동 중엔 갱신하지 않으므로 바로 return;
	if (_moveCount > 0)
	{
		_moveCount++;
		return;
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
			if (o(x, y)._type == Object::OBJ_MAN)
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

	// A. 그 방향이 빈칸이나 목적지 - 사람이 이동
	if (o(tx, ty)._type == Object::OBJ_SPACE)
	{
		o(tx, ty).Move(dx, dy, Object::OBJ_MAN);
		o(x, y).Move(dx, dy, Object::OBJ_SPACE);
		_moveCount = 1;
	}
	// B. 그 방향이 상자 - 그 방향에서 다음 칸이 빈카이나 목적지면 이동
	else if (o(tx, ty)._type == Object::OBJ_BLOCK)
	{
		// 2칸 앞이 범위 내인지 검사
		int tx2 = tx + dx;
		int ty2 = ty + dy;
		if (tx2 < 0 || ty2 < 0 || tx2 >= w || ty2 >= h)
		{
			// 밀 수 없다.
			return;
		}

		if (o(tx2, ty2)._type == Object::OBJ_SPACE)
		{
			// 차례로 교체
			o(tx2, ty2).Move(dx, dy, Object::OBJ_BLOCK);
			o(tx, ty).Move(dx, dy, Object::OBJ_MAN);
			o(x, y).Move(dx, dy, Object::OBJ_SPACE);

			// 이동 시작
			_moveCount = 1;
		}
	}
}

void State::Draw() const
{
	// 두 단계로 나누어 그린다. 우선 배경을 그린다.
	for (size_t y = 0; y < _height; y++)
	{
		for (size_t x = 0; x < _width; x++)
		{
			_objects(x, y).DrawBackground(x, y, _image);
		}
	}

	// 다음은 전경을 그린다. 
	for (size_t y = 0; y < _height; y++)
	{
		for (size_t x = 0; x < _width; x++)
		{
			_objects(x, y).DrawForeground(x, y, _image, _moveCount);
		}
	}
}

bool State::IsCleared() const
{
	for (int y = 0; y < _height; ++y)
	{
		for (int x = 0; x < _width; ++x)
		{
			if (_objects(x, y)._type == Object::OBJ_BLOCK)
			{
				if (_objects(x, y)._flag == false)
				{
					return false;
				}
			}
		}
	}

	return true;
}