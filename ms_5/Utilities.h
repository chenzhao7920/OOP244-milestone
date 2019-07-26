//Student name: Jiawei Yang
//Student number: 121134183
//email: jyang210@myseneca.ca
//Course section: SAA
//Date: March 28, 2019

#ifndef AMA_UTILITIES_H
#define AMA_UTILITIES_H

#include "iProduct.h"
#include "Product.h"
#include "Perishable.h"

namespace ama {
	double& operator+=(double&, const iProduct&);
	std::ostream& operator<<(std::ostream&, const iProduct&);
	std::istream& operator>>(std::istream&, iProduct&);
	iProduct* createInstance(char);
}

#endif