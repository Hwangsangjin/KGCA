#include "StudentManager.h"
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

unsigned int StudentManager::id = 1;
StudentManager* StudentManager::instance = nullptr;

StudentManager::StudentManager()
{
}

StudentManager::~StudentManager()
{
}

// ����
StudentManager* StudentManager::create()
{
	if (instance == nullptr)
	{
		instance = new StudentManager;
	}

	return instance;
}

// ����
void StudentManager::destory()
{
	if (instance == nullptr)
	{
		return;
	}

	delete instance;
	instance = nullptr;
}

// ����
void StudentManager::run()
{
	cout << "< �л� ���� ���α׷� >" << endl << endl;

	while (true)
	{
		srand(time(0));
		print();
		cout << endl;

		cout << "[1] �߰�" << endl;
		cout << "[2] ����" << endl;
		cout << "[3] �˻�" << endl;
		cout << "[4] ���" << endl;
		cout << "[5] ����" << endl;
		cout << "[6] �б�" << endl;
		cout << "[0] ����" << endl << endl;

		cout << "�޴� ���� >> ";

		unsigned int select;
		cin >> select;

		if (cin.fail())
		{
			system("cls");
			cin.clear();
			cin.ignore(INT_MAX, '\n');

			continue;
		}

		if (select == EXIT)
		{
			system("cls");
			destory();
			cout << "= ���� = " << endl;
			break;
		}

		switch (select)
		{
		case ADD:
			add();
			break;
		case REMOVE:
			system("cls");
			remove();
			break;
		case SEARCH:
			system("cls");
			search();
			break;
		case SORT:
			system("cls");
			print();
			break;
		case SAVE:
			system("cls");
			save();
			break;
		case LOAD:
			system("cls");
			load();
			break;
		default:
			system("cls");
			break;
		}
	}
}

// �߰�
void StudentManager::add()
{
	char name[10];
	unsigned int kor;
	unsigned int eng;
	unsigned int math;

	cout << "�л� �̸� : ";
	cin >> name;

	cout << "���� ���� : ";
	cin >> kor;

	cout << "���� ���� : ";
	cin >> eng;
	
	cout << "���� ���� : ";
	cin >> math;

	students.push_back(new Student(StudentManager::id, name, kor, eng, math));
	id++;

	system("cls");
}

// ����
void StudentManager::remove()
{
	if (students.empty())
	{
		cout << "= ������ ���� =" << endl << endl;
	}
	else
	{
		students.pop_back();
		id--;
	}
}

// �˻�
void StudentManager::search()
{
}

// ����
void StudentManager::sort()
{
}

// ���
void StudentManager::print()
{
	if (students.empty())
	{   
		system("cls");
		cout << "< �л� ���� ���α׷� >" << endl << endl;
		cout << "= ������ ���� =" << endl;
	}
	else
	{
		cout << "< �л� ���� ���α׷� >" << endl << endl;

		cout << "��ȣ" << '\t';
		cout << "�̸�" << '\t';
		cout << "����" << '\t';
		cout << "����" << '\t';
		cout << "����" << '\t';
		cout << "����" << '\t';
		cout << "���" << '\t';
		cout << endl;

		for (auto& i : students)
		{
			cout << i->get_id() << '\t';
			cout << i->get_name() << '\t';
			cout << i->get_kor() << '\t';
			cout << i->get_eng() << '\t';
			cout << i->get_math() << '\t';
			cout << i->get_total() << '\t';
			cout << i->get_avg() << endl;
		}
	}
}

// ����
void StudentManager::save()
{
	if (students.empty())
	{
		cout << "= ������ ���� =" << endl << endl;
	}
	else
	{
		ofstream fout;
		fout.open("Student.txt", ios::app);

		if (fout.is_open())
		{
			cout << "= ���� �Ϸ� =" << endl << endl;
		}

		for (auto& i : students)
		{
			fout << i->get_id() << '\t';
			fout << i->get_name() << '\t';
			fout << i->get_kor() << '\t';
			fout << i->get_eng() << '\t';
			fout << i->get_math() << '\t';
			fout << i->get_total() << '\t';
			fout << i->get_avg() << endl;
		}

		fout.close();
	}
}

// �ε�
void StudentManager::load()
{
	ifstream fin;
	fin.open("Student.txt");

	if (fin.fail())
	{
		cout << "= ���� ���� =" << endl << endl;
	}
	else
	{
		cout << "��ȣ" << '\t';
		cout << "�̸�" << '\t';
		cout << "����" << '\t';
		cout << "����" << '\t';
		cout << "����" << '\t';
		cout << "����" << '\t';
		cout << "���" << '\t';
		cout << endl;

		string str;
		while (getline(fin, str))
		{
			cout << str << endl;
		}
		cout << endl;
	}

	fin.close();
}
