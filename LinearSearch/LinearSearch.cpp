#include <iostream>
using namespace std;

// ���� Ž�� �˰����� ����� �Լ�
int LinearSearch(int arr[], int length, int target);

int main()
{
	int arr[] = { 3, 5, 2, 4, 9 };
	int idx = LinearSearch(arr, _countof(arr), 4);

	if (idx == -1)
	{
		cout << "Ž�� ����" << endl;
	}
	else
	{
		cout << "Ÿ�� ���� �ε��� : " << idx << endl;
	}

	idx = LinearSearch(arr, _countof(arr), 7);

	if (idx == -1)
	{
		cout << "Ž�� ����" << endl;
	}
	else
	{
		cout << "Ÿ�� ���� �ε��� : " << idx << endl;
	}

	return 0;
}

int LinearSearch(int arr[], int length, int target)
{
	for (int i = 0; i < length; i++)
	{
		if (arr[i] == target)
		{
			return i;	// ã�� ����� �ε��� �� ��ȯ
		}
	}

	return -1;	// ã�� �������� �ǹ��ϴ� �� ��ȯ
}
