#include <iostream>
using namespace std;

struct Stack
{
	int size;
	int top;
	int* data;
};

void Init(Stack* ps, int size);
void Push(Stack* ps, int num);
int Pop(Stack* ps);
void Delete(Stack* ps);

int main(void)
{
	Stack stack;
	int sel, num;

	Init(&stack, 5);

	while (1)
	{
		cout << "> 1.�߰�, 2.����, 0.���� : ";
		cin >> sel;

		if (sel == 0)
		{
			break;
		}

		switch (sel)
		{
		case 1:
			cout << "> ��ȣ �Է� : ";
			cin >> num;
			Push(&stack, num);
			break;
		case 2:
			num = Pop(&stack);
			cout << "> ���� ��ȣ " << num << endl;
			break;
		}
	}

	for (int i = 0; i < stack.top; i++)
	{
		cout << stack.data[i] << " ";
	}

	Delete(&stack);

	return 0;
}

void Init(Stack* ps, int size)
{
	ps->size = size;
	ps->data = (int*)malloc(size * sizeof(int));
	ps->top = 0;
}

void Delete(Stack* ps)
{
	free(ps->data);
}

void Push(Stack* ps, int num)
{
	if (ps->top == ps->size)
	{
		printf("# ������ ��� á���ϴ�!\n");
	}
	else
	{
		ps->data[ps->top] = num;
		ps->top++;
	}
}

int Pop(Stack* ps)
{
	int num;

	if (ps->top == 0)
	{
		printf("# ������ ������ϴ�!\n");
		num = -1;
	}
	else
	{
		(ps->top)--;
		num = ps->data[ps->top];
	}

	return num;
}