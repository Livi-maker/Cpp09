#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
	std::string infile = "data.csv";
	createDatabase(infile.c_str());
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& ref)
{
	*this = ref;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& ref)
{
	this->prices = ref.prices;
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{}

void	BitcoinExchange::createDatabase(const char* file)
{
	std::ifstream infile(file);
	if (infile.is_open() == false)
		throw std::runtime_error("Error => Could not open database");

	std::string line;
	while (std::getline(infile, line))
		analyzeDatabase(line);
}


void	BitcoinExchange::analyzeDatabase(std::string line)
{
	int	comma;

	comma = line.find(",");
	prices[line.substr(0, comma)] = std::strtod(line.substr(comma + 1).c_str(), NULL);
}

void	BitcoinExchange::BitcoinPrices(const char* file)
{
	std::ifstream infile(file);
	if (infile.is_open() == false)
		throw std::runtime_error("Error => Could not open file");
	std::string line;
	while (getline(infile, line))
	{
		try
		{
			printPrices(line);
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

void	BitcoinExchange::printPrices(std::string line)
{
	std::string date;

	if (line == "date | value")
		return ;
	int	pipe;
	double value;

	pipe = line.find("|");
	if (pipe == -1)
		throw std::runtime_error("Error: bad input => " + line);
	date = line.substr(0, pipe);
	value = std::strtod(line.substr(pipe + 1).c_str(), NULL);
	checkDate(date);
	checkValue(value);
	actualPrice(date, value);
}

void	BitcoinExchange::checkDate(std::string date)
{
	int separator1;
	int separator2;
	std::string year;
	std::string month;
	std::string day;

	separator1 = date.find("-");
	if (separator1 == -1)
		throw std::runtime_error("Error: bad input => " + date);
	separator2 = date.find("-", separator1 + 1);
	if (separator2 == -1)
		throw std::runtime_error("Error: bad input => " + date);
	year = date.substr(0, separator1);
	month = date.substr(separator1 + 1, separator2 - (separator1 + 1));
	day = date.substr(separator2 + 1, 2);
	if (isIntLiteral(year) != 1 || isIntLiteral(month) != 1 || isIntLiteral(day) != 1)
		throw std::runtime_error("Error: bad input => " + date);
	if (std::atoi(year.c_str()) < 2008 || std::atoi(month.c_str()) < 1 || std::atoi(month.c_str()) > 12 || std::atoi(day.c_str()) < 1 || std::atoi(day.c_str()) > 31)
		throw	std::runtime_error("Error: bad input => " + date);

}

void	BitcoinExchange::checkValue(double value)
{
	if (value < 0)
		throw std::runtime_error("Error: not a positive number.");
	if (value > 2147483647)
		throw std::runtime_error("Error: too large a number.");
}

void	BitcoinExchange::actualPrice(std::string date, double value)
{
	std::map<std::string, double>::iterator it;

	it = prices.lower_bound(date);
	if (it == prices.end() || (date != it->first && it != prices.begin()))
		it--;
	std::cout << date << " => " << value << " => " << value * it->second << std::endl;
}

int	BitcoinExchange::isIntLiteral(std::string literal)
{
	int		sign = 1;
	long	number = 0;

	if (!literal[0])
		return (0);
	for (size_t i = 0; i < literal.length(); i++)
	{
		if (i == 0 && (literal[i] == '-' || literal[i] == '+'))
		{
			if (literal[i] == '-')
				return (2);
		}
		else if (literal[i] < '0' || literal[i] > '9')
			return (0);
		number = (number * 10) + (literal[i] - '0');
	}
	if ((number * sign) > 2147483647 || (number * sign) < -2147483648)
			return (3);
	return (1);
}