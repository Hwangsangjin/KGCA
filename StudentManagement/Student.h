#pragma once

#include <string.h>

#define NAME_SIZE 32

class Student
{
private:
    char name[NAME_SIZE];
    unsigned int index;
    unsigned int kor;
    unsigned int eng;
    unsigned int math;
    unsigned int total;
    float avg;

public:
    Student(unsigned int in_index, const char* in_name, unsigned int in_kor, unsigned int in_eng, unsigned int in_math);
	~Student();

    const int& get_index() const;
    const char* get_name() const;
    const int& get_kor() const;
    const int& get_eng() const;
    const int& get_math() const;
    const int& get_total() const;
    const float& get_avg() const;
};
