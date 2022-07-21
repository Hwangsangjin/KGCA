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

	while (true)
	{
		// 랜덤 함수 사용
		srand(unsigned int(time(0)));

		// 파일명 한글 입력시 오류 처리
		setlocale(LC_ALL, "korean");

		// 타이틀 출력
		print_title();

		// 데이터 출력
		print_data();

		// 메뉴 출력
		print_menu();

		// 메뉴 선택
		int select;
		cin >> select;

		// 메뉴 선택 오류 처리
		if (cin.fail())
		{
			system("cls");
			cin.clear();
			cin.ignore(INT_MAX, '\n');

			continue;
		}

		// 종료 선택시 인스턴스 삭제
		if (select == EXIT)
		{
			destory();
			cout << "= 프로그램 종료 = " << endl;
			system("pause");
			break;
		}

		// 분기문
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

// 출력
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

// 데이터 전체
void StudentManager::print_all_data()
{
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

// 데이터 없음
void StudentManager::print_no_data()
{
	cout << "= 데이터 없음 =" << endl << endl;
}

// 타이틀 출력
void StudentManager::print_title()
{
	cout << "< 학생 관리 프로그램 >" << endl << endl;
}

// 메뉴 출력
void StudentManager::print_menu()
{
	cout << "[1]샘플" << " ";
	cout << "[2]정렬" << " ";
	cout << "[3]검색" << " ";
	cout << "[4]추가" << " ";
	cout << "[5]삭제" << " ";
	cout << "[6]저장" << " ";
	cout << "[0]종료" << " ";
	cout << endl;

	cout << "메뉴 선택 >> ";
}

// 샘플
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

// 정렬
void StudentManager::sort()
{
}

// 검색
void StudentManager::search()
{
}

// 추가
void StudentManager::add()
{
	char name[32];
	unsigned int kor;
	unsigned int eng;
	unsigned int math;

	cout << "학생 이름 >> ";
	cin >> name;

	cout << "국어 점수 >> ";
	cin >> kor;

	cout << "영어 점수 >> ";
	cin >> eng;
	
	cout << "수학 점수 >> ";
	cin >> math;

	students.push_back(new Student(index, name, kor, eng, math));
	index++;

	system("cls");
}

// 삭제
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

// 저장
void StudentManager::save()
{
	if (students.empty())
	{
		print_no_data();
	}
	else
	{
		string filename;

		cout << "파일명 입력 >> ";
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
