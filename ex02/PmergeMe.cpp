#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{}

PmergeMe::PmergeMe(std::vector<int> numbers)
{
	std::vector<int> jacobsthal = JacobsthalNumbers(numbers.size() / 2);
	mergeInsertion(numbers, jacobsthal);
	std::cout << "After: ";
	printContainer(ordered);
}

PmergeMe::PmergeMe(std::deque<int> numbers)
{
	std::vector<int> jacobsthal = JacobsthalNumbers(numbers.size() / 2);
	mergeInsertion(numbers, jacobsthal);
}

void	PmergeMe::mergeInsertion(std::vector<int> numbers, std::vector<int> jacobsthal)
{
	std::vector<int> max;
	std::vector<int> min;
	std::vector<int>::iterator it;

	if (numbers.size() == 1)
	{
		ordered.push_back(numbers.front());
		return ;
	}
	for (it = numbers.begin(); it < numbers.end(); it += 2)
	{
		if (it == numbers.end() - 1)
			min.push_back(*it);
		else if (*it < *(it + 1))
		{
			min.push_back(*it);
			max.push_back(*(it + 1));
		}
		else
		{
			min.push_back(*(it + 1));
			max.push_back(*it);
		}
	}
	mergeInsertion(max, jacobsthal);
	insert(min, jacobsthal);
}

void	PmergeMe::mergeInsertion(std::deque<int> numbers, std::vector<int> jacobsthal)
{
	std::deque<int> max;
	std::deque<int> min;
	std::deque<int>::iterator it;

	if (numbers.size() == 1)
	{
		order.push_back(numbers.front());
		return ;
	}
	for (it = numbers.begin(); it < numbers.end(); it += 2)
	{
		if (it == numbers.end() - 1)
			min.push_back(*it);
		else if (*it < *(it + 1))
		{
			min.push_back(*it);
			max.push_back(*(it + 1));
		}
		else
		{
			min.push_back(*(it + 1));
			max.push_back(*it);
		}
	}
	mergeInsertion(max, jacobsthal);
	insert(min, jacobsthal);
}

void	PmergeMe::insert(std::vector<int> min, std::vector<int> jacobsthal)
{
	std::vector<int>::iterator it;

	it = jacobsthal.begin();
	while (it + 1 != jacobsthal.end() && *(it + 1) < (int)min.size())
	{
		binarySearch(min, (*it) - 1, (*(it+1)) - 1);
		it++;
	}
	if (min.size() > 3)
		binarySearch(min, *it, min.size() - 1);
	else
		binarySearch(min, (*it) - 1, min.size() - 1);
}

void	PmergeMe::binarySearch(std::vector<int> min, int jac1, int jac2)
{
	std::vector<int>::iterator it;

	while (jac2 >= jac1)
	{
		it = std::lower_bound(ordered.begin(), ordered.end(), min[jac2]);
		ordered.insert(it, min[jac2]);
		jac2--;
	}
}

void	PmergeMe::insert(std::deque<int> min, std::vector<int> jacobsthal)
{
	std::vector<int>::iterator it;

	it = jacobsthal.begin();
	while (it + 1 != jacobsthal.end() && *(it + 1) < (int)min.size())
	{
		binarySearch(min, (*it) - 1, (*(it+1)) - 1);
		it++;
	}
	if (min.size() > 3)
		binarySearch(min, *it, min.size() - 1);
	else
		binarySearch(min, (*it) - 1, min.size() - 1);
}

void	PmergeMe::binarySearch(std::deque<int> min, int jac1, int jac2)
{
	std::deque<int>::iterator it;

	while (jac2 >= jac1)
	{
		it = std::lower_bound(order.begin(), order.end(), min[jac2]);
		order.insert(it, min[jac2]);
		jac2--;
	}
}

std::vector<int> PmergeMe::JacobsthalNumbers(int size)
{
	std::vector<int> numbers;
	std::vector<int>::iterator it;

	numbers.push_back(1);
	numbers.push_back(3);
	it = numbers.end() - 1;
	while (*it < size)
	{
		numbers.push_back(*it + *(it - 1) * 2);
		it = numbers.end() - 1;
	}
	return numbers;
}

PmergeMe::PmergeMe(const PmergeMe& ref)
{
	*this = ref;
}

PmergeMe& PmergeMe::operator= (const PmergeMe& ref)
{
	(void) ref;
	return (*this);
}

PmergeMe::~PmergeMe(void)
{}
