#include <iostream>

using namespace std;

class Str
{
private:
	// ���ڿ��� �����ϱ� ���� ���� �Ҵ��� �޸𸮸� ����Ű�� ������
	char* _data;

	// ����� ���ڿ��� ����
	int _length;

public:
	// �⺻ ������
	Str()
		: _data(nullptr)
		, _length(0)
	{
	}

	// ��ȯ ������
	explicit Str(const char* str)
		: _data(nullptr)
		, _length(0)
	{
		SetString(str);
	}

	// ���� ������
	Str(const Str& rhs)
		: _data(nullptr)
		, _length(0)
	{
		this->SetString(rhs.GetString());
	}

	// �̵� ������
	Str(Str&& rhs)
		: _data(nullptr)
		, _length(0)
	{
		cout << "Str �̵� ������ ȣ��" << endl;

		// ���� ���縦 �����ص� �������.
		// ������ ������ �� �Ҹ�Ǳ� �����̴�!
		_data = rhs._data;
		_length = rhs._length;

		// ���� �ӽ� ��ü�� ������� �ʱ�ȭ�Ѵ�.
		// ����� �����ϸ� �� �ȴ�.
		rhs._data = nullptr;
		rhs._length = 0;
	}

	// �Ҹ���
	~Str()
	{
		// ��ü�� �Ҹ��ϱ� ���� �޸𸮸� �����Ѵ�.
		Release();
	}

	virtual void OnSetString(const char* data, int length)
	{
		// �ƹ��� �ڵ嵵 �߰����� �ʴ´�.
	}

	int SetString(const char* str)
	{
		// ���ο� ���ڿ� �Ҵ翡 �ռ� ���� ������ �����Ѵ�.
		Release();

		// nullptr�� �μ��� �Լ��� ȣ���ߴٴ� ���� �޸𸮸� �����ϰ�
		// nullptr�� �ʱ�ȭ�ϴ� ������ �� �� �ִ�.
		if (str == nullptr)
		{
			return 0;
		}

		// ���̰� 0�� ���ڿ��� �ʱ�ȭ�� �ν��ϰ� ó���Ѵ�.
		int length = strlen(str);

		if (length == 0)
		{
			return 0;
		}

		// ���ڿ��� ���� NULL ���ڸ� ����� �޸𸮸� �Ҵ��Ѵ�.
		_data = new char[length + 1];

		// ���� �Ҵ��� �޸𸮿� ���ڿ��� �����Ѵ�.
		strcpy_s(_data, sizeof(char) * (length + 1), str);
		_length = length;

		// �̷��� ȣ���Ѵ�!
		OnSetString(_data, _length);

		// ���ڿ��� ���̸� ��ȯ�Ѵ�.
		return length;
	}

	// ��� �б⸸ �����ϹǷ� �޼��带 ���ȭ�Ѵ�.
	const char* GetString() const
	{
		return _data;
	}

	void Release()
	{
		// �� �Լ��� ���� �� ȣ��� ��츦 ����� �ֿ� ����� �ʱ�ȭ�Ѵ�.
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
		//�Ű����� ��ȿ�� �˻�
		if (str == nullptr)
		{
			return 0;
		}

		int length = strlen(str);
		if (length == 0)
		{
			return 0;
		}

		// ��Ʈ�� ���ڿ��� ���ٸ� ���� ���ڿ��� �Ҵ��� �Ͱ� �����ϰ� ó��.
		if (str == nullptr)
		{
			SetString(str);
			return _length;
		}

		// ���� ���ڿ��� ���� ���.
		int currentLength = _length;

		// �� ���ڿ��� ���ļ� ������ �� �ִ� �޸𸮸� ���� �Ҵ�.
		char* result = new char[currentLength + length + 1];

		// ���ڿ� ����
		strcpy_s(result,
			sizeof(char) * (currentLength + 1), _data);
		strcpy_s(result + (sizeof(char) * currentLength),
			sizeof(char) * (length + 1), str);

		// ���� ���ڿ� ���� �� ��� ���� ����
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
		// �ڱ� �ڽſ� ���� �����̸� �ƹ��͵� ���� �ʴ´�.
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
		if (strcmp(data, "�۸��̾Ƶ�") == 0)
		{
			strcpy_s(data,
				sizeof(char) * (length + 1), "*���ѻ��*");
		}
	}

	int SetString(const char* param)
	{
		int result;

		if (strcmp(param, "�۸��̾Ƶ�") == 0)
		{
			result = Str::SetString("���ѻ��");
		}
		else
		{
			result = Str::SetString(param);
		}

		return result;
	}
};

// ������ �ڵ�
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

	// friend �Լ��� �����Ѵ�.
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
	// ������ �Լ��̹Ƿ� ���� ���� �������� ������ ���� �ʰ�
	// private ����� ���� �����Ѵ�.
	cout << "PrintData(): " << rhs._data << endl;
}

class DataEx : public Data
{
public:
	DataEx(int data) : Data(data) {}

	// �������̽��� �����ֱ� ���� ������ ���� ����
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
	// USB �������̽�
	virtual int GetUsbVersion() { return 0; }
	virtual int GetTransferRate() { return 0; }

	// �ø��� �������̽�
	virtual int GetSignal() { return 0; }
	virtual int GetRate() { return 0; }
};

class Node
{
private:
	// ���� ���� ����Ʈ�� ������ ������
	char _name[32];
	Node* pNext = nullptr;

	// friend Ŭ���� ����
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
		// ����Ʈ�� ��� �����͵��� ��� ����ϰ� ����
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

	// ����Ʈ�� ���ο� ��带 �߰�
	void AddNewNode(const char* name)
	{
		Node* pNode = new Node(name);

		pNode->pNext = _head.pNext;
		_head.pNext = pNode;
	}

	// ����Ʈ�� ��� ��� ���� ���
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

// UI Ŭ����
class UI
{
private:
	// UI Ŭ���� ���ο� �ڷᱸ�� ��ü�� ���� ������ �����Ѵ�.
	List& _list;

public:
	// ���� ����� �ݵ�� �ʱ�ȭ ����� �̿��� �ʱ�ȭ�ؾ� �Ѵ�.
	UI(List& list)
		: _list(list)
	{}

	// �޴� ��� �� ����� �Է��� Ȯ���Ѵ�.
	int PrintMenu()
	{
		system("cls");
		cout << "[1]Add\t" << "[2]Print\t" << "[0]Exit\n:";
		cout.flush();
		int input = 0;
		cin >> input;

		return input;
	}

	// ���������� �޴��� ����ϴ� ���� �̺�Ʈ �ݺ���
	void Run()
	{
		char name[32];
		int input = 0;

		while ((input = PrintMenu()) > 0)
		{
			switch (input)
			{
			case 1:	// Add
				cout << "�̸�: ";
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

// ���α׷� ����
int main()
{
	// �ڷᱸ���� UI ��ü�� ������ �����ϰ� �����Ѵ�.
	List list;
	UI ui(list);
	ui.Run();

    return 0;
}
