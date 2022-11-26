#include <iostream>

// 사용자는 각 항을 비교하는 방법을 정의해야 한다.
int CompareData(const void* pLeft, const void* pRight)
{
    return *(int*)pLeft - *(int*)pRight;
}

int main()
{
    int aList[5] = { 30, 50, 10, 20, 40 };

    // 각 항을 비교하는 방법(함수 주소)을 콜백 함수로 전달한다.
    qsort(aList, 5, sizeof(int), CompareData);

    for (auto& i : aList)
    {
        std::cout << i << '\t';
    }

    std::cout << std::endl;

    return 0;
}
