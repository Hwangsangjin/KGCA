#include <iostream>
#include <Queue.h>

using namespace std;

int main()
{
	CircularQueue<int> q(5);
	
	q.enqueue(10);
	q.enqueue(20);
	q.enqueue(30);
	q.enqueue(40);
	q.enqueue(50);
	q.dequeue();
	q.dequeue();
	q.enqueue(60);
	q.enqueue(70);

	q.enqueue(80);
	
	while (!q.empty())
	{
		auto& e = q.front();
		cout << e << " ";
		q.dequeue();
	}
	cout << endl;

	return 0;
}
