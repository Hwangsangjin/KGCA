#include <iostream>

// std::function ��ü�� ����ϱ� ���� ��� �߰�
#include <functional>

// std::function ���ø� Ŭ������ �Ű������� �޴´�.
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

        // �Լ��� ���μ��� �Լ� ��ü�� ���ٽ����� ����Ѵ�.
        [](const char* pszParam, int nParam)->int
        {
            std::cout << pszParam << " : " << nParam << std::endl;

            return 0;
        });

    std::cout << "-End-" << std::endl;

    return 0;
}
