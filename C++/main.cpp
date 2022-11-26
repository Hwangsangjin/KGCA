#include <iostream>

int main()
{
    int data = 10;
    std::cout << data << std::endl;

    auto TestFunc = [data]()->void
    {
        std::cout << data << std::endl;
    };

    TestFunc();

    return 0;
}
