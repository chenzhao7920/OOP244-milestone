//student name: Chen Zhao
//student Id: 120122189
//Section: SAA
#include <iostream>
#include "Date.h"
namespace ama {
	    //private member function

	    void Date::status(int newStatus) {
			State = newStatus;
	    }

	    int Date::mdays(int year, int mon) const {
			int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
			int month = mon >= 1 && mon <= 12 ? mon : 13;
			month--;
			return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
		}
		 
		void Date::set(int y_, int m_, int d_) {
			//set the status first
			if (y_ == 0 && m_ == 0 && d_ == 0)
				this->status(no_error);
			else if (y_ >= min_year && y_ <= max_year && m_ >= 1 && m_ <= 12 && d_ >= 1 && d_ <= mdays(y_, m_))
				this->status(no_error);
			else if (y_ <= min_year || y_ >= max_year)
				this->status(error_year);
			else if (m_ < 1 || m_ > 12)
				this->status(error_mon);
			else if (d_ < 1 || d_ > mdays(y_, m_))
				this->status(error_day);
			//set current object's data member
			bool valid = (y_ >= 0 && m_ >= 0 && d_ >= 0);
			if (valid ) {
				Year = y_;
				Month = m_;
				DayOfTheMonth = d_;	
			}
			else {
				Year = 0;
				Month = 0;
				DayOfTheMonth = 0;
			}
		}

		Date& Date::copy(const Date& d_) {
			Year = d_.Year;
			Month = d_.Month;
			DayOfTheMonth = d_.DayOfTheMonth;
			State = d_.State;
			return *this;
		};

		//public member function
		//default constructor
		Date::Date() {
			set(0, 0, 0);
		}
		// three parameter constructor
	    Date::Date(int y_, int m_, int d_) {
			set(y_, m_, d_);
		}
		//status function
	    int Date::status() const{
			return State;
		}
		//clearError function
		void Date::clearError() {
			this->status(no_error);
		}
		//isGood function
		bool Date::isGood() const {
			bool valid = (status() == no_error && Year >= min_year && Year <= max_year && Month >= 1 && Month <= 12 && DayOfTheMonth >= 1 && DayOfTheMonth <= mdays(Year, Month));
			return valid;
		};
		//operator +=
		Date& Date::operator+=(int days) {

			if ((this->isGood()) == true) {
				if ((DayOfTheMonth + days) <= mdays(Year, Month) && (DayOfTheMonth + days) >= 1) {
					DayOfTheMonth += days;
				}
				else {
					this->status(error_invalid_operation);
				}	   
			}
			else {
				this->status(error_invalid_operation);
			}

			 
			return *this;
			 
		};
		// prefix opetator ++
		Date& Date::operator++() {
			if ((this->isGood()) == true) {
				if ((DayOfTheMonth + 1) <= mdays(Year, Month) && (DayOfTheMonth + 1) >= 1) {
					DayOfTheMonth += 1;
				}
				else {
					this->status(error_invalid_operation);
				}
			}
			else {
				this->status(error_invalid_operation);
			}
			 
			return *this;
		};
		// postfic operator ++
		Date Date::operator++(int) {
			Date d; 
			d.copy(*this);
			++(*this);         
			return d;
		};
		//operator+
		Date Date::operator+(int days) const{
			Date d; 
			d.copy(*this);
			d += days;
		    return d;
			  
		};
		//operator==
		bool Date::operator==(const Date& rhs) const {
			bool eq = (Year == rhs.Year&& Month == rhs.Month && DayOfTheMonth == rhs.DayOfTheMonth);
			return eq;
		};
		//operator!=
		bool Date::operator!=(const Date& rhs) const {
			if (*this == rhs)
				return false;
			else return true;
		};
		//operator<
		bool Date::operator<(const Date& rhs) const {
			bool lt;
			lt = (!(Year > rhs.Year))? true : false;
			if (lt) {
				lt = (!(Month > rhs.Month)) ? true : false;
				if(lt)
					lt=(!(DayOfTheMonth>=rhs.DayOfTheMonth))? true : false;
			}
			return lt;	 
		};
		//operator>
		bool Date::operator>(const Date& rhs) const {
			bool gt = true;
			if((*this < rhs)||(*this== rhs))
				gt = false;
			return gt;
		};
		//:operator<=
		bool Date::operator<=(const Date& rhs) const {
			bool le = true;
			if (*this > rhs)
				le = false;
			return le;
		};
		//operator>=
		bool Date::operator>=(const Date& rhs) const {
			bool ge = true;
			if (*this < rhs)
				ge = false;
			return ge;
		};
		//read function  
		std::istream& Date::read(std::istream& is) {
			//create three int variable to store year, month, day.
			int y_, m_, d_;
			//use char c to get charactor
			char c;
			bool valid = true;
			//store the first intiger
			is >> y_;
			if (is.fail()) {
				valid = false;
				this->status(error_year);
			}
			//get one charactor from the buffer
			is.get(c);
			if (is.fail()) {
				valid = false;
				this->status(error_mon);
			}
			//store the second intiger
			is >> m_;
			if (is.fail()) {
				valid = false;
				this->status(error_mon);
			}
			//get one charactor from the buffer
			is.get(c);
			if (is.fail()) {
				valid = false;
				this->status(error_day);
			}
			//store the third intiger
			is >> d_;
			if (is.fail()) {
				valid = false;
				this->status(error_day);
			}

			if (valid) {
				Date temp(y_, m_, d_);
				*this = temp;
			}
			else {
				this->set(0, 0, 0);
				this->status(error_input);	 
			}
			return is;
		}
		//function write
		ostream& Date::write(std::ostream& os) const {
			bool valid=(Year >= min_year && Year <= max_year && Month >= 1 && Month <= 12 && DayOfTheMonth >= 1 && DayOfTheMonth <= mdays(Year, Month));
			if (!(valid)) {
				os << "0000" << "/" << "00" << "/" << "00";
			}
			else {
				os << Year << "/";
				os.width(2);
				os.fill('0');
				cout.setf(ios::right);
				os << Month << "/"; 
				os.width(2);
				os.fill('0');
				os << DayOfTheMonth;
				os.fill(' ');
		

			}
			return os;
		};
		//helper functions
		//function  operator>>
		std::istream& operator>>(std::istream& is, ama::Date& s) {
			s.read(is);
			return is;
		}
		//function operator<<
		std::ostream& operator<<(std::ostream& os, const ama::Date& s) {
			s.write(os);
			return os;
		}		 
}