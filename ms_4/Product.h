//student name:Chen Zhao
//student Id:120122189
//Section:SAA
#ifndef AMA_PCH_H
#define AMA_PCH_H
#include "iProduct.h"
#include "ErrorState.h"
#include <iostream>
namespace ama {
	
	class Product : public iProduct
	{
		const char Type;  //const  character
		char Sku[max_length_sku + 1];
		char Unit[max_length_unit + 1];
		char * PName;
		int QtyHand;
		int QtyNeed;
		double Price;
		bool Taxable;
		ErrorState error;
	protected:
		void message(const char* pText);
		bool isClear() const;
	public:
		Product(const char type = 'N');
		Product(const char* sku, const char* pname, const char* unit, double price = 0.0f, int qtyneed = 0, int qtyhand = 0, bool tax = true);
		Product(const Product& other);
		~Product();
		Product& operator= (const Product& other);
		int operator+=(int cnt);
		bool operator==(const char* sku) const;
		bool operator> (const char* sku) const;
		bool operator>(const iProduct& other) const;
		int qtyAvailable() const;
		int qtyNeeded() const;
		double total_cost() const;
		bool isEmpty() const;
		std::istream& read(std::istream& in, bool interractive);
		std::ostream& write(std::ostream& out, int writeMode) const;
		//need to implement one more function
		const char* name() const;
	};
}
#endif //PCH_H

