#include <stdio.h>
#include <stdlib.h>

void InputArray(double* pA, int size);
double FindMax(double* pA, int size);

int main()
{
	double arr[5];
	double max;
	int size = _countof(arr);

	InputArray(arr, size);
	
	max = FindMax(arr, size);

	printf("%lf", max);

	return 0;
}

void InputArray(double* pA, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		pA[i] = i;
	}
}

double FindMax(double* pA, int size)
{
	double max = pA[0];
	
	for (size_t i = 0; i < size; i++)
	{
		if (pA[i] > max)
		{
			max = pA[i];
		}
	}

	return max;
}
