#include "Student.h"

Student::Student(unsigned int in_index, std::string in_name, int in_kor, int in_eng, int in_math)
    : name(in_name), kor(in_kor), eng(in_eng), math(in_math)
{
    index = in_index;
    total = kor + eng + math;
    avg = total / 3.0f;
}

Student::~Student()
{
}

const int& Student::get_index() const
{
    return index;
}

const std::string& Student::get_name() const
{
    return name;
}

const int& Student::get_kor() const
{
    return kor;
}

const int& Student::get_eng() const
{
    return eng;
}

const int& Student::get_math() const
{
    return math;
}

const int& Student::get_total() const
{
    return total;
}

const float& Student::get_avg() const
{
    return avg;
}
