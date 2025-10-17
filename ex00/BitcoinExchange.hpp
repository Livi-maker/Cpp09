#pragma once

#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <cstdlib>
#include <stdexcept>

class BitcoinExchange
{
	public:
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange& ref);
		BitcoinExchange& operator= (const BitcoinExchange& ref);
		~BitcoinExchange(void);
		void	BitcoinPrices(const char* file);

		class	invalidFile: public std::exception
		{
			public:
				const char* what() const throw();
		};

	private:
		std::map<std::string, double> prices;

		void	createDatabase(const char* file);
		void	analyzeDatabase(std::string line);
		void	printPrices(std::string line);
		void	checkDate(std::string line);
		void	checkValue(std::string value);
		void	actualPrice(std::string date, double value);
		int		isIntLiteral(std::string line);
		bool	rightFormatValue(std::string literal);
		bool	validDate(int year, int month, int day);
};