//Student name: Jiawei Yang
//Student number: 121134183
//email: jyang210@myseneca.ca
//Course section: SAA
//Date: March 28, 2019

#include "AmaApp.h"

namespace ama {
	AmaApp::AmaApp(const char* filename) {
		strncpy(this->m_filename, filename, 255);
		this->m_filename[255] = '\0';
		*this->m_products = nullptr;
		this->m_noOfProducts = 0;

	}

	AmaApp::~AmaApp() {
		for (int i = 0; i < m_noOfProducts; i++)
		{
			delete[] m_products[i];
		}
	}

	void AmaApp::pause() const {
		std::cout << std::endl << "Press Enter to continue...";
		std::cin.ignore(2000, '\n');
		std::cout << std::endl;
	}

	int AmaApp::menu() const {
		int selection;
		std::cout << "Disaster Aid Supply Management Program" << std::endl
			<< "--------------------------------------" << std::endl
			<< "1- List products" << std::endl
			<< "2- Search product" << std::endl
			<< "3- Add non-perishable product" << std::endl
			<< "4- Add perishable product" << std::endl
			<< "5- Add to product quantity" << std::endl
			<< "6- Delete product" << std::endl
			<< "7- Sort products" << std::endl
			<< "0- Exit program" << std::endl
			<< "> ";
		std::cin >> selection;
		if (std::cin.fail() || selection < 0 || selection > 7) {
			std::cin.clear();
			selection = -1;
		}
		std::cin.ignore(2000, '\n');
		return selection;
	}

	void AmaApp::loadProductRecords() {
		iProduct* product = nullptr;
		char buffer[60] = { '\0' };

		for (int i = 0; i < m_noOfProducts; i++)
		{
			delete[] m_products[i];
		}
		int index = 0;
		std::fstream f(m_filename, std::ios::in);
		if (f.good()) {
			while (!f.eof()) {
				//char tag;
				//f.get(tag);
				//if (tag == 'N' || tag == 'n' || tag == 'P' || tag == 'p') {
				product = createInstance(f.get());
				if (product != nullptr) {
					m_products[index] = product;
					f.get();
					f.getline(buffer, 256, '\n');
					//f.ignore(2000, '\n');
					std::stringstream ss(buffer);
					m_products[index]->read(ss, false);
					index++;
				}
				fflush(stdin);
				//f.ignore();
				//}
			}
		}
		m_noOfProducts = index;
		f.close();
	}

	void AmaApp::saveProductRecords() const {
		if (!std::cin.fail()) {
			std::fstream fout(m_filename, std::ios::out);
			for (int i = 0; i < m_noOfProducts; i++) {
				m_products[i]->write(fout, write_condensed);
				fout << std::endl;
			}
			fout.close();
		}
	}

	void AmaApp::listProducts() const {
		double totalCost = 0;
		std::cout << "------------------------------------------------------------------------------------------------" << std::endl
			<< "| Row |     SKU | Product Name     | Unit       |   Price | Tax |   QtyA |   QtyN | Expiry     |" << std::endl
			<< "|-----|---------|------------------|------------|---------|-----|--------|--------|------------|" << std::endl;
		for (int i = 0; i < m_noOfProducts; i++) {
			std::cout << "|" << std::right << std::setw(4) << i + 1 << " |";
			m_products[i]->write(std::cout, write_table);
			std::cout << std::endl;
			totalCost += *m_products[i];
		}
		std::cout << "------------------------------------------------------------------------------------------------" << std::endl
			<< "|                                                      Total cost of support ($): | " << std::right << std::setw(10) << totalCost << " |" << std::endl
			<< "------------------------------------------------------------------------------------------------" << std::endl;
	}

	iProduct* AmaApp::find(const char* sku) const {
		iProduct* result = nullptr;
		for (int i = 0; i < m_noOfProducts; i++) {
			if (*m_products[i] == sku) {
				result = m_products[i];
			}
		}
		return result;
	}

	void AmaApp::addQty(iProduct* product) {
		int amount;
		//std::cout << product
		product->write(std::cout, write_human);
		std::cout << std::endl << std::endl
			<< "Please enter the number of purchased items: ";
		std::cin >> amount;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(2000, '\n');
			std::cout << "Invalid quantity value!" << std::endl;
		}
		else {
			if (amount > (product->qtyRequired() - product->qtyAvailable())) {
				std::cout << "Too many items; only " << product->qtyRequired() - product->qtyAvailable()
					<< " is needed. Please return the extra "
					<< amount - (product->qtyRequired() - product->qtyAvailable())
					<< " items." << std::endl;
				amount = product->qtyRequired() - product->qtyAvailable();
			}
			*product += amount;
			std::cout << std::endl << "Updated!" << std::endl;
		}
		this->saveProductRecords();
	}

	void AmaApp::addProduct(char tag) {
		iProduct* product = nullptr;
		product = createInstance(tag);
		if (product != nullptr) {
			std::cin >> *product;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(2000, '\n');
				std::cout << std::endl << *product << std::endl << std::endl;
			}
			else {
				this->m_products[this->m_noOfProducts++] = product;
				this->saveProductRecords();
				std::cout << std::endl << "Success!" << std::endl << std::endl;
			}
		}
	}

	int AmaApp::run() {
		bool flag = true;
		this->loadProductRecords();
		do {
			char sku[max_length_sku] = { '\0' };
			switch (this->menu()) {
			case 1:
				this->listProducts();
				this->pause();
				break;
			case 2:
				std::cout << "Please enter the product SKU: ";
				std::cin >> sku;
				std::cin.ignore(2000, '\n');
				if (this->find(sku) != nullptr) {
					std::cout << std::endl;
					this->find(sku)->write(std::cout, write_human);
				}
				else {
					std::cout << std::endl << "No such product!";
				}
				this->pause();
				break;
			case 3:
				this->addProduct('N');
				break;
			case 4:
				this->addProduct('P');
				break;
			case 5:
				std::cout << "Please enter the product SKU: ";
				std::cin >> sku;
				std::cin.ignore(2000, '\n');
				if (this->find(sku) != nullptr) {
					std::cout << std::endl;
					this->addQty(this->find(sku));
				}
				else {
					std::cout << std::endl << "No such product!" << std::endl;
				}
				std::cout << std::endl;
				break;
			case 6:
				break;
			case 7:
				break;
			case 0:
				std::cout << "Goodbye!" << std::endl << std::endl;
				flag = false;
				break;
			default:
				std::cout << "~~~Invalid selection, try again!~~~";
				this->pause();
				break;
			}
		} while (flag);
		return 0;
	}

}