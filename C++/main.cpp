#include <iostream>
using namespace std;

int main()
{
	char str[80];
	char ch;
	int i = 0;

	// get() 함수를 사용한 한 줄 출력
	cout << "문장 입력 : ";

	ch = cin.get();		// 공백 문자를 포함한 모든 문자의 입력

	while (ch != '\n')	// 새줄 문자가 아닌 동안 반복
	{
		str[i] = ch;	// 입력한 문자를 str 배열에 저장
		i++;			// 다음 문자 입력
	}
	
	str[i] = '\0';		// 문자열을 완성하기 위해 마지막에 널문자 저장

	cout << "입력된 문장은 : " << str << endl;

	// getline() 함수를 사용한 한 줄 입력

	cout << "새로운 문장 입력 : ";
	cin.getline(str, _countof(str));	// 한 줄의 데이터 입력
	cout << "새로 입력된 문장 : " << str << endl;

	return 0;
}