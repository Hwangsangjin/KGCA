#include <stdio.h>

// strcmp 함수와 같은 기능을 수행하는 함수
int Strcmp(char* pA, char* pB);

int main()
{
	char str1[80] = "KGCA";
	char str2[80] = "HSJ";

	printf("비교할 문자열 : %s, %s\n", str1, str2);
	printf("결과 : %d", Strcmp(str1, str2));

	return 0;
}

int Strcmp(char* pA, char* pB)	// 비교할 문자열의 포인터
{
	while ((*pA == *pB) && (*pA != '\0'))	// 두 문자가 같으나 널 문자가 아닌 경우
	{
		pA++;	// 다음 문자로 이동
		pB++;	// 다음 문자로 이동
	}

	// 반복문 이후 이 시점에서는 두 문자가 다르거나 둘 다 널 문자이다.

	if (*pA > *pB)		// 앞 문자의 아스키 코드 값이 크면 1 반환
	{
		return 1;
	}
	else if (*pA < *pB)	// 뒷 문자의 아스키 코드 값이 크면 -1 반환
	{
		return -1;
	}
	else                // 둘 다 널 문자이므로 같은 문자열
	{
		return 0;
	}
}