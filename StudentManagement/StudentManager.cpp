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

// 생성
StudentManager* StudentManager::create()
{
	if (instance == nullptr)
	{
		instance = new StudentManager;
	}

	return instance;
}

// 해제
void StudentManager::destory()
{
	if (instance == nullptr)
	{
		return;
	}

	delete instance;
	instance = nullptr;
}

// 실행
void StudentManager::run()
{
	cout << "< 학생 관리 프로그램 >" << endl << endl;

	while (true)
	{
		srand(time(0));
		print();
		cout << endl;

		cout << "[1] 추가" << endl;
		cout << "[2] 삭제" << endl;
		cout << "[3] 검색" << endl;
		cout << "[4] 출력" << endl;
		cout << "[5] 저장" << endl;
		cout << "[6] 읽기" << endl;
		cout << "[0] 종료" << endl << endl;

		cout << "메뉴 선택 >> ";

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
			cout << "= 종료 = " << endl;
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

// 추가
void StudentManager::add()
{
	char name[10];
	unsigned int kor;
	unsigned int eng;
	unsigned int math;

	cout << "학생 이름 : ";
	cin >> name;

	cout << "국어 점수 : ";
	cin >> kor;

	cout << "영어 점수 : ";
	cin >> eng;
	
	cout << "수학 점수 : ";
	cin >> math;

	students.push_back(new Student(StudentManager::id, name, kor, eng, math));
	id++;

	system("cls");
}

// 삭제
void StudentManager::remove()
{
	if (students.empty())
	{
		cout << "= 데이터 없음 =" << endl << endl;
	}
	else
	{
		students.pop_back();
		id--;
	}
}

// 검색
void StudentManager::search()
{
}

// 정렬
void StudentManager::sort()
{
}

// 출력
void StudentManager::print()
{
	if (students.empty())
	{   
		system("cls");
		cout << "< 학생 관리 프로그램 >" << endl << endl;
		cout << "= 데이터 없음 =" << endl;
	}
	else
	{
		cout << "< 학생 관리 프로그램 >" << endl << endl;

		cout << "번호" << '\t';
		cout << "이름" << '\t';
		cout << "국어" << '\t';
		cout << "영어" << '\t';
		cout << "수학" << '\t';
		cout << "총점" << '\t';
		cout << "평균" << '\t';
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

// 저장
void StudentManager::save()
{
	if (students.empty())
	{
		cout << "= 데이터 없음 =" << endl << endl;
	}
	else
	{
		ofstream fout;
		fout.open("Student.txt", ios::app);

		if (fout.is_open())
		{
			cout << "= 저장 완료 =" << endl << endl;
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

// 로드
void StudentManager::load()
{
	ifstream fin;
	fin.open("Student.txt");

	if (fin.fail())
	{
		cout << "= 파일 없음 =" << endl << endl;
	}
	else
	{
		cout << "번호" << '\t';
		cout << "이름" << '\t';
		cout << "국어" << '\t';
		cout << "영어" << '\t';
		cout << "수학" << '\t';
		cout << "총점" << '\t';
		cout << "평균" << '\t';
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
