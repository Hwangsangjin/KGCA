#include "StudentManager.h"

// 학생 관리 매니저 실행
void StudentManager::run()
{
	while (true)
	{
		cout << "[1] 학생 정보 등록" << endl;
		cout << "[2] 학생 정보 삭제" << endl;
		cout << "[3] 학생 정보 검색" << endl;
		cout << "[4] 학생 정보 출력" << endl;
		cout << "[5] 프로그램 종료" << endl;
		cout << endl;
		cout << "옵션 선택 >> ";

		int select;
		cin >> select;

		if (cin.fail())
		{
			cin.clear();

			continue;
		}

		if (select == EXIT)
		{
			break;
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
		}
	}
}

// 학생 정보 추가
void StudentManager::add()
{
	{
		int number;
		char name[10];
		int kor;
		int eng;
		int math;

		cout << "학생 번호 : ";
		cin >> number;
		cout << "학생 이름 : ";
		cin >> name;
		cout << "국어 점수 : ";
		cin >> kor;
		cout << "영어 점수 : ";
		cin >> eng;
		cout << "수학 점수 : ";
		cin >> math;

		students.push_back(new Student(number, name, kor, eng, math));
	}
}

// 학생 정보 제거
void StudentManager::remove()
{
	students.pop_back();
}

// 학생 정보 검색
void StudentManager::search()
{
}

// 학생 정보 출력
void StudentManager::print()
{
	cout << "번호" << " " << "이름" << " " << "국어" << " " << "영어" << " " << "수학" << " " << "총점" << " " << "평균" << endl;

	for (auto& i : students)
	{
		cout << i->get_number() << " " << i->get_name() << " " << i->get_kor() << " " << i->get_eng() << " " << i->get_math() << " " << i->get_total() << " " << i->get_avg() << endl;
	}
}
