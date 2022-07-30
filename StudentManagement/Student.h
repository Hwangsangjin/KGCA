#pragma once

#include <string>

#define NAME_SIZE 32

class Student
{
private:
    std::string _name;
    unsigned int _index;
    int _kor;
    int _eng;
    int _math;
    int _total;
    float _avg;

public:
    Student(unsigned int in_index, std::string in_name, int in_kor, int in_eng, int in_math);
	~Student();

    const int& GetIndex() const;
    const std::string& GetName() const;
    const int& GetKor() const;
    const int& GetEng() const;
    const int& GetMath() const;
    const int& GetTotal() const;
    const float& GetAvg() const;
};
