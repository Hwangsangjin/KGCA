#include <stdio.h>

void Gets(char* pStr);

int main()
{
	char str[80];		// ���ڿ��� ������ �迭

	Gets(str);			// Gets �Լ� ȣ��

	printf("%s", str);	// ���ڿ� ���

	return 0;
}

void Gets(char* pStr)					// pStr�� ù ��° �迭 ��Ҹ� ����Ų��.
{
	char ch;							// �Է��� ���ڸ� �޾Ƶ� �ӽ� ����

	while ((ch = getchar()) != '\n')	// �Է��� ���ڰ� ���� ���ڰ� �ƴ� ���� �ݺ�
	{
		*pStr = ch;						// �迭�� �����ϰ�

		pStr++;							// ���� �迭 ��ҷ� �̵�
	}

	*pStr = '\0';						// ������ ��ҿ� �� ���ڸ� �����Ѵ�.
}