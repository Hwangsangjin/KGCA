#include <stdio.h>

int main()
{
	FILE* fp;
	char str[20] = "empty";
	int ch;

	fp = fopen("a.txt", "r");
	ch = fgetc(fp);
	
	while (fgetc(fp) != EOF);

	fgets(str, sizeof(str), fp);

	printf("%s", str);

	fclose(fp);

	return 0;
}
