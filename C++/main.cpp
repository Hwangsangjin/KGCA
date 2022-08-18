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

	// 복사 생성자
	Str(const Str& rhs)
		: _pszData(nullptr)
		, _nLength(0)
	{
		this->SetString(rhs.GetString());
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

	// 멤버 읽기만 수행하므로 메서드를 상수화한다.
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

	Str& operator=(const Str& rhs)
	{
		// 자기 자신에 대한 대입이면 아무것도 하지 않는다.
		if (this != &rhs)
		{
			this->SetString(rhs.GetString());
		}

		return *this;
	}
};

class Data
{
private:
	int _nData = 0;

public:
	// 매개변수가 하나뿐인 생성자는 형변환이 가능하다.
	Data(int nParam)
		: _nData(nParam)
	{
		cout << "Data(int)" << endl;
	}

	Data(const Data& rhs)
		: _nData(rhs._nData)
	{
		cout << "Data(const Data&)" << endl;
	}

	int GetData()
	{
		return _nData;
	}

	void SetData(int nParam)
	{
		_nData = nParam;
	}
};

// 매개변수가 클래스 형식이며 변환 생성이 가능하다.
void TestFunc(Data param)
{
	cout << "TestFunc(): " << param.GetData() << endl;
}

int main()
{
	// int 자료형에서 Data 형식으로 변환될 수 있다.
	TestFunc(5);

    return 0;
}