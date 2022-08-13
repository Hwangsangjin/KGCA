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
	int _data;

public:
	Data()
		: _data(0)
	{
		cout << "Data()" << endl;
	}

	Data(int param)
		: _data(param)
	{
		cout << "Data(int)" << endl;
	}

	// ���� �����ڸ� �ƿ� ���������ν� ���� ������ ���´�.
	Data(const Data& rhs) = delete;

	// �б� ������ ����� �޼���
	int GetData() const { return _data; }

	// ��� ������ ���⸦ �õ��ϴ� �޼���
	void SetData(int param) { _data = param; }

	// �Ǽ��� double �ڷ��� ���μ��� �Ѿ���� ��츦 �����Ѵ�.
	void SetData(double param) = delete;
};

// �Ű������� Data Ŭ���� '����' �����̹Ƿ� ��ü�� �������� �ʴ´�!
void TestFunc(Data& param)
{
	cout << "TestFunc()" << endl;

	// ��ȣ���� �Լ����� �Ű����� �ν��Ͻ��� ���� �����Ѵ�.
	param.SetData(20);
}

int main()
{
	cout << "Begin" << endl;
	Data a(10);
	TestFunc(a);

	// �Լ� ȣ�� �� a�� ���� ����Ѵ�.
	cout << "a: " << a.GetData() << endl;

	cout << "End" << endl;

    return 0;
}