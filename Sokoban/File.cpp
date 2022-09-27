#include "File.h"
#include <fstream>

File::File(const char* filename)
    : _size(0)
    , _data(nullptr)
{
	std::ifstream in(filename, std::ifstream::binary);
	if (in)
	{
		in.seekg(0, std::ifstream::end);		// �� ������ �̵�
		_size = static_cast<int>(in.tellg());	// ��ġ = ���� ũ��
		in.seekg(0, std::ifstream::beg);		// �� ó������ �̵�
		_data = new char[_size];				// ���� Ȯ��
		in.read(_data, _size);					// �б�
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
	unsigned int r = up[0];
	r |= up[1] << 8;
	r |= up[2] << 16;
	r |= up[3] << 24;

	return r;
}
