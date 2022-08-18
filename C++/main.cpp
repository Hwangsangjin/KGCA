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
	Str()
		: _pszData(nullptr)
		, _nLength(0)
	{
	}

	~Str()
	{
		// ��ü�� �Ҹ��ϱ� ���� �޸𸮸� �����Ѵ�.
		Release();
	}

	// ���� ������
	Str(const Str& rhs)
		: _pszData(nullptr)
		, _nLength(0)
	{
		this->SetString(rhs.GetString());
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

	void TestFunc(const Str& param)
	{
		cout << param.GetString() << endl;
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
};

class Data
{
private:
	int _nData = 0;

public:
	// �Ű������� �ϳ����� �����ڴ� ����ȯ�� �����ϴ�.
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

// �Ű������� Ŭ���� �����̸� ��ȯ ������ �����ϴ�.
void TestFunc(Data param)
{
	cout << "TestFunc(): " << param.GetData() << endl;
}

int main()
{
	// int �ڷ������� Data �������� ��ȯ�� �� �ִ�.
	TestFunc(5);

    return 0;
}