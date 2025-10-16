#include "RPN.hpp"

Rpn::Rpn(void)
{}

Rpn::Rpn(std::string input)
{
	startCalculation(input);
	std::cout << list.top() << std::endl;
}

Rpn::Rpn(const Rpn& ref)
{
	*this = ref;
}

Rpn& Rpn::operator= (const Rpn& ref)
{
	(void) ref;
	return (*this);
}

Rpn::~Rpn(void) {}

void Rpn::startCalculation(std::string input)
{
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == ' ')
			continue ;
		if (input[i] >= '0' && input[i] <= '9')
			list.push(input[i] - '0');
		else if (isOperator(input[i]))
			calculate(input[i]);
	}
}

bool	Rpn::isOperator(char i)
{
	char operators[4] = {'+', '-', '*', '/'};

	for (int x = 0; x < 4; x++)
		if (operators[x] == i)
			return (true);
	return (false);
}

void	Rpn::calculate(char i)
{
	int last;

	last = list.top();
	list.pop();
	if (i == '-')
		list.top() -= last;
	else if (i == '+')
		list.top() += last;
	else if (i == '*')
		list.top() *= last;
	else if (i == '/')
		list.top() /= last;
}