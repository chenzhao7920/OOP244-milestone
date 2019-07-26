//Student name: Jiawei Yang
//Student number: 121134183
//email: jyang210@myseneca.ca
//Course section: SAA
//Date: March 28, 2019


#include "Perishable.h"
//#include "ErrorState.h"

namespace ama {
	Perishable::Perishable() : Product('P') {
	}

	std::ostream& Perishable::write(std::ostream& out, int writeMode) const {
		Product::write(out, writeMode);
		if (!(this->Product::errorMessage()) && !(this->isEmpty())) {
			if (writeMode == write_condensed) {
				out << "," << this->date;
			}
			else if (writeMode == write_table) {
				out << " " << this->date << " |";
			}
			else if (writeMode == write_human) {
				out << std::right << std::setw(max_length_label) << "Expiry Date: " << this->date << std::endl;
			}
		}
		return out;
	}

	std::istream& Perishable::read(std::istream& in, bool interractive) {
		Date temDate;
		Product::read(in, interractive);
		if (interractive) {
			std::cout << std::right << std::setw(max_length_label) << "Expiry date (YYYY/MM/DD): " << std::left;
			in >> temDate;
			if (!temDate.isGood()) {
				in.setstate(std::ios::failbit);
				switch (temDate.status()) {
				case error_year: this->message("Invalid Year in Date Entry"); break;
				case error_mon: this->message("Invalid Month in Date Entry"); break;
				case error_day: this->message("Invalid Day in Date Entry"); break;
				case error_input: this->message("Invalid Date Entry"); break;
				}
			}
			else {
				this->date = temDate;
			}
		}
		else {
			in.get();
			temDate.Date::read(in);
			if (!temDate.isGood()) {
				in.setstate(std::ios::failbit);
				switch (temDate.status()) {
				case error_year: this->message("Invalid Year in Date Entry"); break;
				case error_mon: this->message("Invalid Month in Date Entry"); break;
				case error_day: this->message("Invalid Day in Date Entry"); break;
				case error_input: this->message("Invalid Date Entry"); break;
				}
			}
			else {
				this->date = temDate;
			}
		}
		return in;
	}

}