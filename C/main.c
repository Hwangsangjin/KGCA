#include <stdio.h>

void InputNums(int* nums);
void PrintNums(int* nums);

int main()
{
	int nums[6];

	InputNums(nums);
	PrintNums(nums);

	return 0;
}

void InputNums(int* nums)
{
	int num = 0;
	int dup = 0;

	for (size_t i = 0; i < 6; i++)
	{
		printf("번호 입력 : ");
		scanf_s("%d", &num);

		for (size_t j = 0; j < i; j++)
		{
			if (num == nums[j])
			{
				dup = 1;
				break;
			}
		}

		if (!dup)
		{
			nums[i] = num;
		}
		else
		{
			printf("같은 번호가 있습니다!\n");
			i--;
		}
	}
}

void PrintNums(int* nums)
{
	printf("로또 번호 : ");

	for (size_t i = 0; i < 6; i++)
	{
		printf("%d ", *(nums + i));
	}
}