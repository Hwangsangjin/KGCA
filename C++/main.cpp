#include <iostream>
#include <functional>

// ������ �ڵ�
class TestData
{
private:
    int m_array[5];

public:
    TestData()
    {
        m_array[0] = 30;
        m_array[1] = 10;
        m_array[2] = 50;
        m_array[3] = 20;
        m_array[4] = 40;
    }

    void Print()
    {
        for (auto& i : m_array)
        {
            std::cout << i << '\t';
        }

        std::cout << std::endl;
    }

    // �迭�� �����Ѵ�.
    // �Լ��� �Ű������� ���ٽ��� ���� �� �ִ� function Ŭ������.
    void Sort(std::function<int(int, int)> cmp)
    {
        int nTemp;

        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = i + 1; j < 5; j++)
            {
                // �� ���� ���ϴ� ����� �Լ� ��ü�� �̿��Ѵ�.
                if (cmp(m_array[i], m_array[j]) < 0)
                {
                    nTemp = m_array[i];
                    m_array[i] = m_array[j];
                    m_array[j] = nTemp;
                }
            }
        }
    }
};

int main()
{
    TestData data;

    // �������� ���� �� ���
    data.Sort([](int a, int b)->int { return a - b; });
    data.Print();

    // �������� ���� �� ���
    data.Sort([](int a, int b)->int {return b - a; });
    data.Print();

    return 0;
}
