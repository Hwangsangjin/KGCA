#include <iostream>

// ¼±Çü Å½»ö
bool linear_search(int data[], int n, int target)
{
	for (size_t i = 0; i < n; i++)
	{
		if (data[i] == target)
		{
			return true;
		}
	}

	return false;
}

// ÀÌÁø Å½»ö
bool binary_search(int data[], int n, int target)
{
	int lower = 0;
	int upper = n - 1;

	while (lower <= upper)
	{
		int mid = (lower + upper) / 2;

		if (data[mid] == target)
		{
			return true;
		}
		else if (data[mid] < target)
		{
			lower = mid + 1;
		}
		else
		{
			upper = mid - 1;
		}
	}

	return false;
}

int main()
{
	int arr[] = { 1, 2, 3, 4, 5 };

	bool finded = linear_search(arr, sizeof(arr) / sizeof(int), 3);
	std::cout << finded << std::endl;

	finded = binary_search(arr, sizeof(arr) / sizeof(int), 3);
	std::cout << finded << std::endl;

	return 0;
}