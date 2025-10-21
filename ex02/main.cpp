#include "PmergeMe.hpp"

int main(int ac, char** av)
{
	std::vector<int> numbers;

	for (int i = 1; i < ac; i++)
		numbers.push_back(std::atoi(av[i]));
	PmergeMe ToSorte(numbers);
}