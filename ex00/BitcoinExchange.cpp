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
	// std::map<std::string, double>::iterator it;
	// for (it = prices.begin(); it != prices.end(); it++)
	// 	std::cout << it->first << " " << it->second << std::endl;
}


void	BitcoinExchange::analyzeDatabase(std::string line)
{
	int	comma;

	comma = line.find(",");
	prices[line.substr(0, comma)] = atof(line.substr(comma + 1).c_str());
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
	long value;

	pipe = line.find("|");
	if (pipe == -1)
		throw std::runtime_error("Error: bad input => " + line);
	date = line.substr(0, pipe);
	value = atof(line.substr(pipe + 1).c_str());
	checkDate(date);
	checkValue(value);
	actualPrice(date, value);
}

void	BitcoinExchange::checkDate(std::string date)
{
	int separator1;
	int separator2;
	int year;
	int month;
	int day;

	separator1 = date.find("-");
	if (separator1 == -1)
		throw std::runtime_error("Error: bad input => " + date);
	separator2 = date.find("-", separator1 + 1);
	if (separator2 == -1)
		throw std::runtime_error("Error: bad input => " + date);
	year = std::atoi(date.substr(0, separator1).c_str());
	month = std::atoi(date.substr(separator1 + 1, separator2).c_str());
	day = std::atoi(date.substr(separator2 + 1).c_str());
	if (year < 2008 || month < 1 || month > 12 || day < 1 || day > 31)
		throw	std::runtime_error("Error: bad input => " + date);

}

void	BitcoinExchange::checkValue(long value)
{
	if (value < 0)
		throw std::runtime_error("Error: not a positive number.");
	if (value > 2147483647)
		throw std::runtime_error("Error: too large a number.");
}

void	BitcoinExchange::actualPrice(std::string date, int value)
{
	std::map<std::string, double>::iterator it;

	it = prices.lower_bound(date);
	if (date != it->first)
		it--;
	std::cout << it->first << std::endl;
	std::cout << date << " => " << value << " => " << value * it->second << std::endl;
}