#include <iostream>

int main()
{
    int x = 10;
    int y = 20;
    int z = 0;

    auto TestFunc = [&]()->int
    {
        return z = x + y;
    };

    std::cout << TestFunc() << std::endl;
  
    return 0;
}
