#include <stdio.h>

// strcpy �Լ��� ���� ����� �����ϴ� �Լ�
char* Strcpy(char* pD, char* pS);

int main()
{
	char str[80] = "KGCA";

	printf("�ٲٱ� �� ���ڿ� : %s\n", str);

	Strcpy(str, "GAME");	// ���ڿ� ����

	printf("�ٲ� �� ���ڿ� : %s\n", str);

	printf("�ٸ� ���ڿ� ���� : %s\n", Strcpy(str, "ACADEMY"));	// ��ȯ������ ���

	return 0;
}

char* Strcpy(char* pD, char* pS)	// ���� ���� ��(pD)�� ������ ��(pS)�� ������
{
	char* pO = pD;		// pD ���� ���߿� ��ȯ�ϱ� ���� ����

	while (*pS != '\0')	// pS�� ����Ű�� ���ڰ� �� ���ڰ� �ƴ� ����
	{
		*pD = *pS;		// pS�� ����Ű�� ���ڸ� pD�� ����Ű�� ��ġ�� ����

		pD++;			// ���� ���� ���� ��ġ�� ������ ����

		pS++;			// ������ ���� ������ ��ġ�� ������ ����
	}

	*pD = '\0';			// ���簡 ��� ���� �� ���� ���� ���� �� ���� ����

	return pO;			// ���簡 ���� ���� ������ ���� �ּ� ��ȯ
}