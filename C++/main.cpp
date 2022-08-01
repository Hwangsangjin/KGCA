#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Student
{
public:
    string name;
    int score;

    bool operator<(const Student& st) const
    {
        return score < st.score;
    }
};

template <typename T>
void Print_queue(T q)
{
    while (!q.empty())
    {
        cout << q.top() << " ";
        q.pop();
    }
    cout << endl;
}

int main()
{
    std::vector<int> vec{ 4, 2, 3, 5, 1 };

    priority_queue<int> pq1;

    for (auto& n : vec)
    {
        pq1.push(n);
    }
    Print_queue(pq1);

    priority_queue<int, vector<int>, greater<int>> pq2(vec.begin(), vec.end());
    Print_queue(pq2);

    priority_queue<Student> students;
    students.push({ "Amelia", 80 });
    students.push({ "Sophia", 40 });
    students.push({ "Olivia", 95 });
    students.push({ "George", 70 });

    while (!students.empty())
    {
        auto& s = students.top();
        cout << s.name << " (" << s.score << ")" << endl;
        students.pop();
    }
    
    return 0;
}