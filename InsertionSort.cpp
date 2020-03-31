#include <iostream>
void print(int* arr, int l, int r)
{
	for (int i = l; i <= r; ++i)
		std::cout << arr[i] << " ";//"[" << i << "] = " << 
	std::cout << std::endl;
}

template <class T>
void InsertionSort(T* arr, int l, int r)
{
	for (int i = l + 2; i <= r ; ++i)
	{
		int j = i;
		T temp = arr[i];
		while (j > 0 && temp > arr[j - 1])
		{
			arr[j] = arr[j - 1];
			--j;
		}
		arr[j] = temp;
	}
}

int main()
{
	int arr[10] = { 5, 19, 1, 4, 7, 10, 6, 17, 77, 8 };
	print(arr, 0, 9);
	InsertionSort(arr, 0, 9);
	print(arr, 0, 9);
	return 0;
}