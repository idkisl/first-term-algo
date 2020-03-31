#include <iostream>
#include <string.h>
using namespace std;
void PrintBin(long long a)
{
	int size = sizeof(long long) * 8;

	for (int i = size - 1; i >= 0; i--)
	{
		if ((a & ((long long)1 << i)) != 0)
		{
			std::cout << 1;
		}
		else
		{
			std::cout << 0;
		}
		if (i % 8 == 0)
		{
			std::cout << " ";
		}
	}
}

template <typename T>
void print(T* arr, int l, int r)
{
	for (int i = l; i <= r; ++i)
		std::cout << arr[i] << " ";//"[" << i << "] = " << 
	std::cout << std::endl;
}

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

template <class T>
int GetDigit(T a, int r)
{
	return (a >> r * 2) & 3;
}

template <class T>
void MSDSort(T*& arr, int l, int r, int operation = (sizeof(T) * 4) - 1)
{
	if (operation < 0 || l >= r)
	{
		return;
	}
	int max = 3; // 00 01 10 11
	int* count = new int[max + 1];
	int* count_copy = new int[max + 1];
	memset(count, 0, (max + 1) * sizeof(int));
	int bin_element;
	for (int i = l; i <= r; ++i)
	{
		bin_element = GetDigit(arr[i],operation);
		++count[bin_element];
	}
	--count[0];
	count_copy[0] = count[0];
	for (int i = 1; i <= max; ++i)
	{
		count[i] += count[i - 1];
		count_copy[i] = count[i];
	}
	print(count, 0, max);
	T* b = new T[r - l + 1];
	memcpy(b, arr + l, (r - l + 1)* sizeof(T));
	for (int i = r; i >= l; --i)
	{
		bin_element = GetDigit(arr[i], operation);
		b[count[bin_element]] = arr[i];
		--count[bin_element];
	}
	memcpy(arr + l, b, (r - l + 1) * sizeof(T));
	delete[] b;
	int start = l;
	for (int h = 0; h < 4; ++h)
	{
		if (count_copy[h] == -1)
			continue;
		int finish = count_copy[h] + l;
		MSDSort(arr, start, finish, operation - 1);
		start = finish + 1;
	}
	delete[] count;
	delete[] count_copy;
}

bool check(long long* arr, int l, int r)
{
	for (int i = l; i < r; ++i)
		if (arr[i] > arr[i + 1])
			return false;
	return true;
}

int main()
{
	long long a = 10;
	int M = 1000;
	std::cin >> M;
	long long* arr = new long long[M];
	for (int i = 0; i < M; ++i)
	{
		std::cin >> arr[i];
	}
	//for (int i = 0; i < M; ++i)
	//{
	//	arr[i] = ((long long)rand())<< 48;
	//	arr[i] += ((long long)rand()) << 32;
	//	arr[i] += ((long long)rand()) << 16;
	//	arr[i] += ((long long)rand());
	//}
	for (int i = 0; i < M; ++i)
	{
		PrintBin(arr[i]);
		std::cout <<" : " <<arr[i] << std::endl;
	}
	print(arr, 0, M-1);
	MSDSort(arr, 0, M - 1);
	print(arr, 0, M - 1);

	std::cout << "\n";
	for (int i = 0; i < M; ++i)
	{
		PrintBin(arr[i]);
		std::cout << " : " << arr[i] << std::endl;
	}
	std::cout << check(arr, 0, M-1);
	delete[] arr;
	/*
	long long a = 12;
	int r = 1;
	int b = (a >> r * 2) & 3;
	PrintBin(a);
	cout << b;
	*/
}
