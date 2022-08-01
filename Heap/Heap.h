#pragma once

#include <vector>
#include <algorithm>

// 최대 힙
class MaxHeap
{
private:
	// 동적 배열
	std::vector<int> vec;

	// 부모 노드의 인덱스
	int parent(int i) { return i / 2; }
	// 왼쪽 자식 노드의 인덱스
	int left(int i) { return 2 * i; }
	// 오른쪽 자식 노드의 인덱스
	int right(int i) { return 2 * i + 1; }
	
	// 힙 속성을 만족하도록 트리 재구성
	void heapify_up(int i)
	{
		// 루트 노드가 아니고
		// 현재 노드의 값이 부모 노드 보다 큰 경우
		if (i > 1 && vec[i] > vec[parent(i)])
		{
			// 현재 노드와 부모 노드 교환
			std::swap(vec[i], vec[parent(i)]);

			// 부모 노드에서 이 작업을 반복
			heapify_up(parent(i));
		}
	}

	// 힙 속성을 만족하도록 트리 재구성
	void heapify_down(int i)
	{
		// 현재 노드의 번호를 저장
		int largest = i;

		// 현재 노드의 왼쪽 자식 노드가 존재하고
		// 왼쪽 자식 노드의 값이 현재 노드보다 큰 경우
		if (left(i) < vec.size() && vec[left(i)] > vec[largest])
		{
			// 왼쪽 자식 노드의 값을 저장
			largest = left(i);
		}

		// 현재 노드의 오른쪽 자식 노드가 존재하고
		// 오른쪽 자식 노드의 값이 현재 노드보다 큰 경우
		if (right(i) < vec.size() && vec[right(i)] > vec[largest])
		{
			// 오른쪽 자식 노드의 값을 저장
			largest = right(i);
		}

		// 자식 노드의 값으로 변경된 경우
		if (largest != i)
		{
			// 현재 노드와 자식 노드를 교환
			std::swap(vec[i], vec[largest]);

			// 자식 노드에서 이 작업을 반복
			heapify_down(largest);
		}
	}

public:
	// 생성자
	MaxHeap() : vec(1) {}

	// 추가
	void push(int value)
	{
		// 맨 마지막에 새로운 값을 갖는 노드 추가
		vec.push_back(value);

		// 새로 삽입한 노드와 부모 노드를 서로 비교하여
		// 힙 속성을 만족하지 않으면 현재 노드와 부모 노드를 교환
		heapify_up(vec.size() - 1);
	}

	// 삭제
	void pop()
	{
		// 맨 마지막에 있는 원소를 루트 노드로 복사
		vec[1] = vec.back();

		// 맨 마지막 노드 삭제
		vec.pop_back();

		// 루트 노드와 두 자식 노드를 비교하여
		// 힙 속성을 만족하지 않으면 두 자식 노드 중에서 더 큰(최대 힙) 노드와 교환
		heapify_down(1);
	}

	// 모든 노드 삭제
	void clear() { vec.clear(); vec.push_back(0); }

	// 루트 노드의 인덱스
	int top() const { return vec[1]; }

	// 원소의 갯수
	int size() { return  vec.size() - 1; }

	// 힙이 비었는지 확인
	bool empty() { return  vec.size() == 1; }
};