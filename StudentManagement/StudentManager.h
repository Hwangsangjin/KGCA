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
	static unsigned int _index;
	static StudentManager* _instance;
	LinkedList<Student*> _students;

	StudentManager();
	~StudentManager();

public:
	static StudentManager* Instance();
	static void Release();

	void Run();

	void PrintData();
	void PrintAllData();
	void PrintNoData();
	void PrintTitle();
	void PrintList();
	void PrintMenu();
	void PrintSearch();
	void PrintSave();
	void PrintExit();

	void Sample();
	void Sort();
	void Search();
	void Add();
	void Remove();
	void Save();
	void Load();
};

