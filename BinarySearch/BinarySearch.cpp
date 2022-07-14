#include <iostream>
using namespace std;

// 이진 탐색 알고리즘이 적용된 함수
int BinarySearch(int arr[], int length, int target);

int main()
{
	int arr[] = { 1, 3, 5, 7, 9 };
	int idx;

	idx = BinarySearch(arr, _countof(arr), 7);

	if (idx == -1)
	{
		cout << "탐색 실패" << endl;
	}
	else
	{
		cout << "타겟 저장 인덱스 : " << idx << endl;
	}

	idx = BinarySearch(arr, _countof(arr), 4);

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

int BinarySearch(int arr[], int length, int target)
{
	int first = 0;			// 탐색 대상의 시작 인덱스 값
	int last = length - 1;	// 탐색 대상의 마지막 인덱스 값
	int mid;

	while (first <= last)
	{
		mid = (first + last) / 2;	// 탐색 대상의 중앙을 찾는다.

		if (target == arr[mid])		// 중앙에 저장된 값이 타겟이라면
		{
			return mid;				// 탐색 완료
		}
		else                        // 타겟이 아니라면 탐색 대상을 반으로 줄인다.
		{
			if (target < arr[mid])	// -1 혹은 +1을 추가하지 않으면 first <= mid <= last가 항상 성립되어, 탐색 대상이 존재하지 않는 경우 first와 last의 역전 현상이 발생하지 않는다.
			{
				last = mid - 1; 
			}
			else
			{
				first = mid + 1;
			}
		}
	}

	return -1;	// 찾지 못했을 때 반환되는 값
}
