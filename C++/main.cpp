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

	friend Str operator+(const char* data, const Str& str);
};

Str operator+(const char* data, const Str& str)
{
	Str result(data);
	result.Append(str._data);

	return result;
}

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
	int _data = 0;

public:
	Data() {}
	Data(int data) : _data(data) {}
	virtual ~Data() {}
	void SetData(int data) { _data = data; }
	int GetData() { return _data; }

	// friend 함수로 선언한다.
	friend void PrintData(const Data&);

	Data operator+(const Data& rhs)
	{
		return Data(_data + rhs._data);
	}

	Data& operator=(const Data& rhs)
	{
		_data = rhs._data;

		return *this;
	}

	operator int() { return _data; }
};

void PrintData(const Data& rhs)
{
	// 프렌드 함수이므로 접근 제어 지시자의 영향을 받지 않고
	// private 멤버에 직접 접근한다.
	cout << "PrintData(): " << rhs._data << endl;
}

class DataEx : public Data
{
public:
	DataEx(int data) : Data(data) {}

	// 인터페이스를 맞춰주기 의한 연산자 다중 정의
	using Data::operator+;
	using Data::operator=;

	DataEx operator+(const DataEx& rhs)
	{
		return DataEx(static_cast<int>(Data::operator+(rhs)));
	}

	void SetData(int data)
	{
		if (data > 10) data = 10;

		Data::SetData(data);
	}
};

class USB
{
public:
	virtual int GetUsbVersion() abstract;
	virtual int GetTransferRate() abstract;
};

class Serial
{
public:
	virtual int GetSignal() abstract;
	virtual int GetRate() abstract;
};

class Device
	: public USB
	, public Serial
{
public:
	// USB 인터페이스
	virtual int GetUsbVersion() { return 0; }
	virtual int GetTransferRate() { return 0; }

	// 시리얼 인터페이스
	virtual int GetSignal() { return 0; }
	virtual int GetRate() { return 0; }
};

class Node
{
private:
	// 단일 연결 리스트로 관리할 데이터
	char _name[32];
	Node* pNext = nullptr;

	// friend 클래스 선언
	friend class List;

public:
	explicit Node(const char* name)
	{
		strcpy_s(_name, sizeof(_name), name);
	}
};

class List
{
private:
	Node _head;

public:
	List()
		: _head("Dummy Head")
	{}
	~List()
	{
		// 리스트에 담긴 데이터들을 모두 출력하고 삭제
		Node* pNode = _head.pNext;
		Node* pDelete = nullptr;

		while (pNode)
		{
			pDelete = pNode;
			pNode = pNode->pNext;
			delete pDelete;
		}

		_head.pNext = nullptr;
	}

	// 리스트에 새로운 노드를 추가
	void AddNewNode(const char* name)
	{
		Node* pNode = new Node(name);

		pNode->pNext = _head.pNext;
		_head.pNext = pNode;
	}

	// 리스트의 모든 노드 값을 출력
	void Print()
	{
		Node* pNode = _head.pNext;
		while (pNode)
		{
			cout << pNode->_name << endl;
			pNode = pNode->pNext;
		}
	}
};

// UI 클래스
class UI
{
private:
	// UI 클래스 내부에 자료구조 객체에 대한 참조만 존재한다.
	List& _list;

public:
	// 참조 멤버는 반드시 초기화 목록을 이용해 초기화해야 한다.
	UI(List& list)
		: _list(list)
	{}

	// 메뉴 출력 및 사용자 입력을 확인한다.
	int PrintMenu()
	{
		system("cls");
		cout << "[1]Add\t" << "[2]Print\t" << "[0]Exit\n:";
		cout.flush();
		int input = 0;
		cin >> input;

		return input;
	}

	// 지속적으로 메뉴를 출력하는 메인 이벤트 반복문
	void Run()
	{
		char name[32];
		int input = 0;

		while ((input = PrintMenu()) > 0)
		{
			switch (input)
			{
			case 1:	// Add
				cout << "이름: ";
				cout.flush();
				cin >> name;
				_list.AddNewNode(name);
				break;
				
			case 2:	// Print
				_list.Print();
				break;

			default:
				break;
			}
		}
	}
};

// 프로그램 시작
int main()
{
	// 자료구조와 UI 객체를 별도로 선언하고 연결한다.
	List list;
	UI ui(list);
	ui.Run();

    return 0;
}
