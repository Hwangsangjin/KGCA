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

	// ��� �б⸸ �����ϹǷ� �޼��带 ��ȭ�Ѵ�.
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
};

class Test
{
private:
	int _data;

	// ���� ��� ���� ����(���Ǵ� �ƴϴ�!)
	static int _count;

public:
	Test(int param) : _data(param) { _count++; }
	~Test() {}

	int GetData() { return _data; }
	void ResetCount() { _count = 0; }

	// ���� �޼��� ���� �� ����
	static int GetCount()
	{
		return _count;
	}
};

class Data
{
private:
	// ������ ��� ������
	int* _pData = nullptr;

public:
	Data(int param)
	{
		_pData = new int;
		*_pData = param;
	}

	// ���� ������ ���� �� ����
	Data(const Data& rhs)
	{
		cout << "Data(const Data&)" << endl;

		// �޸𸮸� �Ҵ��Ѵ�.
		_pData = new int;

		// �����Ͱ� ����Ű�� ��ġ�� ���� �����Ѵ�.
		*_pData = *rhs._pData;
	}

	// ��ü�� �Ҹ��ϸ� ���� �Ҵ��� �޸𸮸� �����Ѵ�.
	~Data()
	{
		delete _pData;
	}

	// �ܼ� ���� ������ �Լ��� �����Ѵ�.
	Data& operator=(const Data& rhs)
	{
		*_pData = *rhs._pData;

		// ��ü �ڽſ� ���� ������ ��ȯ�Ѵ�.
		return *this;
	}

	int GetData()
	{
		if (_pData != nullptr)
		{
			return *_pData;
		}

		return 0;
	}
};

int main()
{
	Data a(10);
	Data b(20);

	// �ܼ� ������ �õ��ϸ� ��� ����� ���� �״�� �����Ѵ�.
	a = b;

	cout << a.GetData() << endl;

    return 0;
}