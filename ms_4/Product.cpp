//student name:Chen Zhao
//student Id:120122189
//Section:SAA
#define _CRT_SECURE_NO_WARNINGS_
#include <iostream> 
#include <cstring>
#include <iomanip>
#include "Product.h"
#include <sstream>
using namespace std;
namespace ama {
	// protected function
	// receive the address a null-terminated string and store that message in the errorstate object
	void Product::message(const char* pText) {
		//store the pText message to current error data member,
		this->error.message(pText);
	}
	//if no error message return true, otherwise false
	bool Product::isClear() const {
		//error use bool member function, if errorstring is valid, return ture, no error return false
		return (this->error) ? false : true;
	}
	 
	//public 
	// one or no argument constructor
	Product::Product(const char type) :Type(type) {

		Sku[0] = '\0';
		PName = nullptr;
		Unit[0] = '\0';
		Price = 0.0f;
		QtyNeed = 0;
		QtyHand = 0;
		Taxable = true;
	}
	//7 arguments constructor
	Product::Product(const char* sku, const char* pname, const char* unit, double price, int qtyneed, int qtyhand, bool tax) : Product(){
		/*
		ErrorState error;
		set(error.message(), sku, pname, unit, price, qtyneed, qtyhand, tax);
		 */
		
		bool valid(pname != nullptr);
		if (valid) {
			 
			PName = new (nothrow) char[strlen(pname) + 1];
			strcpy(PName, pname);
			strncpy(Sku, sku, max_length_sku);
			Sku[max_length_sku] = '\0';
			strncpy(Unit, unit, max_length_unit);
			Unit[max_length_unit] = '\0';
			Price = price;
			QtyNeed = qtyneed;
			QtyHand = qtyhand;
			Taxable = tax;

		}
		else {

			Sku[0] = '?';
			PName = nullptr;
			Unit[0] = '?';
			Price = 0.0f;
			QtyNeed = 0;
			QtyHand = 0;
			Taxable = false;
		
		}
	}
	//copy constructor
	Product::Product(const Product& other) : Product() {
		PName = nullptr;
		*this = other;
	}
	Product::~Product() {
		delete[] PName;
	}
	Product& Product::operator= (const Product& other)  {
		if (this!= &other) {
			//shallow copy 
			
			strncpy(this->Sku, other.Sku, max_length_sku);
			Sku[max_length_sku] = '\0';
			strncpy(this->Unit, other.Unit, max_length_unit);
			Unit[max_length_unit] = '\0';
			Price = other.Price;
			QtyNeed = other.QtyNeed;
			QtyHand = other.QtyHand;
			Taxable = other.Taxable;
			//if error is not empty, copy the message to current object, otherwise do nothing
			if (other.error.message() != nullptr) {
				this->message(other.error.message());
			}
			//deep copy resource data
			if (other.PName != nullptr) {
				char * PName2;
				PName2 = new (nothrow) char[strlen(other.PName) + 1];
				strcpy(PName2, other.PName);
				delete[] PName;
				PName = new (nothrow) char[strlen(other.PName) + 1];
				strcpy(PName, PName2);
				delete[] PName2;
				PName2 = nullptr;
				/*PName = new (nothrow) char[strlen(other.PName) + 1];
				strcpy(PName, other.PName);*/
			}
			else {
				PName = nullptr;
			}
		}
		return *this;
	}
	//function operator+=: add qtyhand, return qtyhand
	int Product::operator+=(int cnt) {
		if (cnt >= 0)
			this->QtyHand += cnt;
		return this->QtyHand;
	}
	//operator == :compare sku string
	bool Product::operator==(const char* sku) const {
		return (strcmp(this->Sku, sku) == 0) ? true : false;
	}
	//sku greater then Sku
	bool Product::operator> (const char* sku) const {
		return (strcmp(this->Sku, sku) > 0) ? true : false;
	}
	//PName greater than prod's name
	bool Product::operator> (const iProduct& prod) const {
		return (strcmp(this->PName, prod.name()) > 0) ? true : false;
	}

