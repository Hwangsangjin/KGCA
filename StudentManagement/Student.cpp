#include "Student.h"

Student::Student(unsigned int index, std::string name, int kor, int eng, int math)
    : _name(name), _kor(kor), _eng(eng), _math(math)
{
    _index = index;
    _total = _kor + _eng + _math;
    _avg = _total / 3.0f;
}

Student::~Student()
{
}

const int& Student::GetIndex() const
{
    return _index;
}

const std::string& Student::GetName() const
{
    return _name;
}

const int& Student::GetKor() const
{
    return _kor;
}

const int& Student::GetEng() const
{
    return _eng;
}

const int& Student::GetMath() const
{
    return _math;
}

const int& Student::GetTotal() const
{
    return _total;
}

const float& Student::GetAvg() const
{
    return _avg;
}
