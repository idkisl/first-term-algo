#include <iostream>

void PrintMatrix(uint64_t** arr, int N)
{
	for (int i = 0; i <= N; ++i)
	{
		std::cout << i << " :: ";
		for (int j = 0; j <= N; ++j)
		{
			std::cout << arr[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

uint64_t WidePyramid(int N)
{
	uint64_t** arr = new uint64_t *[N + 1];
	for (int i = 0; i <= N; ++i)
		arr[i] = new uint64_t[N + 1];
	for (int i = 0; i <= N; ++i)
	{
		arr[i][0] = 0;
		arr[0][i] = 1;
	}
	uint64_t s1;
	uint64_t s2;

	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			s1 = arr[i][j - 1];
			if (i < j)
				s2 = 0;
			else
				s2 = arr[i - j][j - 1];
			arr[i][j] = s1 + s2;
		}
	}

	uint64_t s = arr[N][N];

	//удаление массива
	for (int i = 0; i <= N; ++i)
		delete[] arr[i];
	delete[] arr;

	return s;
}

int main()
{
	int N;
	std::cin >> N;
	std::cout << WidePyramid(N);

	return 0;
}