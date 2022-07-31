#include <iostream>

int main()
{
    int aList[5] = { 10, 20, 30, 40, 50 };

    // �������� C ��Ÿ�� �ݺ���
    for (size_t i = 0; i < 5; i++)
    {
        std::cout << aList[i] << ' ';
    }
    std::cout << std::endl;

    // ���� ��� C++11 ��Ÿ�� �ݺ���
    // �� ����� ���� n�� �����Ѵ�.
    for (auto n : aList)
    {
        std::cout << n << std::endl;
    }
    std::cout << std::endl;

    // n�� �� ��ҿ� ���� ������.
    for (auto& n : aList)
    {
        std::cout << n << ' ';
    }
    std::cout << std::endl;

    return 0;
}
