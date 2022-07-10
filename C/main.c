#include <stdio.h>
#include <stdlib.h>

int main()
{
	char mark[5][5] = { 0 };

	for (size_t i = 0; i < _countof(mark); i++)
	{
		for (size_t j = 0; j < _countof(mark); j++)
		{
			if ((i == j) || (i + j == 4))
			{
				mark[i][j] = 'X';
				printf("%c", mark[i][j]);
			}
			else
			{
				mark[i][j] = 'O';
				printf("%c", mark[i][j]);
			}
		}
		printf("\n");
	}

	return 0;
}