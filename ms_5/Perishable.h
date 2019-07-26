//Student name: Jiawei Yang
//Student number: 121134183
//email: jyang210@myseneca.ca
//Course section: SAA
//Date: March 28, 2019

#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H

#include "Product.h"
#include "Date.h"

namespace ama {
	class Perishable : public Product {
		Date date;

	public:
		Perishable();
		std::ostream& write(std::ostream&, int) const;
		std::istream& read(std::istream&, bool);
	};



}
#endif