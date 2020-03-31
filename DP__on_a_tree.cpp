#include <iostream>
#include <vector>

void DFS(std::vector<std::vector<int>>& matrix, std::vector<int>& depth, std::vector<int>& count_children, int current = 0)
{
	for (unsigned int i = 0; i < matrix[current].size(); ++i)
	{
		depth[matrix[current][i]] = depth[current] + 1; // расстояние от корня до ребенка = он сам + 1
		DFS(matrix, depth, count_children, matrix[current][i]);
		count_children[current] += count_children[matrix[current][i]] + 1;
	}
}

void FindSumm(std::vector<std::vector<int>>& matrix, std::vector<int>& depth, std::vector<int>& count_children, std::vector<int>& count_summ , int current = 0)
{
	for (unsigned int i = 0; i < matrix[current].size(); ++i)
	{
		int count_of_children = count_children[matrix[current][i]] + 1;
		int count_of_non_children = matrix.size() - count_children[matrix[current][i]] - 1;

		count_summ[matrix[current][i]] = count_summ[current] - count_of_children + count_of_non_children;
		FindSumm(matrix, depth, count_children, count_summ, matrix[current][i]);
	}
}

std::vector<int> SearchDistanse(std::vector<std::vector<int>>& matrix, int N)
{
	std::vector<int> depth(N);
	std::vector<int> count_children(N);
	depth[0] = 0;
	DFS(matrix, depth, count_children);

	std::vector<int> count_summ(N);
	count_summ[0] = 0;
	for (int i = 0; i < N; ++i)
		count_summ[0] += depth[i];
	FindSumm(matrix, depth, count_children, count_summ);

	return count_summ;
}


int main()
{
	int N;
	std::cin >> N;
	std::vector<std::vector<int>> matrix (N);

	int a, b;
	for (int i = 0; i < N - 1; ++i)
	{
		std::cin >> a >> b;
		matrix[a].push_back(b);
	}
	std::vector<int> count_summ = SearchDistanse(matrix, N);
	for (int i = 0; i < N; ++i)
		std::cout << count_summ[i] << std::endl;
	return 0;
}