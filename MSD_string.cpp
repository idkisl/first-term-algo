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
int GetDigit(T a, int r = 0)
{
	return (a >> r) & 1; // берем один бит
}

template <class T>
void BinaryQSort(T* arr, int l, int r, int IndexBit)
{	
	int i = l;
	int j = r;
	int lenght = sizeof(T) * 8;
	if (r <= l || IndexBit >= lenght)
		return;
	while (j != i)
	{
		while (GetDigit(arr[i], lenght - IndexBit - 1) == 0 && (i < j))
		{
			++i;
		}
		while (GetDigit(arr[j], lenght - IndexBit - 1) == 1 && (i < j))
		{
			--j;
		}
		std::swap(arr[i], arr[j]);
	}
	if (GetDigit(arr[r], lenght - IndexBit - 1) == 0)
		++j;
	BinaryQSort(arr, l, j - 1, IndexBit + 1);
	BinaryQSort(arr, j, r, IndexBit + 1);
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
	BinaryQSort(arr, 0, M - 1, 0);
	print(arr, 0, M - 1);
	delete[] arr;
}
