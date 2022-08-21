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
	// 기본 생성자
	Str()
		: _pszData(nullptr)
		, _nLength(0)
	{
	}

	// 변환 생성자
	explicit Str(const char* pszParam)
		: _pszData(nullptr)
		, _nLength(0)
	{
		SetString(pszParam);
	}

	// 복사 생성자
	Str(const Str& rhs)
		: _pszData(nullptr)
		, _nLength(0)
	{
		this->SetString(rhs.GetString());
	}

	// 이동 생성자
	Str(Str&& rhs)
		: _pszData(nullptr)
		, _nLength(0)
	{
		cout << "Str 이동 생성자 호출" << endl;

		// 얕은 복사를 수행해도 상관없다.
		// 어차피 원본이 곧 소멸되기 때문이다!
		_pszData = rhs._pszData;
		_nLength = rhs._nLength;

		// 원본 임시 객체의 멤버들은 초기화한다.
		// 절대로 해제하면 안 된다.
		rhs._pszData = nullptr;
		rhs._nLength = 0;
	}

	// 소멸자
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

	Str& operator=(const Str& rhs)
	{
		// 자기 자신에 대한 대입이면 아무것도 하지 않는다.
		if (this != &rhs)
		{
			this->SetString(rhs.GetString());
		}

		return *this;
	}

	operator char* () const
	{
		return _pszData;
	}
};

Str TestStr()
{
	Str str("TestStr() return");
	cout << str << endl;
	return str;
}

class Data
{
private:
	int _nData = 0;

public:
	Data() { cout << "Data()" << endl; }
	~Data() { cout << "~Data()" << endl; }

	Data(const Data& rhs)
		: _nData(rhs._nData)
	{
		cout << "Data(const Data&): " << endl;
	}

	// 이동 생성자
	Data(Data&& rhs) noexcept
		: _nData(rhs._nData)
	{
		cout << "Data(Data&&)" << endl;
	}

	Data& operator=(const Data& rhs) = default;

	int GetData() const { return _nData; }
	void SetData(int nParam) { _nData = nParam; }
};

Data TestData(int nParam)
{
	cout << "TestData(): Begin" << endl;

	Data a;
	a.SetData(nParam);

	cout << "TestData(): End" << endl;

	return a;
}


int main()
{
	// 이름 없는 임시 객체가 만들어진다.
	TestStr();

    return 0;
}