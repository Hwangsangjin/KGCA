#pragma once

#define NAME_SIZE 32

#include <string.h>

class Student
{
public:
    int number;
    char name[NAME_SIZE];
    int kor;
    int eng;
    int math;
    int total;
    float avg;

public:
    Student(int in_number, const char* in_name, int in_kor, int in_eng, int in_math)
    {
        number = in_number;
        strcpy_s(name, in_name);
        kor = in_kor;
        eng = in_eng;
        math = in_math;
        total = kor + eng + math;
        avg = total / 3.0f;
    }
	~Student();

    const int& get_number() const
    {
        return number;
    }

    const char* get_name()
    {
        return name;
    }

    const int& get_kor() const
    {
        return kor;
    }

    const int& get_eng() const
    {
        return eng;
    }

    const int& get_math() const
    {
        return math;
    }

    const int& get_total() const
    {
        return total;
    }

    const float& get_avg() const
    {
        return avg;
    }
};
