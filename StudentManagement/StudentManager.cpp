#include "StudentManager.h"
#include <locale>
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

unsigned int StudentManager::_index = 1;
StudentManager* StudentManager::_instance = nullptr;

StudentManager::StudentManager()
{
}

StudentManager::~StudentManager()
{
}

// ����
StudentManager* StudentManager::Instance()
{
	if (_instance == nullptr)
	{
		_instance = new StudentManager;
	}

	return _instance;
}

// ����
void StudentManager::Release()
{
	if (_instance == nullptr)
	{
		return;
	}

	delete _instance;
	_instance = nullptr;
}

// ����
void StudentManager::Run()
{

	while (true)
	{
		// ���� �Լ� ���
		srand(unsigned int(time(0)));

		// ���ϸ� �ѱ� �Է½� ���� ó��
		setlocale(LC_ALL, "korean");

		// Ÿ��Ʋ ���
		PrintTitle();

		// ������ ���
		PrintData();

		// �޴� ���
		PrintMenu();

		// �޴� ����
		int select;
		std::cin >> select;

		// �޴� ���� ���� ó��
		if (std::cin.fail())
		{
			system("cls");
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');

			continue;
		}

		// ���� ���ý� �ν��Ͻ� ����
		if (select == EXIT)
		{
			std::cout << std::endl;
			PrintExit();
			std::cout << std::endl;
			Release();
			system("pause");
			break;
		}

		// �б⹮
		switch (select)
		{
		case SAMPLE:
			Sample();
			break;
		case SORT:
			Sort();
			system("cls");
			break;
		case SEARCH:
			Search();
			system("cls");
			break;
		case ADD:
			Add();
			break;
		case REMOVE:
			system("cls");
			Remove();
			break;
		case SAVE:
			Save();
			break;
		case LOAD:
			Load();
			break;
		default:
			system("cls");
			break;
		}
	}
}

// ���
void StudentManager::PrintData()
{
	if (_students.empty())
	{
		system("cls");
		PrintTitle();
		PrintNoData();
	}
	else
	{
		PrintAllData();
	}
}

