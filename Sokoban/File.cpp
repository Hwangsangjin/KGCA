#include "File.h"
#include <fstream>

File::File(const char* filename)
    : _size(0)
    , _data(nullptr)
{
	std::ifstream in(filename, std::ifstream::binary);
	if (in)
	{
		in.seekg(0, std::ifstream::end);		// 맨 끝으로 이동
		_size = static_cast<int>(in.tellg());	// 위치 = 파일 크기
		in.seekg(0, std::ifstream::beg);		// 맨 처음으로 이동
		_data = new char[_size];				// 영역 확보
		in.read(_data, _size);					// 읽기
	}
}

File::~File()
{
	delete[] _data;
	_data = nullptr;
}

int File::GetSize() const
{
    return _size;
}

const char* File::GetData() const
{
    return _data;
}

unsigned int File::GetUnsigned(int position) const
{
	const unsigned char* up;
	up = reinterpret_cast<const unsigned char*>(_data);
	unsigned int r = up[position];
	r |= up[position + 1] << 8;
	r |= up[position + 2] << 16;
	r |= up[position + 3] << 24;

	return r;
}
