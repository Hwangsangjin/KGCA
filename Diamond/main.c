#include <stdio.h>

// ���̾Ƹ��
void Diamond();

int main()
{
	Diamond();

	return 0;
}

// ���̾Ƹ�� ���
void Diamond()
{
	// �ʿ��� ����
	int i, j;

	// 0~2�� ���
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

	// 3~4�� ���
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