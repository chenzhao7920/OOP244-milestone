//Student name: Jiawei Yang
//Student number: 121134183
//email: jyang210@myseneca.ca
//Course section: SAA
//Date: March 28, 2019

#ifndef AMA_IPRODUCT_H
#define AMA_IPRODUCT_H
#include <iostream>
#include <cstring>
#include <iomanip>

namespace ama {
	const int max_length_label = 30;
	const int max_length_sku = 7;
	const int max_length_name = 75;
	const int max_length_unit = 10;
	const int write_condensed = 0;
	const int write_table = 1;
	const int write_human = 2;
	const double tax_rate = 0.13;

	class iProduct {

	public:
		virtual std::ostream& write(std::ostream&, int) const = 0;
		virtual std::istream& read(std::istream&, bool) = 0;
		virtual bool operator==(const char*) const = 0;
		virtual double total_cost() const = 0;
		virtual int qtyRequired() const = 0;
		virtual int qtyAvailable() const = 0;
		virtual const char* name() const = 0;
		virtual int operator+=(int) = 0;
		virtual bool operator>(const iProduct&) const = 0;
		virtual ~iProduct() {};
	};
}
#endif