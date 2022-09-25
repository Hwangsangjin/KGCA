#include <iostream>

using namespace std;

class Test
{
public:
    Test() { cout << "Test()" << endl; }
    ~Test() { cout << "~Test()" << endl; }

    void TestFunc() { cout << "TestFunc()" << endl; }
};

void RemoveTest(Test* pTest)
{
    cout << "RemoveTest()" << endl;

    // ����� �迭�� �����Ѵ�.
    delete[] pTest;
}

int main()
{
    cout << "-Begin-" << endl;

    // ��� ��ü�� �Ҹ��� �Լ��� ������ ����Ѵ�.
    shared_ptr<Test> ptr(new Test[3], RemoveTest);

    cout << "-End-" << endl;

    return 0;
}
