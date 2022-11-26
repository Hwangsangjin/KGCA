#include <iostream>

// 제작자 코드
class CompareBase
{
public:
    virtual int operator()(int a, int b) const abstract;
};

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

    // 배열을 정렬한다.
    void Sort(const CompareBase& cmp)
    {
        int nTemp;

        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 5; j++)
            {
                // 두 항을 비교하는 방법은 함수 객체를 이용한다.
                if (cmp(m_array[i], m_array[j] < 0))
                {
                    nTemp = m_array[i];
                    m_array[i] = m_array[j];
                    m_array[j] = nTemp;
                }
            }
        }
    }
};

// 사용자 코드
class MyCmpDesc : public CompareBase
{
public:
    int operator()(int a, int b) const { return a - b; }
};

class MyCmpAsce : public CompareBase
{
public:
    int operator()(int a, int b) const { return b - a; }
};

int main()
{
    TestData data;

    // 내림차순 정렬 및 출력
    MyCmpDesc desc;
    data.Sort(desc);
    data.Print();

    // 오름차순 정렬 및 출력
    MyCmpAsce asce;
    data.Sort(asce);
    data.Print();

    return 0;
}
