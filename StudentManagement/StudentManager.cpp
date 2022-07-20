#include "StudentManager.h"

// �л� ���� �Ŵ��� ����
void StudentManager::run()
{
	while (true)
	{
		cout << "[1] �л� ���� ���" << endl;
		cout << "[2] �л� ���� ����" << endl;
		cout << "[3] �л� ���� �˻�" << endl;
		cout << "[4] �л� ���� ���" << endl;
		cout << "[5] ���α׷� ����" << endl;
		cout << endl;
		cout << "�ɼ� ���� >> ";

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

// �л� ���� �߰�
void StudentManager::add()
{
	{
		int number;
		char name[10];
		int kor;
		int eng;
		int math;

		cout << "�л� ��ȣ : ";
		cin >> number;
		cout << "�л� �̸� : ";
		cin >> name;
		cout << "���� ���� : ";
		cin >> kor;
		cout << "���� ���� : ";
		cin >> eng;
		cout << "���� ���� : ";
		cin >> math;

		students.push_back(new Student(number, name, kor, eng, math));
	}
}

// �л� ���� ����
void StudentManager::remove()
{
	students.pop_back();
}

// �л� ���� �˻�
void StudentManager::search()
{
}

// �л� ���� ���
void StudentManager::print()
{
	cout << "��ȣ" << " " << "�̸�" << " " << "����" << " " << "����" << " " << "����" << " " << "����" << " " << "���" << endl;

	for (auto& i : students)
	{
		cout << i->get_number() << " " << i->get_name() << " " << i->get_kor() << " " << i->get_eng() << " " << i->get_math() << " " << i->get_total() << " " << i->get_avg() << endl;
	}
}