	int Product::qtyAvailable() const {
		return this->QtyHand;
	}
	int Product::qtyNeeded() const {
		return this->QtyNeed;
	}
	double Product::total_cost() const {
		double cost;
		if (Taxable)
			cost = Price * (1.00 + tax_rate) * qtyAvailable();
		else
			cost = Price * qtyAvailable();

		return	cost;
	}
	bool Product::isEmpty() const {
		return (PName == nullptr) ? true : false;
	}
	std::istream& Product::read(std::istream& in, bool interractive) {
		char sku_[max_length_sku] = { '\0' };
		char name_[max_length_name] = { '0' };
		char unit_[max_length_unit] = { '0' };
		double price_ = 0.0;
		bool taxable_;
		int qtyhand_ = 0;
		int qtyneed_ = 0;
		char c;
	 
		if (interractive) {
			/*
			cout << setfill(' ') << setw(max_length_label) << right << "Sku: ";
			in >> sku_;
			cout << setw(max_length_label) << "Name (no spaces): ";
			in >> name_;  
			cout << setw(max_length_label) << "Unit: ";
			in >> unit_;
			cout << setw(max_length_label) << "Taxed? (y/n): ";
			in >> c;
			if (c != 'Y' && c != 'y' && c != 'N' && c != 'n') {
				message("Only (Y)es or (N)o are acceptable!");
				in.setstate(std::ios::failbit);
				keep = false;
			}
			else {
				if (c == 'Y' || c == 'y') {
					Taxable = true;
				}
				else if (c == 'N' || c == 'n') {
					Taxable = false;
				}
			}
			if (keep) {
				cout << setw(max_length_label) << "Price: ";
				in >> price_;
				if (in.fail() || Price < 0) {
					message("Invalid Price Entry!");
					keep = false;
				}

			}
			if (keep) {
				cout << setw(max_length_label) << "Quantity on hand: ";
				in >> qtyhand_;
				if (in.fail() || QtyHand < 0) {
					message("Invalid Quantity Available Entry!");
					keep = false;
				}
			}
			if (keep) {
				cout << setw(max_length_label) << "Quantity needed: ";
				in >> QtyNeed;
				if (in.fail() || QtyNeed < 0) {
					message("Invalid Quantity Needed Entry!");
					keep = false;
				}
			}
			 */
			cout << setfill(' ') << setw(max_length_label) << right << "Sku: ";
			in.getline(Sku, max_length_sku, '\n');
			cout << setw(max_length_label) << "Name (no spaces): ";
			//dynamic allocate memory to store the input product name
			PName =nullptr;
			PName = new (nothrow) char[max_length_name+1];
			in.getline(PName, max_length_name, '\n');
			
			cout << setw(max_length_label) << "Unit: ";
			in.getline(Unit, max_length_unit, '\n');
			cout << setw(max_length_label) << "Taxed? (y/n): ";
			in.get(c);

			if (c != 'Y' && c != 'y' && c != 'N' && c != 'n') {
				message("Only (Y)es or (N)o are acceptable!");
				in.setstate(std::ios::failbit);
				
			}
			else {
				if (c == 'Y' || c == 'y') {
					Taxable = true;
				}
				else if (c == 'N' || c == 'n') {
					Taxable = false;
				}
				cout << setw(max_length_label) << "Price: " ;
				in >> Price;
				in.ignore(2000, '\n');
				if (in.fail() || Price < 0) {
					message("Invalid Price Entry!");
				
				}
				else {
					cout << setw(max_length_label) << "Quantity on hand: ";
					in >> QtyHand;
					in.ignore(2000, '\n');
					if (in.fail() || QtyHand < 0) {
						message("Invalid Quantity Available Entry!");
					
					}
					else {
						cout << setw(max_length_label) << "Quantity needed: ";
						in >> QtyNeed;
						in.ignore(2000, '\n');
						if (in.fail() || QtyNeed < 0) {
							message("Invalid Quantity Needed Entry!");
							
						}
					}
				}
			}
		}
		else {
			//make local variable to store each elements 
			
			in.getline(sku_, max_length_sku, ',');
			in.getline(name_, max_length_name, ',');
			in.getline(unit_, max_length_unit, ',');
			in >> price_;
			in.get();
			in >> taxable_;
			in.get();
			in >> qtyhand_;
			in.get();
			in >> qtyneed_;
			if (!this->error)
				*this = Product(sku_, name_, unit_, price_, qtyneed_, qtyhand_, taxable_);
		}

		return in;
	}
	std::ostream& Product::write(std::ostream& out, int writeMode) const {

		if (isClear()) {
			if (!isEmpty()) {
				if (writeMode == write_condensed) {
					out << Type << "," << Sku << "," << PName << "," << Unit << "," << setprecision(2) << Price << "," << (int)Taxable << "," << QtyHand << "," << QtyNeed ;
				}
				if (writeMode == write_table) {
				
					out <<" "<< fixed << setprecision(2) << right << setw(max_length_sku) << Sku << " | ";
					if (strlen(PName) > 16) {
						char tmp[14] = { '\0' };
						strncpy(tmp, PName, 13);
						out << left << setw(13) << tmp << "... | ";
					}
					else {
						out << left << setw(16) << PName << " | ";
					}
						 	 
					out << setw(10) << Unit << " | " 
						<< right << setw(7) << Price << " | ";
					    (Taxable) ? out << "yes | ": out << " no | ";
					out << setw(6) << QtyHand << " | "<< setw(6) << QtyNeed << " |";
				}
				if (writeMode == write_human) {

					out << fixed << setprecision(2)  << right 
						<< setw(max_length_label) << "Sku: " << Sku << "\n"
						<< setw(max_length_label) << "Name: " << PName << "\n"
						<< setw(max_length_label) << "Price: " << Price << "\n"
						<< setw(max_length_label) << "Price after Tax: "  << total_cost() << "\n"
						<< setw(max_length_label) << "Quantity Available: " << QtyHand << " " << Unit << "\n"
						<< setw(max_length_label) << "Quantity Needed: " << QtyNeed << " " << Unit << endl;
				}
			}
			else {
				cout << "";
			}
		}
		else {
			out << error.message();
		}
		return out;
	}
	//add function name
	const char* Product::name() const {
		return this->PName;
	}

}

