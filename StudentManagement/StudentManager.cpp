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
void StudentManager::release()
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

		// 종료 선택시 인스턴스 해제
		if (select == EXIT)
		{
			cout << endl;
			print_exit();
			cout << endl;
			release();
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

// 리스트 출력
void StudentManager::print_list()
{
	cout << "번호" << '\t';
	cout << "이름" << '\t';
	cout << "국어" << '\t';
	cout << "영어" << '\t';
	cout << "수학" << '\t';
	cout << "총점" << '\t';
	cout << "평균" << '\t';
	cout << endl;
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
	cout << "[7]읽기" << " ";
	cout << "[0]종료" << " ";
	cout << endl << endl;

	cout << "메뉴 선택 >> ";
}

// 검색 출력
void StudentManager::print_search()
{
	cout << "= 검색 완료 =" << endl << endl;
}

// 저장 완료
void StudentManager::print_save()
{
	cout << "= 저장 완료 =" << endl << endl;
}

// 종료 출력
void StudentManager::print_exit()
{
	cout << "= 프로그램 종료 = " << endl;
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
			students.push_back(new Student(index, "샘플", rand() % 100 + 1, rand() % 100 + 1, rand() % 100 + 1));
			index++;
		}
		else
		{
			students.push_front(new Student(index, "샘플", rand() % 100 + 1, rand() % 100 + 1, rand() % 100 + 1));
			index++;
		}
	}

	system("cls");
}

// 정렬
void StudentManager::sort()
{
	students.sort();
}

// 검색
void StudentManager::search()
{
	int index;

	cout << "번호 선택 >> ";
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

// 추가
void StudentManager::add()
{
	string name;
	int kor;
	int eng;
	int math;

	cout << "학생 이름 >> ";
	cin >> name;
	name = name.substr(0, 6);

	cout << "국어 점수 >> ";
	cin >> kor;

	if (kor < 0 || kor > 100)
	{
		kor = 100;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	cout << "영어 점수 >> ";
	cin >> eng;

	if (eng < 0 || eng > 100)
	{
		eng = 100;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	
	cout << "수학 점수 >> ";
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
		FILE* stream;
		string filename;

		cout << "파일명 입력 >> ";
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

// 로드
void StudentManager::load()
{
	FILE* stream;
	string filename;

	cout << "파일명 입력 >> ";
	cin >> filename;

	fopen_s(&stream, filename.c_str(), "w");

	for (auto& i : students)
	{
		fscanf(stream, "%d\t%s\t%d\t%d\t%d\t%d\t%.1lf\n", i->get_index(), i->get_name().c_str(), i->get_kor(), i->get_eng(), i->get_math(), i->get_total(), i->get_avg());
	}

	fclose(stream);
}
