#include <iostream>
using namespace std;

int main()
{
	char str[80];
	char ch;
	int i = 0;

	// get() �Լ��� ����� �� �� ���
	cout << "���� �Է� : ";

	ch = cin.get();		// ���� ���ڸ� ������ ��� ������ �Է�

	while (ch != '\n')	// ���� ���ڰ� �ƴ� ���� �ݺ�
	{
		str[i] = ch;	// �Է��� ���ڸ� str �迭�� ����
		i++;			// ���� ���� �Է�
	}
	
	str[i] = '\0';		// ���ڿ��� �ϼ��ϱ� ���� �������� �ι��� ����

	cout << "�Էµ� ������ : " << str << endl;

	// getline() �Լ��� ����� �� �� �Է�

	cout << "���ο� ���� �Է� : ";
	cin.getline(str, _countof(str));	// �� ���� ������ �Է�
	cout << "���� �Էµ� ���� : " << str << endl;

	return 0;
}