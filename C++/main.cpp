#include <iostream>

// �Լ� ��ü Ŭ������ ���� �� ����
class Add
{
public:
    // �Լ� ȣ�� �����ڸ� ���� �����Ѵ�.
    int operator()(int a, int b)
    {
        std::cout << "()(int a, int b)" << std::endl;

        return a + b;
    }

    // �پ��� �Ű����� �������� ���� ������ �� �ִ�.
    double operator()(double a, double b)
    {
        std::cout << "()(double a, double b)" << std::endl;

        return a + b;
    }
};

// �������� �ڵ�
void TestFunc(Add& add)
{
    // ����ڰ� ���� �Լ��� �����ڰ� ȣ���Ѵ�.
    std::cout << add(3, 4) << std::endl;
}

// ������� �ڵ�
int main()
{
    // �Լ��� �����
    Add adder;

    //// �Լ� ��ü�� ȣ���Ѵ�.
    //std::cout << adder(3, 4) << std::endl;
    //std::cout << adder(3.3, 4.4) << std::endl;

    // �����ڿ��� �����ϸ� ȣ�����ش�.
    TestFunc(adder);

    return 0;
}
