#include <iostream>
using namespace std;

class Str
{
private:
	// ���ڿ��� �����ϱ� ���� ���� �Ҵ��� �޸𸮸� ����Ű�� ������
	char* _pszData;

	// ����� ���ڿ��� ����
	int _nLength;

public:
	// �⺻ ������
	Str()
		: _pszData(nullptr)
		, _nLength(0)
	{
	}

	// ��ȯ ������
	explicit Str(const char* pszParam)
		: _pszData(nullptr)
		, _nLength(0)
	{
		SetString(pszParam);
	}

	// ���� ������
	Str(const Str& rhs)
		: _pszData(nullptr)
		, _nLength(0)
	{
		this->SetString(rhs.GetString());
	}

	// �̵� ������
	Str(Str&& rhs)
		: _pszData(nullptr)
		, _nLength(0)
	{
		cout << "Str �̵� ������ ȣ��" << endl;

		// ���� ���縦 �����ص� �������.
		// ������ ������ �� �Ҹ�Ǳ� �����̴�!
		_pszData = rhs._pszData;
		_nLength = rhs._nLength;

		// ���� �ӽ� ��ü�� ������� �ʱ�ȭ�Ѵ�.
		// ����� �����ϸ� �� �ȴ�.
		rhs._pszData = nullptr;
		rhs._nLength = 0;
	}

	// �Ҹ���
	~Str()
	{
		// ��ü�� �Ҹ��ϱ� ���� �޸𸮸� �����Ѵ�.
		Release();
	}

	int SetString(const char* pszParam)
	{
		// ���ο� ���ڿ� �Ҵ翡 �ռ� ���� ������ �����Ѵ�.
		Release();

		// nullptr�� �μ��� �Լ��� ȣ���ߴٴ� ���� �޸𸮸� �����ϰ�
		// nullptr�� �ʱ�ȭ�ϴ� ������ �� �� �ִ�.
		if (pszParam == nullptr)
		{
			return 0;
		}

		// ���̰� 0�� ���ڿ��� �ʱ�ȭ�� �ν��ϰ� ó���Ѵ�.
		int nLength = strlen(pszParam);

		if (nLength == 0)
		{
			return 0;
		}

		// ���ڿ��� ���� NULL ���ڸ� ����� �޸𸮸� �Ҵ��Ѵ�.
		_pszData = new char[nLength + 1];

		// ���� �Ҵ��� �޸𸮿� ���ڿ��� �����Ѵ�.
		strcpy_s(_pszData, sizeof(char) * (nLength + 1), pszParam);
		_nLength = nLength;

		// ���ڿ��� ���̸� ��ȯ�Ѵ�.
		return nLength;
	}

	// ��� �б⸸ �����ϹǷ� �޼��带 ���ȭ�Ѵ�.
	const char* GetString() const
	{
		return _pszData;
	}

	void Release()
	{
		// �� �Լ��� ���� �� ȣ��� ��츦 ����� �ֿ� ����� �ʱ�ȭ�Ѵ�.
		if (_pszData != nullptr)
		{
			delete[] _pszData;
		}

		_pszData = nullptr;
		_nLength = 0;
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

	// �̵� ������
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
	// �̸� ���� �ӽ� ��ü�� ���������.
	TestStr();

    return 0;
}