#include "StudentManager.h"
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

// ����
void StudentManager::run()
{
	cout << "< �л� ���� ���α׷� >" << endl << endl;

	while (true)
	{
		cout << "[1] ���" << endl;
		cout << "[2] ����" << endl;
		cout << "[3] �˻�" << endl;
		cout << "[4] ���" << endl;
		cout << "[5] ����" << endl;
		cout << "[6] �ε�" << endl;
		cout << "[0] ����" << endl << endl;
		cout << "�޴� ���� >> ";

		int select;
		cin >> select;

		if (cin.fail())
		{
			cin.clear();

			continue;
		}

		switch (select)
		{
		case ADD:
			add();
			break;
		case REMOVE:
			remove();
			break;
		case SEARCH:
			search();
			break;
		case PRINT:
			print();
			break;
		case SAVE:
			save();
			break;
		case LOAD:
			load();
			break;
		case EXIT:
			break;
		default:
			cout << endl << "�޴� ���� ���� " << endl << endl;
			break;
		}
	}
}

// �߰�
void StudentManager::add()
{
	{
		unsigned int number;
		char name[10];
		unsigned int kor;
		unsigned int eng;
		unsigned int math;

		cout << endl << "�л� ��ȣ : ";
		cin >> number;
		cout << "�л� �̸� : ";
		cin >> name;
		cout << "���� ���� : ";
		cin >> kor;
		cout << "���� ���� : ";
		cin >> eng;
		cout << "���� ���� : ";
		cin >> math;
		cout << endl;
		students.push_back(new Student(number, name, kor, eng, math));
	}
}

// ����
void StudentManager::remove()
{
	students.pop_back();
}

// �˻�
void StudentManager::search()
{
}

// ���
void StudentManager::print()
{
	if (students.empty())
	{
		cout << endl << "= ������ ���� =" << endl << endl;
	}
	else
	{
		cout << "��ȣ" << '\t' << "�̸�" << '\t' << "����" << '\t' << "����" << '\t' << "����" << '\t' << "����" << '\t' << "���" << endl;

		for (auto& i : students)
		{
			cout << i->get_number() << '\t';
			cout << i->get_name() << '\t';
			cout << i->get_kor() << '\t';
			cout << i->get_eng() << '\t';
			cout << i->get_math() << '\t';
			cout << i->get_total() << '\t';
			cout << i->get_avg();
		}
		cout << endl;
	}
}

// ����
void StudentManager::save()
{
	ofstream fout;
	fout.open("Student.txt", ios::app);

	fout << "��ȣ" << '\t';
	fout << "�̸�" << '\t';
	fout << "����" << '\t';
	fout << "����" << '\t';
	fout << "����" << '\t';
	fout << "����" << '\t';
	fout << "���" << endl;

	for (auto& i : students)
	{
		fout << i->get_number() << '\t';
		fout << i->get_name() << '\t';
		fout << i->get_kor() << '\t';
		fout << i->get_eng() << '\t';
		fout << i->get_math() << '\t';
		fout << i->get_total() << '\t';
		fout << i->get_avg() << endl;
	}
	cout << endl;

	fout.close();
}

// �ε�
void StudentManager::load()
{
	ifstream fin;
	fin.open("Student.txt");

	if (fin.fail())
	{
		cout << endl << "= ������ ���� =" << endl << endl;
	}

	string str;
	while (::getline(fin, str))
	{
		cout << str << endl;
	}

	fin.close();
}
