#include <iostream>

int main()
{
    int aList[5] = { 10, 20, 30, 40, 50 };

    // 전형적인 C 스타일 반복문
    for (size_t i = 0; i < 5; i++)
    {
        std::cout << aList[i] << ' ';
    }
    std::cout << std::endl;

    // 범위 기반 C++11 스타일 반복문
    // 각 요소의 값을 n에 복사한다.
    for (auto n : aList)
    {
        std::cout << n << std::endl;
    }
    std::cout << std::endl;

    // n은 각 요소에 대한 참조다.
    for (auto& n : aList)
    {
        std::cout << n << ' ';
    }
    std::cout << std::endl;

    return 0;
}
