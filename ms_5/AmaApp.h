//Student name: Jiawei Yang
//Student number: 121134183
//email: jyang210@myseneca.ca
//Course section: SAA
//Date: March 28, 2019

#ifndef AMA_AMAAPP_H
#define AMA_AMAAPP_H
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "iProduct.h"
#include "Utilities.h"
#include "Perishable.h"
#include "Product.h"
namespace ama {
	class AmaApp {
		char m_filename[256];
		iProduct* m_products[100];
		int m_noOfProducts;

		AmaApp(const AmaApp&) = delete;
		AmaApp& operator=(const AmaApp&) = delete;
		void pause() const;
		int menu() const;
		void loadProductRecords();
		void saveProductRecords() const;
		void listProducts() const;
		iProduct* find(const char* sku) const;
		void addQty(iProduct* product);
		void addProduct(char tag);


	public:
		AmaApp(const char*);
		~AmaApp();
		int run();
	};


}
#endif