#include <iostream>
using namespace std;

// 순차 탐색 알고리즘이 적용된 함수
int LinearSearch(int arr[], int length, int target);

int main()
{
	int arr[] = { 3, 5, 2, 4, 9 };
	int idx = LinearSearch(arr, _countof(arr), 4);

	if (idx == -1)
	{
		cout << "탐색 실패" << endl;
	}
	else
	{
		cout << "타겟 저장 인덱스 : " << idx << endl;
	}

	idx = LinearSearch(arr, _countof(arr), 7);

	if (idx == -1)
	{
		cout << "탐색 실패" << endl;
	}
	else
	{
		cout << "타겟 저장 인덱스 : " << idx << endl;
	}

	return 0;
}

int LinearSearch(int arr[], int length, int target)
{
	for (int i = 0; i < length; i++)
	{
		if (arr[i] == target)
		{
			return i;	// 찾은 대상의 인덱스 값 반환
		}
	}

	return -1;	// 찾지 못했음을 의미하는 값 반환
}
