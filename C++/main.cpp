#include <iostream>
#include <vector>

int main()
{
    // ��Ұ� int �ڷ����̰� ������ �� ���� ���� ����
    std::vector<int> vec(3);
    vec[0] = 10;
    vec[1] = 20;
    vec[2] = 30;

    for (auto& i : vec)
    {
        std::cout << i << '\t';
    }

    std::cout << std::endl;

    // �ڿ� ���ο� ��� �� ���� �� �߰��Ѵ�.
    vec.push_back(30);
    vec.push_back(40);

    for (auto& i : vec)
    {
        std::cout << i << '\t';
    }

    std::cout << std::endl;

    return 0;
}
