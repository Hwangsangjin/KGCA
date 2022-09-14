#include <stdio.h>

int main()
{
	// ÆÄÀÏ
	FILE* fp;
	char str[20] = "empty";
	int ch;

	fp = fopen("test.txt", "r");
	ch = fgetc(fp);
	
	while (fgetc(fp) != EOF);

	fgets(str, sizeof(str), fp);

	printf("%s\n", str);

	fclose(fp);

	return 0;
}
