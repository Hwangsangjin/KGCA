#include "StudentManager.h"
#include <locale>
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

unsigned int StudentManager::index = 1;
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

	while (true)
	{
		// ���� �Լ� ���
		srand(unsigned int(time(0)));

		// ���ϸ� �ѱ� �Է½� ���� ó��
		setlocale(LC_ALL, "korean");

		// Ÿ��Ʋ ���
		print_title();

		// ������ ���
		print_data();

		// �޴� ���
		print_menu();

		// �޴� ����
		int select;
		cin >> select;

		// �޴� ���� ���� ó��
		if (cin.fail())
		{
			system("cls");
			cin.clear();
			cin.ignore(INT_MAX, '\n');

			continue;
		}

		// ���� ���ý� �ν��Ͻ� ����
		if (select == EXIT)
		{
			destory();
			cout << "= ���α׷� ���� = " << endl;
			system("pause");
			break;
		}

		// �б⹮
		switch (select)
		{
		case SAMPLE:
			sample();
			break;
		case SORT:
			break;
		case SEARCH:
			search();
			break;
		case ADD:
			add();
			break;
		case REMOVE:
			system("cls");
			remove();
			break;
		case SAVE:
			save();
			break;
		default:
			system("cls");
			break;
		}
	}
}

// ���
void StudentManager::print_data()
{
	if (students.empty())
	{
		system("cls");
		print_title();
		print_no_data();
	}
	else
	{
		print_all_data();
	}
}

// ������ ��ü
void StudentManager::print_all_data()
{
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
		cout << i->get_index() << '\t';
		cout << i->get_name() << '\t';
		cout << i->get_kor() << '\t';
		cout << i->get_eng() << '\t';
		cout << i->get_math() << '\t';
		cout << i->get_total() << '\t';
		cout << i->get_avg();
		cout << endl;
	}
	cout << endl;
}

// ������ ����
void StudentManager::print_no_data()
{
	cout << "= ������ ���� =" << endl << endl;
}

// Ÿ��Ʋ ���
void StudentManager::print_title()
{
	cout << "< �л� ���� ���α׷� >" << endl << endl;
}

// �޴� ���
void StudentManager::print_menu()
{
	cout << "[1]����" << " ";
	cout << "[2]����" << " ";
	cout << "[3]�˻�" << " ";
	cout << "[4]�߰�" << " ";
	cout << "[5]����" << " ";
	cout << "[6]����" << " ";
	cout << "[0]����" << " ";
	cout << endl;

	cout << "�޴� ���� >> ";
}

// ����
void StudentManager::sample()
{
	if (students.empty() == false)
	{
		students.clear();
		index = 1;
	}

	const int SAMPLE_SIZE = 20;

	for (size_t i = 0; i < SAMPLE_SIZE; i++)
	{
		int random = rand() % 2;

		if (random == 0)
		{
			students.push_back(new Student(index, "TEST", rand() % 100 + 1, rand() % 100 + 1, rand() % 100 + 1));
			index++;
		}
		else
		{
			students.push_front(new Student(index, "TEST", rand() % 100 + 1, rand() % 100 + 1, rand() % 100 + 1));
			index++;
		}
	}

	system("cls");
}

// ����
void StudentManager::sort()
{
}

// �˻�
void StudentManager::search()
{
}

// �߰�
void StudentManager::add()
{
	char name[32];
	unsigned int kor;
	unsigned int eng;
	unsigned int math;

	cout << "�л� �̸� >> ";
	cin >> name;

	cout << "���� ���� >> ";
	cin >> kor;

	cout << "���� ���� >> ";
	cin >> eng;
	
	cout << "���� ���� >> ";
	cin >> math;

	students.push_back(new Student(index, name, kor, eng, math));
	index++;

	system("cls");
}

// ����
void StudentManager::remove()
{
	if (students.empty())
	{
		print_no_data();
	}
	else
	{
		students.pop_back();
		index--;
	}
}

// ����
void StudentManager::save()
{
	if (students.empty())
	{
		print_no_data();
	}
	else
	{
		string filename;

		cout << "���ϸ� �Է� >> ";
		cin >> filename;

		ofstream fout;
		fout.open(filename, ios::out);

		if (fout.is_open())
		{
			for (auto& i : students)
			{
				fout << i->get_index() << '\t';
				fout << i->get_name() << '\t';
				fout << i->get_kor() << '\t';
				fout << i->get_eng() << '\t';
				fout << i->get_math() << '\t';
				fout << i->get_total() << '\t';
				fout << i->get_avg() << endl;
			}
		}

		fout.close();
		system("cls");
	}
}
