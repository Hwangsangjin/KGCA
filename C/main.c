#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char str[80];

	printf("������ ���Ե� ���ڿ� �Է� : ");
	fgets(str, _countof(str), stdin);
	str[strlen(str) - 1] = '\0';
	printf("�Էµ� ���ڿ��� %s�Դϴ�.\n", str);

	return 0;
}