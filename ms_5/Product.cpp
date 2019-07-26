//Student name: Jiawei Yang
//Student number: 121134183
//email: jyang210@myseneca.ca
//Course section: SAA
//Date: March 28, 2019

#define _CRT_SECURE_NO_WARNINGS

#include "Product.h"


namespace ama {
	void Product::message(const char* pText) {
		this->error = pText;
	}

	bool Product::isClear() const {
		return this->error.message() == nullptr ? true : false;
	}

	Product::Product(const char type) : productType(type) {
		strcpy(this->SKU, "???");
		strcpy(this->productUnit, "???");
		this->productName = nullptr;
		this->qtyOnHand = 0;
		this->qtyNeeded = 0;
		this->unitPrice = 0;
		this->taxable = true;
	}

	Product::Product(const char* SKU, const char* productName, const char* productUnit,
		double unitPrice, int qtyNeeded, int qtyOnHand, bool taxable) : Product() {
		if (productName != nullptr || *productName != '\0') {
			int length = strlen(productName);
			this->productName = new (std::nothrow) char[length + 1];
			if (this->productName != nullptr) {
				strncpy(this->productName, productName, length);
				this->productName[length] = '\0';
				strncpy(this->SKU, SKU, max_length_sku);
				this->SKU[max_length_sku] = '\0';
				strncpy(this->productUnit, productUnit, max_length_unit);
				this->productUnit[max_length_unit] = '\0';
				this->unitPrice = unitPrice;
				this->qtyNeeded = qtyNeeded;
				this->qtyOnHand = qtyOnHand;
				this->taxable = taxable;
			}
		}
	}

	Product::Product(const Product& rhs) : Product() {
		*this = rhs;
	}

	Product::~Product() {
		if (this->productName != nullptr) {
			delete[] this->productName;
		}
	}

	Product& Product::operator=(const Product& rhs) {
		if (rhs.isEmpty() == false) {
			if (this->productName != nullptr) {
				delete[] this->productName;
				this->productName = nullptr;
			}
			int length = strlen(rhs.productName);
			this->productName = new (std::nothrow) char[length + 1];
			if (this->productName != nullptr) {
				strncpy(this->productName, rhs.productName, length);
				this->productName[length] = '\0';
				strncpy(this->SKU, rhs.SKU, max_length_sku);
				this->SKU[max_length_sku] = '\0';
				strncpy(this->productUnit, rhs.productUnit, max_length_unit);
				this->productUnit[max_length_unit] = '\0';
				this->unitPrice = rhs.unitPrice;
				this->qtyNeeded = rhs.qtyNeeded;
				this->qtyOnHand = rhs.qtyOnHand;
				this->taxable = rhs.taxable;
			}
		}
		return *this;
	}

	int Product::operator+=(int cnt) {
		if (cnt > 0) {
			if (this->isEmpty() == false) {
				this->qtyOnHand += cnt;
			}
		}
		return this->qtyOnHand;
	}

	bool Product::operator==(const char* sku) const {
		return strcmp(this->SKU, sku) == 0 ? true : false;
	}

	bool Product::operator> (const char* sku) const {
		return strcmp(this->SKU, sku) > 0 ? true : false;
	}

	bool Product::operator> (const iProduct& rhs) const {
		return strcmp(this->productName, rhs.name()) > 0 ? true : false;
	}

	int Product::qtyAvailable() const {
		return this->qtyOnHand;
	}

	int Product::qtyRequired() const {
		return this->qtyNeeded;
	}

	double Product::total_cost() const {
		return taxable ? this->unitPrice * this->qtyAvailable() * (1 + tax_rate) : this->unitPrice * this->qtyAvailable();
	}

	bool Product::isEmpty() const {
		return this->productName == nullptr ? true : false;
	}

