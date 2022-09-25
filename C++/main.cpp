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

    // 대상을 배열로 삭제한다.
    delete[] pTest;
}

int main()
{
    cout << "-Begin-" << endl;

    // 대상 객체를 소멸할 함수를 별도로 등록한다.
    shared_ptr<Test> ptr(new Test[3], RemoveTest);

    cout << "-End-" << endl;

    return 0;
}
