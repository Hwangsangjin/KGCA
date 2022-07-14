#include <stdio.h>

void Input(int* pA, int* pB);
void Swap(int* pA, int* pB);
void Print(int a, int b);

int main()
{
	int a, b;		// ������ �Է� ���� ����

	Input(&a, &b);	// ������ ���� �� �Է�

	Swap(&a, &b);	// ���� ��ȯ

	Print(a, b);	// ��ȯ�� �� ���

	return 0;
}

void Input(int* pA, int* pB)
{
	printf("�� ���� �Է� : ");
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
	printf("�� ���� ��� : %d %d\n", a, b);
}