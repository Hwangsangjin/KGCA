#include <stdio.h>

// strcmp �Լ��� ���� ����� �����ϴ� �Լ�
int Strcmp(char* pA, char* pB);

int main()
{
	char str1[80] = "KGCA";
	char str2[80] = "HSJ";

	printf("���� ���ڿ� : %s, %s\n", str1, str2);
	printf("��� : %d", Strcmp(str1, str2));

	return 0;
}

int Strcmp(char* pA, char* pB)	// ���� ���ڿ��� ������
{
	while ((*pA == *pB) && (*pA != '\0'))	// �� ���ڰ� ������ �� ���ڰ� �ƴ� ���
	{
		pA++;	// ���� ���ڷ� �̵�
		pB++;	// ���� ���ڷ� �̵�
	}

	// �ݺ��� ���� �� ���������� �� ���ڰ� �ٸ��ų� �� �� �� �����̴�.

	if (*pA > *pB)		// �� ������ �ƽ�Ű �ڵ� ���� ũ�� 1 ��ȯ
	{
		return 1;
	}
	else if (*pA < *pB)	// �� ������ �ƽ�Ű �ڵ� ���� ũ�� -1 ��ȯ
	{
		return -1;
	}
	else                // �� �� �� �����̹Ƿ� ���� ���ڿ�
	{
		return 0;
	}
}