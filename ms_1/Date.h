//student name: Chen Zhao
//student Id: 120122189
//Section: SAA
#ifndef _DATE_H_AMA_
#define _DATE_H_AMA_
#include <iostream>

using namespace std;
namespace ama {
	const int min_year = 2019;
	const int max_year = 2028;
	const int no_error = 0;
	const int error_year = 1;
	const int error_mon = 2;
	const int error_day = 3;
	const int error_invalid_operation = 4;
	const int error_input = 5;

	class Date
	{
	private:
		int Year;
		int Month;
		int DayOfTheMonth;
		int State;
		 
		void status(int newStatus);
		int mdays(int year, int month) const;
		void set(int, int, int);
		Date& copy(const Date&);
	public:
		Date();
		Date(int, int, int);
	 
		int status() const;
		void clearError();
		bool isGood() const;
		Date& operator+=(int);
		Date& operator++();
		Date operator++(int);
		Date operator+(int days) const;
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;
		istream& read(istream& is);
		ostream& write(std::ostream& os) const;
	};

	std::istream&  operator>> (std::istream&, Date& date);
	std::ostream&  operator<< (std::ostream&, const Date& date);
}
#endif

