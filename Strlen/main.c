#include <stdio.h>

// strlen �Լ��� ���� ����� �����ϴ� �Լ�
int Strlen(char* pS);

int main()
{
	char str[80] = "KGCA";

	printf("���ڿ�: %s\n", str);
	printf("���ڼ�: %d\n", Strlen(str));

	return 0;
}

int Strlen(char* pS)	// pS�� �迭���� �����ϰ� ù ��° �迭 ��Ҹ� ����Ų��.
{
	int count = 0;		// ������ ���� ���� ���� ����

	while (*pS != '\0')	// pS�� ����Ű�� ���ڰ� �� ���ڰ� �ƴ� ����
	{
		count++;		// ������ �� ����

		pS++;			// �����͸� ���� ������ ��ġ�� �̵�
	}

	return count;		// ��ü ������ �� ��ȯ
}