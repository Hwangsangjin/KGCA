#pragma once

template<typename T>
class Array2D
{
private:
	T* _array;
	int _size0;
	int _size1;

public:
	Array2D()
		: _array(nullptr)
	{}
	~Array2D()
	{
		delete[] _array;
		_array = nullptr;
	}

	void SetSize(int size0, int size1)
	{
		_size0 = size0;
		_size1 = size1;
		_array = new T[size0 * size1];
	}

	T& operator()(int index0, int index1)
	{
		return _array[index1 * _size0 + index0];
	}

	const T& operator()(int index0, int index1) const
	{
		return _array[index1 * _size0 + index0];
	}
};

