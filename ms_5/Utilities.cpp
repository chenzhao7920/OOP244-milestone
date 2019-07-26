//Student name: Jiawei Yang
//Student number: 121134183
//email: jyang210@myseneca.ca
//Course section: SAA
//Date: March 28, 2019

#include "Utilities.h"

namespace ama {
	double& operator+=(double& total, const iProduct& prod) {
		return total += prod.total_cost();
	}

	std::ostream& operator<<(std::ostream& out, const iProduct& prod) {
		prod.write(out, write_human);
		return out;
	}

	std::istream& operator>>(std::istream& in, iProduct& prod) {
		prod.read(in, true);
		return in;
	}
	iProduct* createInstance(char tag) {
		iProduct* iproduct = nullptr;
		if (tag == 'N' || tag == 'n') {
			iproduct = new Product();
		}
		else if (tag == 'P' || tag == 'p') {
			iproduct = new Perishable();
		}
		return iproduct;
	}
}