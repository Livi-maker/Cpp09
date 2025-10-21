#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>

template <typename T>
void printContainer(T& container)
{
	for (size_t i = 0; i < container.size(); i++)
		std::cout << container[i] << " ";
	std::cout << std::endl;
}

class PmergeMe
{
	public:
		PmergeMe(void);
		PmergeMe(const PmergeMe& ref);
		PmergeMe(std::vector<int> numbers);
		PmergeMe(std::deque<int> numbers);
		PmergeMe& operator= (const PmergeMe& ref);
		~PmergeMe(void);

	private:
		std::vector<int> ordered;
		std::deque<int> order;
		void	mergeInsertion(std::vector<int> numbers);
		void	mergeInsertion(std::deque<int> numbers);
		void	insert(std::vector<int> min);
		void	insert(std::deque<int> min);
};