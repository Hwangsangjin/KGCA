#pragma once
#include <iostream>
struct Test
{
	int num;
	//char name[20];

	Test(int i)
	{ 
		num = i;
	}
	//Test(int i, const char* inc)
	//{
	//	num = i;
	//	strcpy_s(name, inc);
	//}

	friend std::ostream& operator<<(std::ostream& os, const Test& test)
	{
		os << test;
		return os;
	}

	friend std::ofstream& operator<<(std::ofstream& fs, const Test& test)
	{
		fs << test;
		return fs;
	}

	friend std::istream& operator>>(std::istream& is, Test& test)
	{
		is >> test;
		return is;
	}

	friend std::ostream& operator<<(std::ostream& os, Test& test)
	{
		os << test;
		return os;
	}
};

