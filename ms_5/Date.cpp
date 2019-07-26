//Student name: Jiawei Yang
//Student number: 121134183
//email: jyang210@myseneca.ca
//Course section: SAA
//Date: March 28, 2019

#include <iomanip>
#include "Date.h"

namespace ama {
	void Date::status(int newStatus) {
		this->statusOfDate = newStatus;
	}

	int Date::mdays(int year, int mon) const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	Date::Date() {
		this->clearError();
		this->year = 0;
		this->month = 0;
		this->day = 0;
	}

	Date::Date(int year, int month, int day) {
		if (year >= min_year && year <= max_year) {
			if (month >= 1 && month <= 12) {
				if (day >= 1 && day <= this->mdays(year, month)) {
					this->clearError();
					this->year = year;
					this->month = month;
					this->day = day;
				}
				else {
					*this = Date();
					this->status(error_day);
				}
			}
			else {
				*this = Date();
				this->status(error_mon);
			}
		}
		else {
			*this = Date();
			this->status(error_year);
		}
	}

	Date::~Date() {
	}

	int Date::status() {
		return this->statusOfDate;
	}

	void Date::clearError() {
		this->status(no_error);
	}

	bool Date::isGood() {
		return (this->statusOfDate == no_error && this->year != 0 && this->month != 0 && this->day != 0) ? true : false;
	}

	Date& Date::operator+=(int days) {
		Date result = *this;
		if (result.isGood()) {
			result.day += days;
			if (result.day >= 1 && result.day <= result.mdays(result.year, result.month))
				*this = result;
			else
				this->status(error_invalid_operation);
		}
		else {
			this->status(error_invalid_operation);
		}
		return *this;
	}

	Date& Date::operator++() {
		Date result = *this;
		if (result.isGood()) {
			result.day += 1;
			if (result.day >= 1 && result.day <= result.mdays(result.year, result.month))
				*this = result;
			else
				this->status(error_invalid_operation);
		}
		else {
			this->status(error_invalid_operation);
		}
		return *this;
	}

	Date Date::operator++(int) {
		Date result = *this;
		++(*this);
		return result;
	}

	Date Date::operator+(int days) {
		Date result = *this;
		if (result.isGood()) {
			result.day += days;
			if (result.day < 1 || result.day > result.mdays(result.year, result.month)) {
				result = *this;
				result.status(error_invalid_operation);
			}
		}
		else {
			result.status(error_invalid_operation);
		}
		return result;
	}

	bool Date::operator==(const Date& rhs)const {
		return (this->year - rhs.year == 0 && this->month - rhs.month == 0 && this->day - rhs.day == 0) ? true : false;
	}

	bool Date::operator!=(const Date& rhs)const {
		return (!(*this == rhs)) ? true : false;
	}

	bool Date::operator<(const Date& rhs)const {
		int date1 = this->year * 10000 + this->month * 100 + this->day;
		int date2 = rhs.year * 10000 + rhs.month * 100 + rhs.day;
		return (date1 < date2) ? true : false;
	}

	bool Date::operator>(const Date& rhs)const {
		return (!(*this < rhs || *this == rhs)) ? true : false;
	}

	bool Date::operator<=(const Date& rhs)const {
		return (*this < rhs || *this == rhs) ? true : false;
	}

	bool Date::operator>=(const Date& rhs)const {
		return (*this > rhs || *this == rhs) ? true : false;
	}

	std::istream& Date::read(std::istream& is) {
		int year = 0, month = 0, day = 0;
		is >> year;
		is.get();
		is >> month;
		is.get();
		is >> day;
		if (is.fail()) {
			*this = Date();
			this->status(error_input);
		}
		else {
			*this = Date(year, month, day);
		}
		return is;
	}

	std::ostream& Date::write(std::ostream& os)const {
		os << std::setfill('0') << std::setiosflags(std::ios::right) 
			<< std::setw(4) << this->year << "/"
			<< std::setw(2) << this->month << "/"
			<< std::setw(2) << this->day << std::setfill(' ');
		return os;
	}

	std::istream& operator>>(std::istream&is, Date& date) {
		date.read(is);
		return is;
	}

	std::ostream& operator<<(std::ostream& os, const Date& date) {
		date.write(os);
		return os;
	}
}