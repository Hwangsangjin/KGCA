#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char str[80];

	printf("공백이 포함된 문자열 입력 : ");
	fgets(str, _countof(str), stdin);
	str[strlen(str) - 1] = '\0';
	printf("입력된 문자열은 %s입니다.\n", str);

	return 0;
}