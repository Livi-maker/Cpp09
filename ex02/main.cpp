#include "PmergeMe.hpp"

int main(int ac, char** av)
{
	if (ac == 1)
		return 1;
	std::vector<int> numbers;
	std::deque<int> num;
	clock_t timeBefore;
	clock_t timeAfter;

	timeBefore = clock();
	for (int i = 1; i < ac; i++)
		numbers.push_back(std::atoi(av[i]));
	std::cout << "Before: ";
	printContainer(numbers);
	PmergeMe ToSorte(numbers);
	timeAfter = clock();
	std::cout << "Time to process a range of " << numbers.size() << " elements with std::vector : " << timeAfter - timeBefore<< " us" << std::endl;
	for (size_t i = 0; i < numbers.size(); i++)
		num.push_back(numbers[i]);
	timeBefore = clock();
	std::cout << "Time to process a range of " << numbers.size() << " elements with std::deque : " << timeBefore - timeAfter << " us" << std::endl;
}