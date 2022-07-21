#pragma once

#include "Student.h"
#include "LinkedList.h"

enum MENU
{
	EXIT,
	ADD,
	REMOVE,
	SEARCH,
	SORT,
	SAVE,
	LOAD
};

class StudentManager
{
private:
	static unsigned int id;
	static StudentManager* instance;
	LinkedList<Student*> students;

	StudentManager();
	~StudentManager();

public:
	static StudentManager* create();
	static void destory();

	void run();
	void add();
	void remove();
	void search();
	void sort();
	void print();
	void save();
	void load();
};

