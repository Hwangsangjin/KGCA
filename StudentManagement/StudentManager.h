#pragma once

#include "Student.h"
#include "LinkedList.h"
#include <iostream>

enum MENU
{
	NONE,
	ADD,
	REMOVE,
	SEARCH,
	PRINT,
	SAVE,
	LOAD,
	EXIT = 0
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
	void save();
	void load();
};

