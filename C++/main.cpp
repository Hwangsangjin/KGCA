#include <iostream>
using namespace std;

int main()
{
	int n;
	std::cout << "홀수 입력 : ";
	std::cin >> n;

	int arr[50][50] = { 0 };
	int x = 0;
	int y = (n - 1) / 2;
	int end = n * n;

	for (size_t i = 1; i <= end; i++)
	{
		// 1. 시작은 첫 행, 한 가운데 열에 1을 둔다.
		arr[x][y] = i;

		// 2. 행을 감소, 열을 증가하면서 순차적으로 수를 넣어간다.
		x--;
		y++;

		// 3. 행은 감소하므로 첫 행보다 작아지는 경우에는 마지막 행으로 넘어간다.
		if (x < 0)
		{
			x = n - 1;
		}

		// 4. 열은 증가하므로 마지막 열보다 커지는 경우에는 첫 열로 넘어간다.
		if (y > n - 1)
		{
			y = 0;
		}

		// 5. 넣은 수가 n의 배수이면 행만 증가한다. 열은 변화없음.
		if (i % n == 0)
		{
			x++;
		}
	}

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}
