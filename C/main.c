#include <stdio.h>

int main()
{
	char str[100] = { 0 };
	int count = 0;

	printf("문장 입력 : ");
	gets(str);

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (isupper(str[i]))
		{
			str[i] = tolower(str[i]);
			count++;
		}
	}

	printf("바뀐 문장 : ");
	puts(str);
	printf("바뀐 문자 수 : %d\n", count);

	return 0;
}