//Найти все простые числа в диапазоне [2..n] за O(n).

#include <iostream>

int Eratosfen_line(int n, int*& prime) 
{
	int* min_devisor = new int[n + 1]; //массив для минимальных пр. делителей
	for (int i = 0; i <= n; ++i)
		min_devisor[i] = 0;
	int count_prime_number = 0; //количество простых чисел
	for (int i = 2; i <= n; i++) 
	{
		if (min_devisor[i] == 0) 
		{
			min_devisor[i] = i;
			prime[count_prime_number] = i; //запоминаем простое число
			++count_prime_number;
		}
		for (int k = 0; k < count_prime_number && prime[k] <= min_devisor[i] && i * prime[k] <= n; k++)
		{
			min_devisor[i * prime[k]] = prime[k];
		}

	}
	delete[] min_devisor;
	return count_prime_number;
}


int main() {
	int N;
	std::cin >> N;
	int* prime = new int[N + 1];
	int count_prime = Eratosfen_line(N, prime);
	for (int i = 0; i < count_prime; i++) {
		std::cout << prime[i] << " ";
	}
	delete[] prime;
	return 0;
}

