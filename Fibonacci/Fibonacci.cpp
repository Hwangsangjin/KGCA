#include <iostream>
using namespace std;

// 피보나치 수
int Fibonacci(int n);

int main()
{
	int num;
	cout << "정수 입력 : ";
	cin >> num;

	cout << "피보나치 수 : ";

	for (size_t i = 1; i < num; i++)
	{
		
		cout << Fibonacci(i) <<" ";
	}

	return 0;
}

int Fibonacci(int n)
{
	if (n == 1 || n == 2)
	{
		return 1;
	}
	else
	{
		return Fibonacci(n - 1) + Fibonacci(n - 2);
	}

	return 0;
}
