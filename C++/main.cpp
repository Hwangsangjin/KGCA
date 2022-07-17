#include <iostream>
using namespace std;

int main()
{
	int n;
	std::cout << "Ȧ�� �Է� : ";
	std::cin >> n;

	int arr[50][50] = { 0 };
	int x = 0;
	int y = (n - 1) / 2;
	int end = n * n;

	for (size_t i = 1; i <= end; i++)
	{
		// 1. ������ ù ��, �� ��� ���� 1�� �д�.
		arr[x][y] = i;

		// 2. ���� ����, ���� �����ϸ鼭 ���������� ���� �־��.
		x--;
		y++;

		// 3. ���� �����ϹǷ� ù �ຸ�� �۾����� ��쿡�� ������ ������ �Ѿ��.
		if (x < 0)
		{
			x = n - 1;
		}

		// 4. ���� �����ϹǷ� ������ ������ Ŀ���� ��쿡�� ù ���� �Ѿ��.
		if (y > n - 1)
		{
			y = 0;
		}

		// 5. ���� ���� n�� ����̸� �ุ �����Ѵ�. ���� ��ȭ����.
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
