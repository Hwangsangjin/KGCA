#include "StudentManager.h"
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

// 실행
void StudentManager::run()
{
	cout << "< 학생 관리 프로그램 >" << endl << endl;

	while (true)
	{
		cout << "[1] 등록" << endl;
		cout << "[2] 삭제" << endl;
		cout << "[3] 검색" << endl;
		cout << "[4] 출력" << endl;
		cout << "[5] 저장" << endl;
		cout << "[6] 로드" << endl;
		cout << "[0] 종료" << endl << endl;
		cout << "메뉴 선택 >> ";

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
			cout << endl << "메뉴 선택 오류 " << endl << endl;
			break;
		}
	}
}

// 추가
void StudentManager::add()
{
	{
		unsigned int number;
		char name[10];
		unsigned int kor;
		unsigned int eng;
		unsigned int math;

		cout << endl << "학생 번호 : ";
		cin >> number;
		cout << "학생 이름 : ";
		cin >> name;
		cout << "국어 점수 : ";
		cin >> kor;
		cout << "영어 점수 : ";
		cin >> eng;
		cout << "수학 점수 : ";
		cin >> math;
		cout << endl;
		students.push_back(new Student(number, name, kor, eng, math));
	}
}

// 삭제
void StudentManager::remove()
{
	students.pop_back();
}

// 검색
void StudentManager::search()
{
}

// 출력
void StudentManager::print()
{
	if (students.empty())
	{
		cout << endl << "= 데이터 없음 =" << endl << endl;
	}
	else
	{
		cout << "번호" << '\t' << "이름" << '\t' << "국어" << '\t' << "영어" << '\t' << "수학" << '\t' << "총점" << '\t' << "평균" << endl;

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

// 저장
void StudentManager::save()
{
	ofstream fout;
	fout.open("Student.txt", ios::app);

	fout << "번호" << '\t';
	fout << "이름" << '\t';
	fout << "국어" << '\t';
	fout << "영어" << '\t';
	fout << "수학" << '\t';
	fout << "총점" << '\t';
	fout << "평균" << endl;

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

// 로드
void StudentManager::load()
{
	ifstream fin;
	fin.open("Student.txt");

	if (fin.fail())
	{
		cout << endl << "= 데이터 없음 =" << endl << endl;
	}

	string str;
	while (::getline(fin, str))
	{
		cout << str << endl;
	}

	fin.close();
}
