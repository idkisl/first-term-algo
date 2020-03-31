#include <iostream>
void print(int* arr, int l, int r)
{
	for (int i = l; i <= r; ++i)
		std::cout << arr[i] << " ";//"[" << i << "] = " << 
	std::cout << std::endl;
}

void heapifyDown(int* arr, int l, int r, int k)
{
	if (2 * k + 1 <= r && arr[k] < arr[2 * k + 1] && (arr[2 * k + 1] > arr[2 * k + 2] || 2*k + 2  > r))
	{
		//std::cout << "swap [" << arr[k] << "," << arr[(k - 1) / 2] << "]" << std::endl;
		std::swap(arr[k], arr[2 * k + 1]);
		k = 2 * k + 1;
		heapifyDown(arr, l, r, k);
	} else if (2 * k + 2 <= r && arr[k] < arr[2 * k + 2])
	{
		//std::cout << "swap [" << arr[k] << "," << arr[(k - 1) / 2] << "]" << std::endl;
		std::swap(arr[k], arr[2 * k + 2]);
		k = 2 * k + 2;
		heapifyDown(arr, l, r, k);
	}
}

void BuildHeap(int* arr, int l, int r)
{
	for (int i = r; i >= l; --i)
	{
		heapifyDown(arr, l, r, i);
		//print(arr, 0, 9);
	}
}

void HeapSort(int* arr, int l, int r)
{
	BuildHeap(arr, l, r);
	//std::cout << "Our Heap : ";
	//print(arr, l, r);
	while (l != r)
	{
		std::swap(arr[0], arr[r]);
		--r;
		//print(arr, l, r);
		heapifyDown(arr, l, r, l);
		//print(arr, l, r);
	}
}

int main()
{
	
	int arr[10] = { 17, 18,8,7,9,13,14,44,0,6 };
	print(arr, 0, 9);
	HeapSort(arr, 0, 9);
	print(arr, 0, 9);
	return 0;
}