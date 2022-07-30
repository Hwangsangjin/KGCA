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

// 생성
StudentManager* StudentManager::Instance()
{
	if (_instance == nullptr)
	{
		_instance = new StudentManager;
	}

	return _instance;
}

// 해제
void StudentManager::Release()
{
	if (_instance == nullptr)
	{
		return;
	}

	delete _instance;
	_instance = nullptr;
}

// 실행
void StudentManager::Run()
{

	while (true)
	{
		// 랜덤 함수 사용
		srand(unsigned int(time(0)));

		// 파일명 한글 입력시 오류 처리
		setlocale(LC_ALL, "korean");

		// 타이틀 출력
		PrintTitle();

		// 데이터 출력
		PrintData();

		// 메뉴 출력
		PrintMenu();

		// 메뉴 선택
		int select;
		std::cin >> select;

		// 메뉴 선택 오류 처리
		if (std::cin.fail())
		{
			system("cls");
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');

			continue;
		}

		// 종료 선택시 인스턴스 해제
		if (select == EXIT)
		{
			std::cout << std::endl;
			PrintExit();
			std::cout << std::endl;
			Release();
			system("pause");
			break;
		}

		// 분기문
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

// 출력
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

// 데이터 전체
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

// 데이터 없음
void StudentManager::PrintNoData()
{
	std::cout << "= 데이터 없음 =" << std::endl << std::endl;
}

// 타이틀 출력
void StudentManager::PrintTitle()
{
	std::cout << "< 학생 관리 프로그램 >" << std::endl << std::endl;
}

// 리스트 출력
void StudentManager::PrintList()
{
	std::cout << "번호" << '\t';
	std::cout << "이름" << '\t';
	std::cout << "국어" << '\t';
	std::cout << "영어" << '\t';
	std::cout << "수학" << '\t';
	std::cout << "총점" << '\t';
	std::cout << "평균" << '\t';
	std::cout << std::endl;
}

// 메뉴 출력
void StudentManager::PrintMenu()
{
	std::cout << "[1]샘플" << " ";
	std::cout << "[2]정렬" << " ";
	std::cout << "[3]검색" << " ";
	std::cout << "[4]추가" << " ";
	std::cout << "[5]삭제" << " ";
	std::cout << "[6]저장" << " ";
	std::cout << "[7]읽기" << " ";
	std::cout << "[0]종료" << " ";
	std::cout << std::endl << std::endl;

	std::cout << "메뉴 선택 >> ";
}

// 검색 출력
void StudentManager::PrintSearch()
{
	std::cout << "= 검색 완료 =" << std::endl << std::endl;
}

// 저장 완료
void StudentManager::PrintSave()
{
	std::cout << "= 저장 완료 =" << std::endl << std::endl;
}

// 종료 출력
void StudentManager::PrintExit()
{
	std::cout << "= 프로그램 종료 = " << std::endl;
}

// 샘플
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
			_students.push_back(new Student(_index, "샘플", rand() % 100 + 1, rand() % 100 + 1, rand() % 100 + 1));
			_index++;
		}
		else
		{
			_students.push_front(new Student(_index, "샘플", rand() % 100 + 1, rand() % 100 + 1, rand() % 100 + 1));
			_index++;
		}
	}

	system("cls");
}

// 정렬
void StudentManager::Sort()
{
	
}

// 검색
void StudentManager::Search()
{
	int _index;

	std::cout << "번호 선택 >> ";
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

// 추가
void StudentManager::Add()
{
	std::string _name;
	int _kor;
	int _eng;
	int _math;

	std::cout << "학생 이름 >> ";
	std::cin >> _name;
	_name = _name.substr(0, 6);

	std::cout << "국어 점수 >> ";
	std::cin >> _kor;

	if (_kor < 0 || _kor > 100)
	{
		_kor = 100;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}

	std::cout << "영어 점수 >> ";
	std::cin >> _eng;

	if (_eng < 0 || _eng > 100)
	{
		_eng = 100;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	
	std::cout << "수학 점수 >> ";
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

// 삭제
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

// 저장
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

		std::cout << "파일명 입력 >> ";
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

// 로드
void StudentManager::Load()
{
	std::ifstream fin;
	std::string filename;

	std::cout << "파일명 입력 >> ";
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
