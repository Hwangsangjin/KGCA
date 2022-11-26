#include <iostream>
#include <vector>

int TestFunc(int param)
{
    std::cout << "Function Pointer: " << param << std::endl;

    return param;
}

int main()
{
    // 람다식 선언 및 정의
    auto func = [](int param)->int
    {
        std::cout << "Lambda: " << param << std::endl;

        return param;
    };

    // 람다식 호출
    func(5);

    // 함수 포인터를 이용한 호출
    auto pfTest = TestFunc;
    pfTest(10);

    return 0;
}
