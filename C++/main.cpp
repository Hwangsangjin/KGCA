#include <iostream>
#include <vector>

int main()
{
    // 요소가 int 자료형이고 개수가 세 개인 벡터 선언
    std::vector<int> vec(3);
    vec[0] = 10;
    vec[1] = 20;
    vec[2] = 30;

    for (auto& i : vec)
    {
        std::cout << i << '\t';
    }

    std::cout << std::endl;

    // 뒤에 새로운 요소 두 개를 더 추가한다.
    vec.push_back(30);
    vec.push_back(40);

    for (auto& i : vec)
    {
        std::cout << i << '\t';
    }

    std::cout << std::endl;

    return 0;
}
