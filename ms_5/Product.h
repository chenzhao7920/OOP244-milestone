//Student name: Jiawei Yang
//Student number: 121134183
//email: jyang210@myseneca.ca
//Course section: SAA
//Date: March 28, 2019

#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H

#include "iProduct.h"
#include "ErrorState.h"
namespace ama {

	class Product : public iProduct {
		const char productType;
		char SKU[max_length_sku + 1];
		char productUnit[max_length_unit + 1];
		char* productName;
		int qtyOnHand;
		int qtyNeeded;
		double unitPrice;
		bool taxable;
		ErrorState error;

	protected:
		void message(const char*);
		bool isClear() const;

	public:
		Product(const char Type = 'N');
		Product(const char*, const char*, const char*, double = 0, int = 0, int = 0, bool = true);
		Product(const Product&);
		~Product();
		Product& operator=(const Product&);
		int operator+=(int);
		bool operator==(const char*) const;
		bool operator> (const char*) const;
		bool operator>(const iProduct&) const;
		int qtyAvailable() const;
		int qtyRequired() const;
		double total_cost() const;
		bool isEmpty() const;
		std::istream& read(std::istream&, bool);
		std::ostream& write(std::ostream&, int) const;
		const char* name() const;
		const ErrorState& errorMessage()const;
	};
}
#endif