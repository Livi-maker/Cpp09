#pragma once

#include <iostream>
#include <string>
#include <stack>

class Rpn
{
	public:
		Rpn(void);
		Rpn(std::string input);
		Rpn(const Rpn& ref);
		Rpn& operator= (const Rpn& ref);
		~Rpn(void);

	private:
		void	startCalculation(std::string input);
		bool	isOperator(char i);
		void	calculate(char i);
		std::stack<int> list;
};