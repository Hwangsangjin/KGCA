#pragma once

#include <vector>
#include <algorithm>

// �ִ� ��
class MaxHeap
{
private:
	// ���� �迭
	std::vector<int> vec;

	// �θ� ����� �ε���
	int parent(int i) { return i / 2; }
	// ���� �ڽ� ����� �ε���
	int left(int i) { return 2 * i; }
	// ������ �ڽ� ����� �ε���
	int right(int i) { return 2 * i + 1; }
	
	// �� �Ӽ��� �����ϵ��� Ʈ�� �籸��
	void heapify_up(int i)
	{
		// ��Ʈ ��尡 �ƴϰ�
		// ���� ����� ���� �θ� ��� ���� ū ���
		if (i > 1 && vec[i] > vec[parent(i)])
		{
			// ���� ���� �θ� ��� ��ȯ
			std::swap(vec[i], vec[parent(i)]);

			// �θ� ��忡�� �� �۾��� �ݺ�
			heapify_up(parent(i));
		}
	}

	// �� �Ӽ��� �����ϵ��� Ʈ�� �籸��
	void heapify_down(int i)
	{
		// ���� ����� ��ȣ�� ����
		int largest = i;

		// ���� ����� ���� �ڽ� ��尡 �����ϰ�
		// ���� �ڽ� ����� ���� ���� ��庸�� ū ���
		if (left(i) < vec.size() && vec[left(i)] > vec[largest])
		{
			// ���� �ڽ� ����� ���� ����
			largest = left(i);
		}

		// ���� ����� ������ �ڽ� ��尡 �����ϰ�
		// ������ �ڽ� ����� ���� ���� ��庸�� ū ���
		if (right(i) < vec.size() && vec[right(i)] > vec[largest])
		{
			// ������ �ڽ� ����� ���� ����
			largest = right(i);
		}

		// �ڽ� ����� ������ ����� ���
		if (largest != i)
		{
			// ���� ���� �ڽ� ��带 ��ȯ
			std::swap(vec[i], vec[largest]);

			// �ڽ� ��忡�� �� �۾��� �ݺ�
			heapify_down(largest);
		}
	}

public:
	// ������
	MaxHeap() : vec(1) {}

	// �߰�
	void push(int value)
	{
		// �� �������� ���ο� ���� ���� ��� �߰�
		vec.push_back(value);

		// ���� ������ ���� �θ� ��带 ���� ���Ͽ�
		// �� �Ӽ��� �������� ������ ���� ���� �θ� ��带 ��ȯ
		heapify_up(vec.size() - 1);
	}

	// ����
	void pop()
	{
		// �� �������� �ִ� ���Ҹ� ��Ʈ ���� ����
		vec[1] = vec.back();

		// �� ������ ��� ����
		vec.pop_back();

		// ��Ʈ ���� �� �ڽ� ��带 ���Ͽ�
		// �� �Ӽ��� �������� ������ �� �ڽ� ��� �߿��� �� ū(�ִ� ��) ���� ��ȯ
		heapify_down(1);
	}

	// ��� ��� ����
	void clear() { vec.clear(); vec.push_back(0); }

	// ��Ʈ ����� �ε���
	int top() const { return vec[1]; }

	// ������ ����
	int size() { return  vec.size() - 1; }

	// ���� ������� Ȯ��
	bool empty() { return  vec.size() == 1; }
};