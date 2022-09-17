#include <iostream>

using namespace std;

class Str
{
private:
	// 문자열을 저장하기 위해 동적 할당한 메모리를 가리키는 포인터
	char* _data;

	// 저장된 문자열의 길이
	int _length;

public:
	// 기본 생성자
	Str()
		: _data(nullptr)
		, _length(0)
	{
	}

	// 변환 생성자
	explicit Str(const char* str)
		: _data(nullptr)
		, _length(0)
	{
		SetString(str);
	}

	// 복사 생성자
	Str(const Str& rhs)
		: _data(nullptr)
		, _length(0)
	{
		this->SetString(rhs.GetString());
	}

	// 이동 생성자
	Str(Str&& rhs)
		: _data(nullptr)
		, _length(0)
	{
		cout << "Str 이동 생성자 호출" << endl;

		// 얕은 복사를 수행해도 상관없다.
		// 어차피 원본이 곧 소멸되기 때문이다!
		_data = rhs._data;
		_length = rhs._length;

		// 원본 임시 객체의 멤버들은 초기화한다.
		// 절대로 해제하면 안 된다.
		rhs._data = nullptr;
		rhs._length = 0;
	}

	// 소멸자
	~Str()
	{
		// 객체가 소멸하기 전에 메모리를 해제한다.
		Release();
	}

	virtual void OnSetString(const char* data, int length)
	{
		// 아무런 코드도 추가하지 않는다.
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
		_data = new char[length + 1];

		// 새로 할당한 메모리에 문자열을 저장한다.
		strcpy_s(_data, sizeof(char) * (length + 1), str);
		_length = length;

		// 미래를 호출한다!
		OnSetString(_data, _length);

		// 문자열의 길이를 반환한다.
		return length;
	}

	// 멤버 읽기만 수행하므로 메서드를 상수화한다.
	const char* GetString() const
	{
		return _data;
	}

	void Release()
	{
		// 이 함수가 여러 번 호출될 경우를 고려해 주요 멤버를 초기화한다.
		if (_data != nullptr)
		{
			delete[] _data;
		}

		_data = nullptr;
		_length = 0;
	}

	int GetLength() const
	{
		return _length;
	}

	int Append(const char* str)
	{
		//매개변수 유효성 검사
		if (str == nullptr)
		{
			return 0;
		}

		int length = strlen(str);
		if (length == 0)
		{
			return 0;
		}

		// 세트된 문자열이 없다면 새로 문자열을 할당한 것과 동일하게 처리.
		if (str == nullptr)
		{
			SetString(str);
			return _length;
		}

		// 현재 문자열의 길이 백업.
		int currentLength = _length;

		// 두 문자열을 합쳐서 저장할 수 있는 메모리를 새로 할당.
		char* result = new char[currentLength + length + 1];

		// 문자열 조합
		strcpy_s(result,
			sizeof(char) * (currentLength + 1), _data);
		strcpy_s(result + (sizeof(char) * currentLength),
			sizeof(char) * (length + 1), str);

		// 기존 문자열 삭제 및 멤버 정보 갱신
		Release();

		_data = result;
		_length = currentLength + length;

		return _length;
	}

	Str operator+(const Str& rhs)
	{
		Str result(_data);
		result.Append(rhs.GetString());

		return result;
	}

	Str& operator+=(const Str& rhs)
	{
		Append(rhs.GetString());

		return *this;
	}

	char& operator[](int index)
	{
		return _data[index];
	}

	char operator[](int index) const
	{
		return _data[index];
	}

	int operator==(const Str& rhs)
	{
		if (_data != nullptr && rhs._data != nullptr)
		{
			if (strcmp(_data, rhs._data) == 0)
			{
				return 1;
			}
		}

		return 0;
	}

	int operator!=(const Str& rhs)
	{
		if (_data != nullptr && rhs._data != nullptr)
		{
			if (strcmp(_data, rhs._data) == 0)
			{
				return 0;
			}
		}
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
		return _data;
	}
};

class StrEx : public Str
{
public:
	StrEx() = default;
	StrEx(const char* data)
		: Str(data)
	{
	}
	~StrEx() = default;

	int Find(const char* param)
	{
		if (param == nullptr || GetString() == nullptr)
		{
			return -1;
		}

		const char* result = strstr(GetString(), param);
		if (result != nullptr)
		{
			return result - GetString();
		}

		return -1;
	}

