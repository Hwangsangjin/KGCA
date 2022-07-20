#include "Student.h"

Student::Student(unsigned int in_number, const char* in_name, unsigned int in_kor, unsigned int in_eng, unsigned int in_math) : number(in_number), kor(in_kor), eng(in_eng), math(in_math)
{
    strcpy_s(name, in_name);
    total = kor + eng + math;
    avg = total / 3.0f;
}

Student::~Student()
{
}

const int& Student::get_number() const
{
    return number;
}

const char* Student::get_name() const
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
