#include <iostream>

// 함수 객체 클래스의 선언 및 정의
class Add
{
public:
    // 함수 호출 연산자를 다중 정의한다.
    int operator()(int a, int b)
    {
        std::cout << "()(int a, int b)" << std::endl;

        return a + b;
    }

    // 다양한 매개변수 구성으로 다중 정의할 수 있다.
    double operator()(double a, double b)
    {
        std::cout << "()(double a, double b)" << std::endl;

        return a + b;
    }
};

// 제작자의 코드
void TestFunc(Add& add)
{
    // 사용자가 만든 함수를 제작자가 호출한다.
    std::cout << add(3, 4) << std::endl;
}

// 사용자의 코드
int main()
{
    // 함수를 만들고
    Add adder;

    //// 함수 객체를 호출한다.
    //std::cout << adder(3, 4) << std::endl;
    //std::cout << adder(3.3, 4.4) << std::endl;

    // 제작자에게 전달하면 호출해준다.
    TestFunc(adder);

    return 0;
}
