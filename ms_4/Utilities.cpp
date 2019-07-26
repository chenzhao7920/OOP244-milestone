//student name:Chen Zhao
//student Id:120122189
//Section:SAA
#include <iostream> 
#include "Utilities.h"

namespace ama {
	double& operator+=(double& total, const iProduct& prod) {
		double add;
		add = prod.total_cost();
		total += add;
		return total;
	}
	ostream& operator<<(ostream& out, const iProduct& prod) {
		prod.write(out, write_human);
		return out;
	}
	istream& operator>>(istream& in, iProduct& prod) {
		prod.read(in, true);
		return in;
	}
	iProduct* createInstance(char tag) {
		iProduct * product = nullptr;
		if (tag == 'N' || tag == 'n') {
			 
			product = new Product();
		}
		 
		return product;
	}
}