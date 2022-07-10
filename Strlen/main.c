#include <stdio.h>

// strlen 함수와 같은 기능을 수행하는 함수
int Strlen(char* pS);

int main()
{
	char str[80] = "KGCA";

	printf("문자열: %s\n", str);
	printf("문자수: %d\n", Strlen(str));

	return 0;
}

int Strlen(char* pS)	// pS는 배열명을 저장하고 첫 번째 배열 요소를 가리킨다.
{
	int count = 0;		// 문자의 수를 세기 위한 변수

	while (*pS != '\0')	// pS가 가리키는 문자가 널 문자가 아닌 동안
	{
		count++;		// 문자의 수 증가

		pS++;			// 포인터를 다음 문자의 위치로 이동
	}

	return count;		// 전체 문자의 수 반환
}