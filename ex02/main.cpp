#include "PmergeMe.hpp"

int main(int ac, char** av)
{
	if (ac == 1)
		return 1;
	std::vector<int> numbers;
	time_t timeBefore;
	time_t timeAfter;

	time(&timeBefore);
	for (int i = 1; i < ac; i++)
		numbers.push_back(std::atoi(av[i]));
	std::cout << "Before: ";
	printContainer(numbers);
	PmergeMe ToSorte(numbers);
	time(&timeAfter);
	std::cout << "Time to process a range of " << numbers.size() << " elements with std::vector : " << timeAfter << " us" << std::endl;
}