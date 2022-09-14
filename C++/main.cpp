#include <iostream>
using namespace std;

class Str
{
private:
	// ���ڿ��� �����ϱ� ���� ���� �Ҵ��� �޸𸮸� ����Ű�� ������
	char* _str;

	// ����� ���ڿ��� ����
	int _length;

public:
	// �⺻ ������
	Str()
		: _str(nullptr)
		, _length(0)
	{
	}

	// ��ȯ ������
	explicit Str(const char* str)
		: _str(nullptr)
		, _length(0)
	{
		SetString(str);
	}

	// ���� ������
	Str(const Str& rhs)
		: _str(nullptr)
		, _length(0)
	{
		this->SetString(rhs.GetString());
	}

	// �̵� ������
	Str(Str&& rhs)
		: _str(nullptr)
		, _length(0)
	{
		cout << "Str �̵� ������ ȣ��" << endl;

		// ���� ���縦 �����ص� �������.
		// ������ ������ �� �Ҹ�Ǳ� �����̴�!
		_str = rhs._str;
		_length = rhs._length;

		// ���� �ӽ� ��ü�� ������� �ʱ�ȭ�Ѵ�.
		// ����� �����ϸ� �� �ȴ�.
		rhs._str = nullptr;
		rhs._length = 0;
	}

	// �Ҹ���
	~Str()
	{
		// ��ü�� �Ҹ��ϱ� ���� �޸𸮸� �����Ѵ�.
		Release();
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
		_str = new char[length + 1];

		// ���� �Ҵ��� �޸𸮿� ���ڿ��� �����Ѵ�.
		strcpy_s(_str, sizeof(char) * (length + 1), str);
		_length = length;

		// ���ڿ��� ���̸� ��ȯ�Ѵ�.
		return length;
	}

	// ��� �б⸸ �����ϹǷ� �޼��带 ���ȭ�Ѵ�.
	const char* GetString() const
	{
		return _str;
	}

	void Release()
	{
		// �� �Լ��� ���� �� ȣ��� ��츦 ����� �ֿ� ����� �ʱ�ȭ�Ѵ�.
		if (_str != nullptr)
		{
			delete[] _str;
		}

		_str = nullptr;
		_length = 0;
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
		return _str;
	}
};

Str TestStr()
{
	Str str("TestStr() return");
	cout << str << endl;
	return str;
}

// ������ - �ʱ� ������
class Data
{
private:	// ������ ���� �Ұ���
	int _data = 0;

protected:	// �Ļ� Ŭ������ ���� ����
	void PrintData() { cout << "Data::PrintData()" << endl; }

public:		// ������ ���� ����
	Data() { cout << "Data()" << endl; }

	int GetData() const { return _data; }
	void SetData(int data) { _data = data; }
};

// ������ - �ı� ������
class DataEx : public Data
{
public:
	DataEx() { cout << "DataEx()" << endl; }

	void TestFunc()
	{
		// �⺻ ���� ����� ����
		PrintData();
		SetData(5);
		cout << Data::GetData() << endl;
	}
};

// �����
int main()
{
	DataEx data;

	// �⺻ Ŭ����(Data) ����� ����
	data.SetData(10);
	cout << data.GetData() << endl;

	// �Ļ� Ŭ����(DataEx) ����� ����
	data.TestFunc();

    return 0;
}