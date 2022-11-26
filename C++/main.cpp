#include <iostream>

// std::function 객체를 사용하기 위한 헤더 추가
#include <functional>

// std::function 템플릿 클래스를 매개변수로 받는다.
void TestFunc(const char* pszParam, std::function<int(const char*, int)> param)
{
    std::cout << pszParam << std::endl;
    param("Hello", 10);
}

int main()
{
    std::cout << "-Begin-" << std::endl;
    
    ::TestFunc(
        "TestFunc()",

        // 함수의 실인수로 함수 몸체를 람다식으로 기술한다.
        [](const char* pszParam, int nParam)->int
        {
            std::cout << pszParam << " : " << nParam << std::endl;

            return 0;
        });

    std::cout << "-End-" << std::endl;

    return 0;
}
