#include "PmergeMe.hpp"

bool	isInt(std::string literal)
{
	int		sign = 1;
	long	number = 0;

	if (!literal[0])
		return false;
	for (size_t i = 0; i < literal.length(); i++)
	{
		if (i == 0 && (literal[i] == '+'))
			continue ;
		else if (literal[i] < '0' || literal[i] > '9')
			return false;
		number = (number * 10) + (literal[i] - '0');
	}
	if ((number * sign) > 2147483647 || (number * sign) < -2147483648)
			return false;
	return true;
}

int main(int ac, char** av)
{
	if (ac == 1)
		return 1;
	std::vector<int> numbers;
	std::deque<int> num;
	clock_t timeBefore;
	clock_t timeAfter;
	double checkTime;

	timeBefore = clock();
	for (int i = 1; i < ac; i++)
	{
		if (isInt(av[i]) == false)
		{
			std::cout << "Error" << std::endl;
			return 1;
		}
		numbers.push_back(std::atoi(av[i]));
	}
	std::cout << "Before: ";
	printContainer(numbers);
	PmergeMe ToSorte(numbers);
	timeAfter = clock();
	double timeVector = double(timeAfter - timeBefore) * 1e6 / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << numbers.size() << " elements with std::vector : " << timeVector << " us" << std::endl;

	timeBefore = clock();
	for (int i = 1; i < ac; i++)
		num.push_back(std::atoi(av[i]));
	PmergeMe second(num);
	timeAfter = clock();
	timeVector = double(timeAfter - timeBefore) * 1e6 / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << numbers.size() << " elements with std::deque : " << timeVector << " us" << std::endl;
}