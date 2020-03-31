//Атлеты
#include <algorithm>
#include <iostream>
#include <vector>

template <class T>
struct Sportsmen
{
	T m; // масса
	T s; // Сила
	void Print()
	{
		std::cout << "m = " << m << " s = " << s << std::endl;
	}
};

template <class T>
struct comparator
{
	bool operator()(const Sportsmen<T>& s1, const Sportsmen<T>& s2)
	{
		if (s1.m < s2.m)
			return true;
		if (s1.m == s2.m && s1.s > s1.s)
			return true;
		return false;
	}
};

template <class T>
int CountLayers(std::vector<Sportsmen<T>> group)
{
	int N = group.size();
	std::sort(group.begin(), group.end(), comparator<T>());
	T all_mass = 0;
	int count_layers = 0;
	for (int i = 0; i < N; ++i)
	{
		if (group[i].s >= all_mass) // нам подходит это спортсмен 
		{
			all_mass += group[i].m;
			++count_layers;
		}
	}
	return count_layers;
}
int main()
{
	std::vector<Sportsmen<int>> group;

	Sportsmen<int> sport;
	while (std::cin >> sport.m >>sport.s)
	{
		group.push_back(sport);
	}
	std::cout << CountLayers<int> (group);

	return 0;
}
/*
Допустим, у нас есть n-1 спортсмен, совместная масса которых all_mass<n - 1> (от n - 1 спортсмена)
Мы выбираем самого легкого и самого слабого спортсмена sportsmen<n>, котрый может поднять всех педыдущих (у него сила >= all_mass<n - 1>)
Допустим, мы выберем любого другого, а не нашего спортсмена. Назовем его sportsmen2<n>, у нас может быть две ситуации:
1) масса (sportsmen<n>) < масса (sportsmen2<n>)
2) масса (sportsmen<n>) == масса (sportsmen2<n>), и при этом сила (sportsmen<n>) <= сила (sportsmen2<n>)

Разберем случаи:
1) Пирамида будет либо такой же высоты(если все последующие, которые могут выдержать sportsmen<n>, могут также выдержать и 
пирамиду с sportsmen2<n>), либо меньшей( если не все смогу выдержать)
2) Высота опять же может быть или такой же, или меньшей высоты. Так как, возможно, человек более сильный может выдержать также
и человека с меньшей силой. В обратную же сторону это точно не сработает.

Второй случай в контесте не проверяется
*/