#include <iostream>
//передать *array,в диапазоне [l,r]
template <class T>
void CountingSort(T*& arr, int l, int r)
{
	T max = arr[r];
	for (int i = l; i <= r; ++i)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	T* count = new T[max + 1];
	memset(count, 0, (max + 1) * sizeof(T));
	for (int i = l; i <= r; ++i)
	{
		++count[arr[i]];
	}
	--count[0];
	for (int i = 1; i <= max; ++i)
	{
		count[i] += count[i - 1];
	}

	T* b = new T[r + 1];
	memset(b, 0, (r + 1) * sizeof(T));
	for (int i = r; i >= l; --i)
	{
		b[count[arr[i]]] = arr[i];
		--count[arr[i]];
	}
	delete[] arr;
	arr = b;
	delete[] count;
}
int main()
{
    std::cout << "Hello World!\n";
}
