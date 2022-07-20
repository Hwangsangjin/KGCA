#pragma once

#include "Student.h"
#include "LinkedList.h"
#include <iostream>
using namespace std;

enum MENU
{
	NONE,
	ADD,
	REMOVE,
	SEARCH,
	PRINT,
	EXIT
};

class StudentManager
{
private:
	LinkedList<Student*> students;

public:
	StudentManager() {};

	void run();

	void add();
	void remove();
	void search();
	void print();

};

