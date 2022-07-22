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
void StudentManager::release()
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
			cout << endl;
			print_exit();
			cout << endl;
			release();
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
			sort();
			system("cls");
			break;
		case SEARCH:
			search();
			system("cls");
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
		case LOAD:
			load();
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
	print_list();

	for (auto& i : students)
	{
		cout << i->get_index() << '\t';
		cout << i->get_name() << '\t';
		cout << i->get_kor() << '\t';
		cout << i->get_eng() << '\t';
		cout << i->get_math() << '\t';
		cout << i->get_total() << '\t';
		cout.setf(ios::showpoint);
		cout.precision(4);
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

// ����Ʈ ���
void StudentManager::print_list()
{
	cout << "��ȣ" << '\t';
	cout << "�̸�" << '\t';
	cout << "����" << '\t';
	cout << "����" << '\t';
	cout << "����" << '\t';
	cout << "����" << '\t';
	cout << "���" << '\t';
	cout << endl;
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
	cout << "[7]�б�" << " ";
	cout << "[0]����" << " ";
	cout << endl << endl;

	cout << "�޴� ���� >> ";
}

// �˻� ���
void StudentManager::print_search()
{
	cout << "= �˻� �Ϸ� =" << endl << endl;
}

// ���� �Ϸ�
void StudentManager::print_save()
{
	cout << "= ���� �Ϸ� =" << endl << endl;
}

// ���� ���
void StudentManager::print_exit()
{
	cout << "= ���α׷� ���� = " << endl;
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
			students.push_back(new Student(index, "����", rand() % 100 + 1, rand() % 100 + 1, rand() % 100 + 1));
			index++;
		}
		else
		{
			students.push_front(new Student(index, "����", rand() % 100 + 1, rand() % 100 + 1, rand() % 100 + 1));
			index++;
		}
	}

	system("cls");
}

// ����
void StudentManager::sort()
{
	students.sort();
}

// �˻�
void StudentManager::search()
{
	int index;

	cout << "��ȣ ���� >> ";
	cin >> index;
	cout << endl;

	for (auto& i : students)
	{
		if (index == i->get_index())
		{
			print_search();
			print_list();

			cout << i->get_index() << '\t';
			cout << i->get_name() << '\t';
			cout << i->get_kor() << '\t';
			cout << i->get_eng() << '\t';
			cout << i->get_math() << '\t';
			cout << i->get_total() << '\t';
			cout.setf(ios::showpoint);
			cout.precision(3);
			cout << i->get_avg() << endl;
			cout << endl;

			system("pause");
		}
	}
}

// �߰�
void StudentManager::add()
{
	string name;
	int kor;
	int eng;
	int math;

	cout << "�л� �̸� >> ";
	cin >> name;
	name = name.substr(0, 6);

	cout << "���� ���� >> ";
	cin >> kor;

	if (kor < 0 || kor > 100)
	{
		kor = 100;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	cout << "���� ���� >> ";
	cin >> eng;

	if (eng < 0 || eng > 100)
	{
		eng = 100;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	
	cout << "���� ���� >> ";
	cin >> math;

	if (math < 0 || math > 100)
	{
		math = 100;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

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
		FILE* stream;
		string filename;

		cout << "���ϸ� �Է� >> ";
		cin >> filename;
	
		fopen_s(&stream, filename.c_str(), "w");

		for (auto& i : students)
		{
			fprintf(stream, "%d\t%s\t%d\t%d\t%d\t%d\t%.1lf\n", i->get_index(), i->get_name().c_str(), i->get_kor(), i->get_eng(), i->get_math(), i->get_total(), i->get_avg());
		}
		
		print_save();
		system("pause");

		fclose(stream);
		system("cls");
	}
}

// �ε�
void StudentManager::load()
{
	FILE* stream;
	string filename;

	cout << "���ϸ� �Է� >> ";
	cin >> filename;

	fopen_s(&stream, filename.c_str(), "w");

	for (auto& i : students)
	{
		fscanf(stream, "%d\t%s\t%d\t%d\t%d\t%d\t%.1lf\n", i->get_index(), i->get_name().c_str(), i->get_kor(), i->get_eng(), i->get_math(), i->get_total(), i->get_avg());
	}

	fclose(stream);
}
