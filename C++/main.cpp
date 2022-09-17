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

	// ���� �Լ��� ���� �� �����ߴ�.
	virtual void PrintData()
	{
		cout << "Data: " << _pszData << endl;
	}

	void TestFunc()
	{
		cout << "-TestFunc()-" << endl;

		// �� ������ �Լ��� ȣ��ȵ�.
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

		// �Ļ� Ŭ�������� �θ� Ŭ���� ��� �޸𸮸� �����ߴ�.
		delete _data;
	}
};

// ���� ������ �ڵ�
class Interface
{
public:
	Interface()
	{
		cout << "Interface()" << endl;
	}

	// ���� �ְ� ���Ǵ� ���� ���� ���� �Լ�
	virtual int GetData() const abstract;
	virtual void SetData(int data) abstract;
};

// �ı� ������ �ڵ�
class CData : public Interface
{
private:
	int _data = 0;

public:
	CData()
	{
		cout << "CData()" << endl;
	}

	// ���� ���� �Լ��� �Ļ� Ŭ�������� '�ݵ��' �����ؾ� �Ѵ�.
	virtual int GetData() const
	{
		return _data;
	}

	virtual void SetData(int data)
	{
		_data = data;
	}
};

// �ʱ� �������� �ڵ�
class Object
{
protected:
	int _deviceID = 0;

public:
	Object() {}
	virtual ~Object() {}

	// ��� �Ļ� Ŭ������ �� �޼��带 �����ٰ� ������ �� �ִ�.
	virtual int GetDeviceID() abstract;
};

// �ʱ� �����ڰ� ���� �Լ�
void PrintID(Object* pObject)
{
	// ������ � �������� ������ �׷��� ID�� ����� �� �ִ�!
	cout << "Device ID: " << pObject->GetDeviceID() << endl;
}

// �ı� �������� �ڵ�
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

// ����� �ڵ�
int main()
{
	TV a(5);
	Phone b(10);

	// ���� ��ü�� �����̵� �˾Ƽ� �ڽ��� ID�� ����Ѵ�.
	::PrintID(&a);
	::PrintID(&b);

    return 0;
}