	std::istream& Product::read(std::istream& in, bool interractive) {
		char sku[max_length_sku] = { '\0' };
		char name[max_length_name] = { '\0' };
		char unit[max_length_unit] = { '\0' };
		char yorn;
		bool taxable, flag = true;
		double price = 0;
		int qtyOnHand = 0, qtyNeeded = 0;
		if (interractive) {
			std::cout << std::right << std::setw(max_length_label) << "Sku: ";
			in >> sku;
			std::cout << std::setw(max_length_label) << "Name (no spaces): ";
			std::cin >> name;
			std::cout << std::setw(max_length_label) << "Unit: ";
			in >> unit;
			std::cout << std::setw(max_length_label) << "Taxed? (y/n): ";
			in >> yorn;
			if (yorn == 'y' || yorn == 'Y') {
				taxable = true;
			}
			else if (yorn == 'n' || yorn == 'N') {
				taxable = false;
			}
			else {
				in.setstate(std::ios::failbit);
				this->message("Only (Y)es or (N)o are acceptable!");
				flag = false;
			}
			if (flag) {
				std::cout << std::setw(max_length_label) << "Price: ";
				in >> price;
				if (price <= 0) {
					in.setstate(std::ios::failbit);
					this->message("Invalid Price Entry!");
					flag = false;
				}
			}
			if (flag) {
				std::cout << std::setw(max_length_label) << "Quantity on hand: ";
				in >> qtyOnHand;
				if (std::cin.fail() || qtyOnHand < 0) {
					in.setstate(std::ios::failbit);
					this->message("Invalid Quantity Available Entry!");
					flag = false;
				}
			}
			if (flag) {
				std::cout << std::setw(max_length_label) << "Quantity needed: " << std::left;
				in >> qtyNeeded;
				if (std::cin.fail() || qtyNeeded < 0) {
					in.setstate(std::ios::failbit);
					this->message("Invalid Quantity Needed Entry!");
				}
			}
		}
		else {
			in.getline(sku, max_length_sku, ',');
			in.getline(name, max_length_name, ',');
			in.getline(unit, max_length_unit, ',');
			in >> price;
			in.get();
			in >> taxable;
			in.get();
			in >> qtyOnHand;
			in.get();
			in >> qtyNeeded;
			if (price <= 0) {
				this->message("Invalid Price Entry!");
			}
			else if (taxable != true && taxable != false) {
				this->message("Only (Y)es or (N)o are acceptable!");
			}
			else if (qtyOnHand < 0) {
				this->message("Invalid Quantity Available Entry!");
			}
			else if (qtyNeeded < 0) {
				this->message("Invalid Quantity Needed Entry!");
			}
		}
		if (!this->error) {
			*this = Product(sku, name, unit, price, qtyNeeded, qtyOnHand, taxable);
		}
		return in;
	}

	std::ostream& Product::write(std::ostream& out, int writeMode) const {
		if (this->error) {
			out << this->error.message();
		}
		else if (!this->isEmpty()) {
			if (writeMode == write_condensed) {
				out << this->productType << "," << this->SKU << "," << this->productName << ","
					<< this->productUnit << "," << std::fixed << std::setprecision(2) << this->unitPrice << ","
					<< this->taxable << "," << this->qtyAvailable() << "," << this->qtyRequired();
			}
			else if (writeMode == write_table) {
				out << " " << std::right << std::setw(max_length_sku) << this->SKU << " | ";
				if (strlen(this->productName) > 16) {
					char tem[14] = { 0 };
					strncpy(tem, this->productName, 13);
					out << std::left << std::setw(13) << tem << "... | ";
				}
				else {
					out << std::left << std::setw(16) << this->productName << " | ";
				}
				out << std::left << std::setw(10) << this->productUnit << " | "
					<< std::right << std::setw(7) << std::fixed << std::setprecision(2) << this->unitPrice << " | "
					<< std::right << std::setw(3);
				if (this->taxable) {
					out << "yes";
				}
				else {
					out << "no";
				}
				out << " | " << std::right << std::setw(6) << this->qtyAvailable() << " | "
					<< std::right << std::setw(6) << this->qtyRequired() << " |" << std::left;
			}
			else if (writeMode == write_human) {
				out << std::right << std::setw(max_length_label) << "Sku: " << this->SKU << std::endl
					<< std::setw(max_length_label) << "Name: " << this->productName << std::endl
					<< std::setw(max_length_label) << "Price: " << std::fixed << std::setprecision(2) << this->unitPrice << std::endl
					<< std::setw(max_length_label) << "Price after Tax: ";
				if (this->taxable) {
					out << this->unitPrice * 1.13;
				}
				else {
					out << this->unitPrice;
				}
				out << std::endl
					<< std::setw(max_length_label) << "Quantity Available: " << this->qtyAvailable() << " " << this->productUnit << std::endl
					<< std::setw(max_length_label) << "Quantity Needed: " << this->qtyRequired() << " " << this->productUnit << std::endl;
			}
		}
		return out;
	}

	const char* Product::name() const {
		return this->productName;
	}

	const ErrorState& Product::errorMessage()const {
		return this->error;
	}
}