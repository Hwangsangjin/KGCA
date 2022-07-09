#include <stdio.h>
#include <stdlib.h>

int main()
{
	char str[80];

	printf("공백이 포함된 문자열 입력 : ");
	fgets(str, _countof(str), stdin);

	printf("입력된 문자열은 %s입니다.\n", str);

	return 0;
}