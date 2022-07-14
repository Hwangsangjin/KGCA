#include <iostream>
using namespace std;

// ���� Ž�� �˰����� ����� �Լ�
int BinarySearch(int arr[], int length, int target);

int main()
{
	int arr[] = { 1, 3, 5, 7, 9 };
	int idx;

	idx = BinarySearch(arr, _countof(arr), 7);

	if (idx == -1)
	{
		cout << "Ž�� ����" << endl;
	}
	else
	{
		cout << "Ÿ�� ���� �ε��� : " << idx << endl;
	}

	idx = BinarySearch(arr, _countof(arr), 4);

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

int BinarySearch(int arr[], int length, int target)
{
	int first = 0;			// Ž�� ����� ���� �ε��� ��
	int last = length - 1;	// Ž�� ����� ������ �ε��� ��
	int mid;

	while (first <= last)
	{
		mid = (first + last) / 2;	// Ž�� ����� �߾��� ã�´�.

		if (target == arr[mid])		// �߾ӿ� ����� ���� Ÿ���̶��
		{
			return mid;				// Ž�� �Ϸ�
		}
		else                        // Ÿ���� �ƴ϶�� Ž�� ����� ������ ���δ�.
		{
			if (target < arr[mid])	// -1 Ȥ�� +1�� �߰����� ������ first <= mid <= last�� �׻� �����Ǿ�, Ž�� ����� �������� �ʴ� ��� first�� last�� ���� ������ �߻����� �ʴ´�.
			{
				last = mid - 1; 
			}
			else
			{
				first = mid + 1;
			}
		}
	}

	return -1;	// ã�� ������ �� ��ȯ�Ǵ� ��
}
