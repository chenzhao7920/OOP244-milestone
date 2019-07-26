//Student name: Jiawei Yang
//Student number: 121134183
//email: jyang210@myseneca.ca
//Course section: SAA
//Date: March 28, 2019

#ifndef AMA_DATE_H
#define AMA_DATE_H

#include <iostream>

namespace ama {
	const int min_year = 2019;
	const int max_year = 2028;
	const int no_error = 0;
	const int error_year = 1;
	const int error_mon = 2;
	const int error_day = 3;
	const int error_invalid_operation = 4;
	const int error_input = 5;

	class Date {
		int year;
		int month;
		int day;
		int statusOfDate;

		void status(int);
		int mdays(int, int) const;

	public:
		Date();
		Date(int, int, int);
		~Date();

		int status();
		void clearError();
		bool isGood();
		Date& operator+=(int);
		Date& operator++();
		Date operator++(int);
		Date operator+(int);
		bool operator==(const Date&)const;
		bool operator!=(const Date&)const;
		bool operator<(const Date&)const;
		bool operator>(const Date&)const;
		bool operator<=(const Date&)const;
		bool operator>=(const Date&)const;
		std::istream& read(std::istream&);
		std::ostream& write(std::ostream&)const;
	};
	std::istream& operator>>(std::istream&, Date&);
	std::ostream& operator<<(std::ostream&, const Date&);
}

#endif
