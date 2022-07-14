#include <stdio.h>

// strcat 함수와 같은 기능을 수행하는 함수
char* Strcat(char* pD, char* pS);

int main()
{
	char str[80] = "KGCA";

	printf("처음 문자열 : %s\n", str);

	Strcat(str, " GAME");	// 문자열 붙여넣기

	printf("붙여넣기 후 문자열 : %s\n", Strcat(str, " ACADEMY"));	// 반환값으로 출력

	return 0;
}

char* Strcat(char* pD, char* pS)	// 복사 받을 곳(pD)과 복사할 곳(pS)의 포인터
{
	char* pO = pD;		// 배열의 처음 위치 보관

	while (*pD != '\0')	// pD를 널 문자의 위치로 이동
	{
		pD++;
	}

	while (*pS != '\0')	// pS가 가리키는 문자가 널 문자가 아닌 동안
	{
		*pD = *pS;		// pS가 가리키는 문자를 pD가 가리키는 위치에 대입

		pD++;			// 복사 받을 다음 위치로 포인터 증가

		pS++;			// 복사할 다음 문자의 위치로 포인터 증가
	}

	*pD = '\0';			// 복사가 모두 끝난 후 복사 받을 곳에 널 문자 저장

	return pO;			// 붙여넣은 배열의 시작 위치 반환
}