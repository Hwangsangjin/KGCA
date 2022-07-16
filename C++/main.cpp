#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> vec1{ 1, 2, 3, 4 };
	cout << vec1.capacity() << ":" << vec1.size() << endl;

	vec1.push_back(5);
	cout << vec1.capacity() << ":" << vec1.size() << endl;

	vec1.push_back(6);
	cout << vec1.capacity() << ":" << vec1.size() << endl;

	vec1.insert(vec1.begin(), 0);
	cout << vec1.capacity() << ":" << vec1.size() << endl;

	vec1.erase(vec1.begin() + 1, vec1.begin() + 3);
	cout << vec1.capacity() << ":" << vec1.size() << endl;

	for (size_t i = 0; i < vec1.size(); i++)
	{
		cout << vec1[i] << ", ";
	}
	cout << endl;
}