	void OnSetString(char* data, int length)
	{
		if (strcmp(data, "멍멍이아들") == 0)
		{
			strcpy_s(data,
				sizeof(char) * (length + 1), "*착한사람*");
		}
	}

	int SetString(const char* param)
	{
		int result;

		if (strcmp(param, "멍멍이아들") == 0)
		{
			result = Str::SetString("착한사람");
		}
		else
		{
			result = Str::SetString(param);
		}

		return result;
	}
};

// 제작자 코드
class Data
{
private:
	char* _pszData;

public:
	Data()
	{
		cout << "Data()" << endl;
		_pszData = new char[32];
	}

	virtual ~Data()
	{
		cout << "~Data()" << endl;
		delete _pszData;
	}

	virtual void TestFunc1() {}
	virtual void TestFunc2() {}

	// 가상 함수로 선언 및 정의했다.
	virtual void PrintData()
	{
		cout << "Data: " << _pszData << endl;
	}

	void TestFunc()
	{
		cout << "-TestFunc()-" << endl;

		// 실 형식의 함수가 호출된디.
		PrintData();
		cout << "-----" << endl;
	}
};

class DataEx : public Data
{
private:
	int* _pnData;
public:
	DataEx()
	{
		cout << "~DataEx()" << endl;
		_pnData = new int;
	}

	~DataEx()
	{
		cout << "~DataEx()" << endl;
		delete _pnData;
	}

	virtual void TestFunc1() {}
	virtual void TestFunc2()
	{
		cout << "TestFunc2()" << endl;
	}
};

class DataA
{
protected:
	char* _data;

public:
	DataA()
	{
		cout << "DataA()" << endl;
		_data = new char[32];

	}
	~DataA()
	{
		cout << "~DataA()" << endl;
		delete _data;
	}
};

class DataB : public DataA
{
public:
	DataB()
	{
		cout << "DataB()" << endl;
	}
	~DataB()
	{
		cout << "~DataB()" << endl;
	}
};

class DataC : public DataB
{
public:
	DataC()
	{
		cout << "DataC()" << endl;
	}
	~DataC()
	{
		cout << "~DataC()" << endl;

		// 파생 클래스에서 부모 클래스 멤버 메모리를 해제했다.
		delete _data;
	}
};

// 최초 설계자 코드
class Interface
{
public:
	Interface()
	{
		cout << "Interface()" << endl;
	}

	// 선언만 있고 정의는 없는 순수 가상 함수
	virtual int GetData() const abstract;
	virtual void SetData(int data) abstract;
};

// 후기 개발자 코드
class CData : public Interface
{
private:
	int _data = 0;

public:
	CData()
	{
		cout << "CData()" << endl;
	}

	// 순수 가상 함수는 파생 클래스에서 '반드시' 정의해야 한다.
	virtual int GetData() const
	{
		return _data;
	}

	virtual void SetData(int data)
	{
		_data = data;
	}
};

// 초기 제작자의 코드
class Object
{
protected:
	int _deviceID = 0;

public:
	Object() {}
	virtual ~Object() {}

	// 모든 파생 클래스는 이 메서드를 가졌다고 가정할 수 있다.
	virtual int GetDeviceID() abstract;
};

// 초기 제작자가 만든 함수
void PrintID(Object* pObject)
{
	// 실제로 어떤 것일지는 모르지만 그래도 ID는 출력할 수 있다!
	cout << "Device ID: " << pObject->GetDeviceID() << endl;
}

// 후기 제작자의 코드
class TV : public Object
{
public:
	TV(int id)
	{
		_deviceID = id;
	}

	virtual int GetDeviceID()
	{
		cout << "TV::GetDeivceID()" << endl;
		return _deviceID;
	}
};

class Phone : public Object
{
public:
	Phone(int id)
	{
		_deviceID = id;
	}

	virtual int GetDeviceID()
	{
		cout << "Phone::GetDeivceID()" << endl;
		return _deviceID;
	}
};

// 사용자 코드
int main()
{
	TV a(5);
	Phone b(10);

	// 실제 객체가 무엇이든 알아서 자신의 ID를 출력한다.
	::PrintID(&a);
	::PrintID(&b);

    return 0;
}
