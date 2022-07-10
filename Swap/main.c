#include <stdio.h>

void Input(int* pA, int* pB);
void Swap(int* pA, int* pB);
void Print(int a, int b);

int main()
{
	int a, b;		// 정수를 입력 받을 변수

	Input(&a, &b);	// 변수에 정수 값 입력

	Swap(&a, &b);	// 변수 교환

	Print(a, b);	// 교환된 값 출력

	return 0;
}

void Input(int* pA, int* pB)
{
	printf("두 정수 입력 : ");
	scanf_s("%d%d", pA, pB);
}

void Swap(int* pA, int* pB)
{
	int temp;

	temp = *pA;
	*pA = *pB;
	*pB = temp;
}

void Print(int a, int b)
{
	printf("두 정수 출력 : %d %d\n", a, b);
}