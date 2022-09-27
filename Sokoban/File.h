#pragma once

class File
{
private:
	int _size;
	char* _data;

public:
	File(const char* filename);
	~File();

	int GetSize() const;
	const char* GetData() const;
	unsigned int GetUnsigned(int position) const;
};

