#include <iostream>
using namespace std;

// 제작자 코드
class CTest
{
public:
    // 생성자 초기화 목록을 이용한 멤버 초기화
    CTest() {}

    // 두 개의 멤버 데이터 선언과 동시에 초기화
    int m_nData1 = 10;
    int m_nData2 = 20;

    // 멤버 함수 선언 및 정의
    void PrintData()
    {
        // 두 개의 멤버 데이터에 접근하고 값을 출력한다.
        cout << m_nData1 << endl;
        cout << m_nData2 << endl;
    }
};

// 사용자 코드
int main()
{
    CTest t;
    t.PrintData();

    return 0;
}