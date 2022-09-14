#include <iostream>
using namespace std;

class Str
{
private:
	// 문자열을 저장하기 위해 동적 할당한 메모리를 가리키는 포인터
	char* _str;

	// 저장된 문자열의 길이
	int _length;

public:
	// 기본 생성자
	Str()
		: _str(nullptr)
		, _length(0)
	{
	}

	// 변환 생성자
	explicit Str(const char* str)
		: _str(nullptr)
		, _length(0)
	{
		SetString(str);
	}

	// 복사 생성자
	Str(const Str& rhs)
		: _str(nullptr)
		, _length(0)
	{
		this->SetString(rhs.GetString());
	}

	// 이동 생성자
	Str(Str&& rhs)
		: _str(nullptr)
		, _length(0)
	{
		cout << "Str 이동 생성자 호출" << endl;

		// 얕은 복사를 수행해도 상관없다.
		// 어차피 원본이 곧 소멸되기 때문이다!
		_str = rhs._str;
		_length = rhs._length;

		// 원본 임시 객체의 멤버들은 초기화한다.
		// 절대로 해제하면 안 된다.
		rhs._str = nullptr;
		rhs._length = 0;
	}

	// 소멸자
	~Str()
	{
		// 객체가 소멸하기 전에 메모리를 해제한다.
		Release();
	}

	int SetString(const char* str)
	{
		// 새로운 문자열 할당에 앞서 기존 정보를 해제한다.
		Release();

		// nullptr을 인수로 함수를 호출했다는 것은 메모리를 해제하고
		// nullptr로 초기화하는 것으로 볼 수 있다.
		if (str == nullptr)
		{
			return 0;
		}

		// 길이가 0인 문자열도 초기화로 인식하고 처리한다.
		int length = strlen(str);

		if (length == 0)
		{
			return 0;
		}

		// 문자열의 끝인 NULL 문자를 고려해 메모리를 할당한다.
		_str = new char[length + 1];

		// 새로 할당한 메모리에 문자열을 저장한다.
		strcpy_s(_str, sizeof(char) * (length + 1), str);
		_length = length;

		// 문자열의 길이를 반환한다.
		return length;
	}

	// 멤버 읽기만 수행하므로 메서드를 상수화한다.
	const char* GetString() const
	{
		return _str;
	}

	void Release()
	{
		// 이 함수가 여러 번 호출될 경우를 고려해 주요 멤버를 초기화한다.
		if (_str != nullptr)
		{
			delete[] _str;
		}

		_str = nullptr;
		_length = 0;
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
		return _str;
	}
};

Str TestStr()
{
	Str str("TestStr() return");
	cout << str << endl;
	return str;
}

// 제작자 - 초기 개발자
class Data
{
private:	// 누구도 접근 불가능
	int _data = 0;

protected:	// 파생 클래스만 접근 가능
	void PrintData() { cout << "Data::PrintData()" << endl; }

public:		// 누구나 접근 가능
	Data() { cout << "Data()" << endl; }

	int GetData() const { return _data; }
	void SetData(int data) { _data = data; }
};

// 제작자 - 후기 개발자
class DataEx : public Data
{
public:
	DataEx() { cout << "DataEx()" << endl; }

	void TestFunc()
	{
		// 기본 형식 멤버에 접근
		PrintData();
		SetData(5);
		cout << Data::GetData() << endl;
	}
};

// 사용자
int main()
{
	DataEx data;

	// 기본 클래스(Data) 멤버에 접근
	data.SetData(10);
	cout << data.GetData() << endl;

	// 파생 클래스(DataEx) 멤버에 접근
	data.TestFunc();

    return 0;
}