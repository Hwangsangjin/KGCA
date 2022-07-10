#include <stdio.h>

void Gets(char* pStr);

int main()
{
	char str[80];		// 문자열을 저장할 배열

	Gets(str);			// Gets 함수 호출

	printf("%s", str);	// 문자열 출력

	return 0;
}

void Gets(char* pStr)					// pStr은 첫 번째 배열 요소를 가리킨다.
{
	char ch;							// 입력한 문자를 받아둘 임시 변수

	while ((ch = getchar()) != '\n')	// 입력한 문자가 개행 문자가 아닌 동안 반복
	{
		*pStr = ch;						// 배열에 저장하고

		pStr++;							// 다음 배열 요소로 이동
	}

	*pStr = '\0';						// 마지막 요소에 널 문자를 저장한다.
}