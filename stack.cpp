#include <iostream>
using namespace std;
int* double_stack(int* stack_old, int stack_element, int stack_long)
{
	int* stack = new int[stack_long * 2];
	for (int i = 0; i <= stack_element; ++i)
	{
		stack[i] = stack_old[i];
	}
	delete[] stack_old;
	return stack;
}
int* push_stack(int* stack, int stack_element, int stack_long, int element)
{
	if (stack_element < stack_long)
	{
		stack[stack_element] = element;
		//++stack_element;
	}
	else
	{
		stack = double_stack(stack, stack_element, stack_long);
		stack_long *= 2;
		stack[stack_element] = element;
		//++stack_element;
	}
	return stack;
}
int take_stack(int* stack, int stack_element, int* answer)
{
	if (stack_element > 0)
	{
		answer[0] = stack[stack_element - 1];
		//cout << stack[stack_element - 1] << endl;
		--stack_element;
	}
	else
		answer[0] = -1;
		//cout << -1 << endl;
	return stack_element;
}
int* reverse_stack(int* stack1, int* stack2, int long1, int long_element1)
{
	int* new_stack2 = new int[long1];
	for (int i = 0; i < long_element1; ++i)
	{
		new_stack2[i] = stack1[long_element1 - i - 1];
	}
	delete[] stack2;
	return new_stack2;
}
int* delete_stack(int* stack)
{
	int* new_stack = new int[1];
	delete[] stack;
	return new_stack;
}
struct Stack
{
	int element = 0;
	int llong = 1;
	int* array = new int[1];
};
bool list()
{
	Stack stack1;
	Stack stack2;
	int* answer = new int[1];
	bool main_answer = true;
	int command = 3, element = 0, N;
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		cin >> command >> element;

		if (command == 3)
		{
			stack1.array = push_stack(stack1.array, stack1.element, stack1.llong, element);
			if (stack1.llong == stack1.element)
				stack1.llong *= 2;
			++stack1.element;
		}
		if (command == 2)
		{
			if (stack2.element == 0)
			{
				stack2.array = reverse_stack(stack1.array, stack2.array, stack1.llong, stack1.element);
				stack2.llong = stack1.llong;
				stack2.element = stack1.element;
				stack1.array = delete_stack(stack1.array);
				stack1.llong = 1;
				stack1.element = 0;
			}
			stack2.element = take_stack(stack2.array, stack2.element, answer);
			if (main_answer && answer[0] != element)
				main_answer = false;
		}
	}
	delete[] stack1.array;
	delete[] stack2.array;
	return main_answer;
}

int main()
{
	bool answer;
	answer = list();

	if (answer)
		cout << "YES";
	else
		cout << "NO";
	return 0;
}