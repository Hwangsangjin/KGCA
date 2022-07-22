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
	LOAD
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
	static void release();

	void run();

	void print_data();
	void print_all_data();
	void print_no_data();
	void print_title();
	void print_list();
	void print_menu();
	void print_search();
	void print_save();
	void print_exit();

	void sample();
	void sort();
	void search();
	void add();
	void remove();
	void save();
	void load();
};

