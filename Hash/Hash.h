#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

// ü�̴��� ������ �ؽ� Ŭ����
class hash_set
{
private:
	// ����
	int sz;
	// ������
	std::vector<std::list<int>> data;

public:
	// ������
	hash_set(int n) : sz(n), data(sz) {}

	// �ؽ� �Լ�
	int hash(int key) { return  key % sz; }

	// �߰�
	void insert(int value) { data[hash(value)].push_back(value); }

	// Ž��
	bool find(int value)
	{
		auto& entries = data[hash(value)];
		return std::find(entries.begin(), entries.end(), value) != entries.end();
	}

	// ����
	void erase(int value)
	{
		auto& entries = data[hash(value)];
		auto iter = std::find(entries.begin(), entries.end(), value);

		if (iter != entries.end())
		{
			entries.erase(iter);
		}
	}

	// ���
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