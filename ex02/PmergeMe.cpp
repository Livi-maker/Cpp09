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
	mergeInsertion(numbers);
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

void	PmergeMe::mergeInsertion(std::deque<int> numbers)
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
	mergeInsertion(max);
	insert(min);
}

void	PmergeMe::insert(std::vector<int> min, std::vector<int> jacobsthal)
{
	std::vector<int>::iterator it;

	(void) jacobsthal;
	for (size_t i = 0; i < min.size(); i++)
	{
		for (it = ordered.begin(); it < ordered.end(); it++)
		{
			if (*it > min[i])
			{
				ordered.insert(it, min[i]);
				break ;
			}
		}
		if (it == ordered.end())
			ordered.push_back(min[i]);
	}
}

void	PmergeMe::insert(std::deque<int> min)
{
	std::deque<int>::iterator it;

	for (size_t i = 0; i < min.size(); i++)
	{
		for (it = order.begin(); it < order.end(); it++)
		{
			if (*it > min[i])
			{
				order.insert(it, min[i]);
				break ;
			}
		}
		if (it == order.end())
			ordered.push_back(min[i]);
	}
}

std::vector<int> PmergeMe::JacobsthalNumbers(int size)
{
	std::vector<int> numbers;
	std::vector<int>::iterator it;

	numbers.push_back(0);
	numbers.push_back(1);
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
