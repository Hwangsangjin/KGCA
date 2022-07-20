#pragma once

#include <string.h>

#define NAME_SIZE 32

class Student
{
public:
    unsigned int number;
    char name[NAME_SIZE];
    unsigned int kor;
    unsigned int eng;
    unsigned int math;
    unsigned int total;
    float avg;

public:
    Student(unsigned int in_number, const char* in_name, unsigned int in_kor, unsigned int in_eng, unsigned int in_math);
	~Student();

    const int& get_number() const;
    const char* get_name() const;
    const int& get_kor() const;
    const int& get_eng() const;
    const int& get_math() const;
    const int& get_total() const;
    const float& get_avg() const;
};
