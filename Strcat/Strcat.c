#include <stdio.h>

// strcat �Լ��� ���� ����� �����ϴ� �Լ�
char* Strcat(char* pD, char* pS);

int main()
{
	char str[80] = "KGCA";

	printf("ó�� ���ڿ� : %s\n", str);

	Strcat(str, " GAME");	// ���ڿ� �ٿ��ֱ�

	printf("�ٿ��ֱ� �� ���ڿ� : %s\n", Strcat(str, " ACADEMY"));	// ��ȯ������ ���

	return 0;
}

char* Strcat(char* pD, char* pS)	// ���� ���� ��(pD)�� ������ ��(pS)�� ������
{
	char* pO = pD;		// �迭�� ó�� ��ġ ����

	while (*pD != '\0')	// pD�� �� ������ ��ġ�� �̵�
	{
		pD++;
	}

	while (*pS != '\0')	// pS�� ����Ű�� ���ڰ� �� ���ڰ� �ƴ� ����
	{
		*pD = *pS;		// pS�� ����Ű�� ���ڸ� pD�� ����Ű�� ��ġ�� ����

		pD++;			// ���� ���� ���� ��ġ�� ������ ����

		pS++;			// ������ ���� ������ ��ġ�� ������ ����
	}

	*pD = '\0';			// ���簡 ��� ���� �� ���� ���� ���� �� ���� ����

	return pO;			// �ٿ����� �迭�� ���� ��ġ ��ȯ
}