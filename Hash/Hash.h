#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

// 체이닝을 구현한 해싱 클래스
class hash_set
{
private:
	// 갯수
	int sz;
	// 데이터
	std::vector<std::list<int>> data;

public:
	// 생성자
	hash_set(int n) : sz(n), data(sz) {}

	// 해시 함수
	int hash(int key) { return  key % sz; }

	// 추가
	void insert(int value) { data[hash(value)].push_back(value); }

	// 탐색
	bool find(int value)
	{
		auto& entries = data[hash(value)];
		return std::find(entries.begin(), entries.end(), value) != entries.end();
	}

	// 삭제
	void erase(int value)
	{
		auto& entries = data[hash(value)];
		auto iter = std::find(entries.begin(), entries.end(), value);

		if (iter != entries.end())
		{
			entries.erase(iter);
		}
	}

	// 출력
	void print()
	{
		for (size_t i = 0; i < sz; i++)
		{
			std::cout << i << ": ";

			for(auto& n : data[i])
			{
				std::cout << n << " ";
			}
			std::cout << std::endl;
		}
	}
};