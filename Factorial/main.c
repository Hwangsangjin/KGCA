#include <stdio.h>

int Factorial(int n);

int main()
{
	printf("%d", Factorial(5));

	return 0;
}

int Factorial(int n)
{
	int result = 0;

	if (n == 1)
	{
		return 1;
	}
	else
	{
		result = n * Factorial(n - 1);
	}
}