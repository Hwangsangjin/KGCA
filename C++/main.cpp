#include <iostream>

// ����ڴ� �� ���� ���ϴ� ����� �����ؾ� �Ѵ�.
int CompareData(const void* pLeft, const void* pRight)
{
    return *(int*)pLeft - *(int*)pRight;
}

int main()
{
    int aList[5] = { 30, 50, 10, 20, 40 };

    // �� ���� ���ϴ� ���(�Լ� �ּ�)�� �ݹ� �Լ��� �����Ѵ�.
    qsort(aList, 5, sizeof(int), CompareData);

    for (auto& i : aList)
    {
        std::cout << i << '\t';
    }

    std::cout << std::endl;

    return 0;
}
