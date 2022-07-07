#include <stdio.h>

// 다이아몬드
void Diamond();

int main()
{
	Diamond();

	return 0;
}

// 다이아몬드 출력
void Diamond()
{
	// 필요한 변수
	int i, j;

	// 0~2행 출력
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 2 - i; j++)
		{
			printf(" ");
		}

		for (j = 0; j < 1 + i * 2; j++)
		{
			printf("*");
		}

		printf("\n");
	}

	// 3~4행 출력
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 1 + i; j++)
		{
			printf(" ");
		}

		for (j = 0; j < 3 - 2 * i; j++)
		{
			printf("*");
		}

		printf("\n");
	}
}