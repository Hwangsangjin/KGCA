#include <iostream>
#include <vector>

int TestFunc(int param)
{
    std::cout << "Function Pointer: " << param << std::endl;

    return param;
}

int main()
{
    // ���ٽ� ���� �� ����
    auto func = [](int param)->int
    {
        std::cout << "Lambda: " << param << std::endl;

        return param;
    };

    // ���ٽ� ȣ��
    func(5);

    // �Լ� �����͸� �̿��� ȣ��
    auto pfTest = TestFunc;
    pfTest(10);

    return 0;
}
