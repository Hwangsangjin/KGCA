#include <stdio.h>

int main()
{
	char str[100] = { 0 };
	int count = 0;

	printf("���� �Է� : ");
	gets(str);

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (isupper(str[i]))
		{
			str[i] = tolower(str[i]);
			count++;
		}
	}

	printf("�ٲ� ���� : ");
	puts(str);
	printf("�ٲ� ���� �� : %d\n", count);

	return 0;
}