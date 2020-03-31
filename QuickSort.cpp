#include <fstream>
#include <time.h>
#include <iostream>
#include <ctime>

template <class T>
void InsertionSort(T* arr, int l, int r)
{
	for (int i = l + 2; i <= r; ++i)
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

int FindPivot(int l, int r)
{
	//srand(time(NULL));
	//int Size = r - l;
	//return (rand() % Size + l);
	return (l+r)/2;
	//return l;
}

template <typename T>
void print(T* arr, int l, int r)
{
	for (int i = l; i <= r; ++i)
		std::cout << arr[i] << " ";//"[" << i << "] = " << 
	std::cout << std::endl;
}

template <typename T>
struct IsLess {
	bool operator()(const T& l, const T& r) const
	{
		return l < r;
	}
};

template <class  T>
int Partition(T* arr, int l, int r, int p)
{
	int i = l;
	int j = r;
	T pivot = arr[p];
	while (true)
	{
		while (arr[i] < pivot) ++i;
		while (arr[j] > pivot) --j;
		if (i >= j) return j;
		std::swap(arr[i], arr[j]);
		++i;
		--j;
	}
	return p;
}


template <class T>
void qsort(T* arr, int l, int r)
{
	if (abs(l - r) == 0)
		return;
	if (abs(l - r) <= 14)
	{
		InsertionSort(arr, l, r);
		return;
	}

	int pivot = FindPivot(l, r);
	pivot = Partition(arr, l, r, pivot);
	qsort(arr, l, pivot);
	qsort(arr, pivot + 1, r);
}


int main()
{
	for (int k = 0; k < 5; ++k)
	{
		unsigned int start_time = clock();
		std::ifstream in("text2.txt");
		int N;
		in >> N;
		int* arr = new int[N];
		for (int i = 0; i < N; ++i)
		{
			in >> arr[i];
		}
		in.close();
		qsort(arr, 0, N - 1);
		std::ofstream fout;

		fout.open("text_.txt");
		for (int i = 0; i < N; ++i)
			fout << arr[i] << " ";
		fout.close();
		delete[] arr;
		unsigned int end_time = clock();
		unsigned int search_time = end_time - start_time;
	}
	
	return 0;
}