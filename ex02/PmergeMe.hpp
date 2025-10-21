#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
		PmergeMe& operator= (const PmergeMe& ref);
		~PmergeMe(void);

	private:
		std::vector<int> ordered;
		void	mergeInsertion(std::vector<int> numbers);
		void	printMax(void);
		void	insert(std::vector<int> min);
};