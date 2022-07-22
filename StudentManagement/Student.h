#pragma once

#include <string>

#define NAME_SIZE 32

class Student
{
private:
    std::string name;
    unsigned int index;
    int kor;
    int eng;
    int math;
    int total;
    float avg;

public:
    Student(unsigned int in_index, std::string in_name, int in_kor, int in_eng, int in_math);
	~Student();

    const int& get_index() const;
    const std::string& get_name() const;
    const int& get_kor() const;
    const int& get_eng() const;
    const int& get_math() const;
    const int& get_total() const;
    const float& get_avg() const;
};
