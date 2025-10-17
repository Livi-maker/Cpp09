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
	std::string value;

	pipe = line.find("|");
	if (pipe == -1)
		throw std::runtime_error("Error: bad input => " + line);
	date = line.substr(0, pipe - 1);
	value = line.substr(pipe + 1);
	checkDate(date);
	checkValue(value);
	actualPrice(date, std::strtod(value.c_str(), NULL));
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
	day = date.substr(separator2 + 1);
	if (isIntLiteral(year) != 1 || isIntLiteral(month) != 1 || isIntLiteral(day) != 1)
		throw std::runtime_error("Error: bad input => " + date);
	if (validDate(std::atoi(year.c_str()), std::atoi(month.c_str()), std::atoi(day.c_str())) == false)
		throw	std::runtime_error("Error: invalid date => " + date);

}

void	BitcoinExchange::checkValue(std::string value)
{
	double v = std::strtod(value.c_str() + 1, NULL);

	if (v < 0)
		throw std::runtime_error("Error: not a positive number.");
	if (v > 2147483647)
		throw std::runtime_error("Error: too large a number.");
	if (rightFormatValue(value) == false)
		throw std::runtime_error("Error: bad value =>" + value);
}

void	BitcoinExchange::actualPrice(std::string date, double value)
{
	std::map<std::string, double>::iterator it;

	it = prices.lower_bound(date);
	if (it == prices.end() || (date != it->first && it != prices.begin()))
		it--;
	std::cout << date << " => " << value << " => " << value * it->second << std::endl;
}

bool	BitcoinExchange::rightFormatValue(std::string literal)
{
	long	number = 0;

	if (literal[0] != ' ')
		return false;
	for (size_t i = 1; i < literal.length(); i++)
	{
		if ((literal[i] < '0' || literal[i] > '9') && literal[i] != '.')
			return false;
		number = (number * 10) + (literal[i] - '0');
	}
	if (number > 2147483647 || number  < -2147483648)
			return false;
	return true;
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

bool	BitcoinExchange::validDate(int year, int month, int day)
{
	if (year < 2008 || year > 2025 || day < 1 || day > 31 || month < 1 || month > 12)
		return false;
	if (day == 31 && (month == 11 || month == 4 || month == 6 || month == 9))
		return false;
	if (month == 2 && (year % 4) == 0 && day > 29)
		return false;
	if (month == 2 && (year % 4) != 0 && day > 28)
		return false;
	return true;
}