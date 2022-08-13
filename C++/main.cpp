#include <iostream>
using namespace std;

class Str
{
private:
	// 문자열을 저장하기 위해 동적 할당한 메모리를 가리키는 포인터
	char* _pszData;

	// 저장된 문자열의 길이
	int _nLength;

public:
	Str()
		: _pszData(nullptr)
		, _nLength(0)
	{
	}

	~Str()
	{
		// 객체가 소멸하기 전에 메모리를 해제한다.
		Release();
	}

	int SetString(const char* pszParam)
	{
		// 새로운 문자열 할당에 앞서 기존 정보를 해제한다.
		Release();

		// nullptr을 인수로 함수를 호출했다는 것은 메모리를 해제하고
		// nullptr로 초기화하는 것으로 볼 수 있다.
		if (pszParam == nullptr)
		{
			return 0;
		}

		// 길이가 0인 문자열도 초기화로 인식하고 처리한다.
		int nLength = strlen(pszParam);

		if (nLength == 0)
		{
			return 0;
		}

		// 문자열의 끝인 NULL 문자를 고려해 메모리를 할당한다.
		_pszData = new char[nLength + 1];

		// 새로 할당한 메모리에 문자열을 저장한다.
		strcpy_s(_pszData, sizeof(char) * (nLength + 1), pszParam);
		_nLength = nLength;

		// 문자열의 길이를 반환한다.
		return nLength;
	}

	// 멤버 읽기만 수행하므로 메서드를 상화한다.
	const char* GetString() const
	{
		return _pszData;
	}

	void Release()
	{
		// 이 함수가 여러 번 호출될 경우를 고려해 주요 멤버를 초기화한다.
		if (_pszData != nullptr)
		{
			delete[] _pszData;
		}

		_pszData = nullptr;
		_nLength = 0;
	}

	void TestFunc(const Str& param)
	{
		cout << param.GetString() << endl;
	}
};

class Test
{
private:
	int _data;

	// 정적 멤버 변수 선언(정의는 아니다!)
	static int _count;

public:
	Test(int param) : _data(param) { _count++; }
	~Test() {}

	int GetData() { return _data; }
	void ResetCount() { _count = 0; }

	// 정적 메서드 선언 및 정의
	static int GetCount()
	{
		return _count;
	}
};

class Data
{
private:
	int _data;

public:
	Data()
		: _data(0)
	{
		cout << "Data()" << endl;
	}

	Data(int param)
		: _data(param)
	{
		cout << "Data(int)" << endl;
	}

	// 복사 생성자를 아예 삭제함으로써 복사 생성을 막는다.
	Data(const Data& rhs) = delete;

	// 읽기 전용인 상수형 메서드
	int GetData() const { return _data; }

	// 멤버 변수에 쓰기를 시도하는 메서드
	void SetData(int param) { _data = param; }

	// 실수로 double 자료형 실인수가 넘어오는 경우를 차단한다.
	void SetData(double param) = delete;
};

// 매개변수가 Data 클래스 '참조' 형식이므로 객체가 생성되지 않는다!
void TestFunc(Data& param)
{
	cout << "TestFunc()" << endl;

	// 피호출자 함수에서 매개변수 인스턴스의 값을 변경한다.
	param.SetData(20);
}

int main()
{
	cout << "Begin" << endl;
	Data a(10);
	TestFunc(a);

	// 함수 호출 후 a의 값을 출력한다.
	cout << "a: " << a.GetData() << endl;

	cout << "End" << endl;

    return 0;
}