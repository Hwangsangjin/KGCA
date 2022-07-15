#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> v1;
	vector<int> v2(10);
	vector<int> v3(10, 1);
	vector<int> v4{ 10, 20, 30, 40, 50 };

	vector<int> v5(v4);
	vector<int> v6(v4.begin(), v4.begin() + 3);

	for (int i = 0; i < v6.size(); i++)
		cout << v6[i] << endl;

	vector<vector<int>> mat1(2, vector<int>(3, 1));

	vector<vector<int>> mat2
	{
		{1,2,3},
		{4,5,6}
	};

	for (int r = 0; r < mat2.size(); r++)
	{
		for (int c = 0; c < mat2[r].size(); c++)
		{
			cout << mat2[r][c] << ", ";
		}
		cout << endl;
	}

	return 0;
}
