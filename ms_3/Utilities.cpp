//student name:Chen Zhao
//student Id:120122189
//Section:SAA
#include <iostream> 
#include "Utilities.h"

namespace ama {
	double& operator+=(double& total, const Product& prod) {
		double add;
		add = prod.total_cost() * prod.qtyAvailable();
		total += add;
		return total;
	}
	ostream& operator<<(ostream& out, const Product& prod) {
		prod.write(out, write_human);
		return out;
	}
	istream& operator>>(istream& in, Product& prod) {
		prod.read(in, true);
		return in;
	}
}