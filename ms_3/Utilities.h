//student name:Chen Zhao
//student Id:120122189
//Section:SAA
#ifndef AMA_UTILITIES_H
#define AMA_UTILITIES_H
#include "Product.h"
#include "ErrorState.h"

namespace ama {
	double& operator+=(double& total, const Product& prod);
	ostream& operator<<(ostream& out, const Product& prod);
	istream& operator>>(istream& in, Product& prod);
}
#endif
