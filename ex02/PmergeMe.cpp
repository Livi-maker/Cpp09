#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{}

PmergeMe::PmergeMe(std::vector<int> numbers)
{
	mergeInsertion(numbers);
	std::cout << "After: ";
	printContainer(ordered);
}

void	PmergeMe::mergeInsertion(std::vector<int> numbers)
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
	mergeInsertion(max);
	insert(min);
}

void	PmergeMe::insert(std::vector<int> min)
{
	std::vector<int>::iterator it;

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
