#pragma once

#include "Student.h"
#include "LinkedList.h"

enum MENU
{
	EXIT,
	SAMPLE,
	SORT,
	SEARCH,
	ADD,
	REMOVE,
	SAVE,
};

class StudentManager
{
private:
	static unsigned int index;
	static StudentManager* instance;
	LinkedList<Student*> students;

	StudentManager();
	~StudentManager();

public:
	static StudentManager* create();
	static void destory();

	void run();
	void print_data();
	void print_all_data();
	void print_no_data();
	void print_title();
	void print_menu();
	void sample();
	void sort();
	void search();
	void add();
	void remove();
	void save();
};