// ������ ��ü
void StudentManager::PrintAllData()
{
	PrintList();

	for (auto& i : _students)
	{
		std::cout << i->GetIndex() << '\t';
		std::cout << i->GetName() << '\t';
		std::cout << i->GetKor() << '\t';
		std::cout << i->GetEng() << '\t';
		std::cout << i->GetMath() << '\t';
		std::cout << i->GetTotal() << '\t';
		std::cout.setf(std::ios::showpoint);
		std::cout.precision(4);
		std::cout << i->GetAvg();
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

// ������ ����
void StudentManager::PrintNoData()
{
	std::cout << "= ������ ���� =" << std::endl << std::endl;
}

// Ÿ��Ʋ ���
void StudentManager::PrintTitle()
{
	std::cout << "< �л� ���� ���α׷� >" << std::endl << std::endl;
}

// ����Ʈ ���
void StudentManager::PrintList()
{
	std::cout << "��ȣ" << '\t';
	std::cout << "�̸�" << '\t';
	std::cout << "����" << '\t';
	std::cout << "����" << '\t';
	std::cout << "����" << '\t';
	std::cout << "����" << '\t';
	std::cout << "���" << '\t';
	std::cout << std::endl;
}

// �޴� ���
void StudentManager::PrintMenu()
{
	std::cout << "[1]����" << " ";
	std::cout << "[2]����" << " ";
	std::cout << "[3]�˻�" << " ";
	std::cout << "[4]�߰�" << " ";
	std::cout << "[5]����" << " ";
	std::cout << "[6]����" << " ";
	std::cout << "[7]�б�" << " ";
	std::cout << "[0]����" << " ";
	std::cout << std::endl << std::endl;

	std::cout << "�޴� ���� >> ";
}

// �˻� ���
void StudentManager::PrintSearch()
{
	std::cout << "= �˻� �Ϸ� =" << std::endl << std::endl;
}

// ���� �Ϸ�
void StudentManager::PrintSave()
{
	std::cout << "= ���� �Ϸ� =" << std::endl << std::endl;
}

// ���� ���
void StudentManager::PrintExit()
{
	std::cout << "= ���α׷� ���� = " << std::endl;
}

// ����
void StudentManager::Sample()
{
	if (_students.empty() == false)
	{
		_students.clear();
		_index = 1;
	}

	const int SAMPLE_SIZE = 20;

	for (size_t i = 0; i < SAMPLE_SIZE; i++)
	{
		int random = rand() % 2;

		if (random == 0)
		{
			_students.push_back(new Student(_index, "����", rand() % 100 + 1, rand() % 100 + 1, rand() % 100 + 1));
			_index++;
		}
		else
		{
			_students.push_front(new Student(_index, "����", rand() % 100 + 1, rand() % 100 + 1, rand() % 100 + 1));
			_index++;
		}
	}

	system("cls");
}

// ����
void StudentManager::Sort()
{
	
}

// �˻�
void StudentManager::Search()
{
	int _index;

	std::cout << "��ȣ ���� >> ";
	std::cin >> _index;
	std::cout << std::endl;

	for (auto& i : _students)
	{
		if (_index == i->GetIndex())
		{
			PrintSearch();
			PrintList();

			std::cout << i->GetIndex() << '\t';
			std::cout << i->GetName() << '\t';
			std::cout << i->GetKor() << '\t';
			std::cout << i->GetEng() << '\t';
			std::cout << i->GetMath() << '\t';
			std::cout << i->GetTotal() << '\t';
			std::cout.setf(std::ios::showpoint);
			std::cout.precision(3);
			std::cout << i->GetAvg() << std::endl;
			std::cout << std::endl;

			system("pause");
		}
	}
}

// �߰�
void StudentManager::Add()
{
	std::string _name;
	int _kor;
	int _eng;
	int _math;

	std::cout << "�л� �̸� >> ";
	std::cin >> _name;
	_name = _name.substr(0, 6);

	std::cout << "���� ���� >> ";
	std::cin >> _kor;

	if (_kor < 0 || _kor > 100)
	{
		_kor = 100;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}

	std::cout << "���� ���� >> ";
	std::cin >> _eng;

	if (_eng < 0 || _eng > 100)
	{
		_eng = 100;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	
	std::cout << "���� ���� >> ";
	std::cin >> _math;

	if (_math < 0 || _math > 100)
	{
		_math = 100;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}

	_students.push_back(new Student(_index, _name, _kor, _eng, _math));
	_index++;

	system("cls");
}

// ����
void StudentManager::Remove()
{
	if (_students.empty())
	{
		PrintNoData();
	}
	else
	{
		_students.pop_back();
		_index--;
	}
}

// ����
void StudentManager::Save()
{
	if (_students.empty())
	{
		PrintNoData();
	}
	else
	{
		std::ofstream fout;
		std::string filename;

		std::cout << "���ϸ� �Է� >> ";
		std::cin >> filename;
	

		fout.open(filename, std::ios::out);

		for (auto& i : _students)
		{
			fout << i->GetIndex() << '\t';
			fout << i->GetName() << '\t';
			fout << i->GetKor() << '\t';
			fout << i->GetEng() << '\t';
			fout << i->GetMath() << '\t';
			fout << i->GetTotal() << '\t';
			fout << i->GetAvg() << std::endl;
		}
		
		PrintSave();
		system("pause");

		fout.close();
		system("cls");
	}
}

// �ε�
void StudentManager::Load()
{
	std::ifstream fin;
	std::string filename;

	std::cout << "���ϸ� �Է� >> ";
	std::cin >> filename;

	fin.open(filename);

	if (fin.is_open())
	{
		std::cout << std::endl;
		PrintList();

		std::string str;

		while (std::getline(fin, str))
		{
			std::cout << str << std::endl;
		}
		std::cout << std::endl;

		system("pause");
	}

	fin.close();
}
