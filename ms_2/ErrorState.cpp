//student name:Chen Zhao
//student Id:120122189
//Section:SAA
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "ErrorState.h"

using namespace std;
namespace ama {

    //private function
	//set function, dynamic allocate memory for name array
	void ErrorState::set(const char* errorMessage) {
		 
		bool valid = (errorMessage != nullptr && strlen(errorMessage) != 0);
		if (valid) {
			ErrorStr = nullptr;
			ErrorStr = new(nothrow) char[strlen(errorMessage) + 1];
			strcpy(ErrorStr, errorMessage);
			ErrorStr[strlen(errorMessage)] = '\0';

		}
		else {
			ErrorStr = nullptr;
		}
	}

	
    //public functions

	//one or zero constructor
	ErrorState::ErrorState(const char* errorMessage) {
	
		set(errorMessage);
	}

	//destrutor to de-allocate dynamic memory
	ErrorState::~ErrorState() {
		delete[] ErrorStr;
		ErrorStr = nullptr;
	}

	//bool function to teturn the status if status is valid (not in empty sate)
	ErrorState::operator bool() const {
		bool valid = (ErrorStr != nullptr && strlen(ErrorStr) != 0);
		return valid;
	}

	//store the pText to Errorstr, like a constructor, overload assignment operator, attention !!!no memory leaks
	ErrorState& ErrorState::operator = (const char* pText) {
		bool valid = (pText != nullptr && strlen(pText) != 0);
		if (valid) {
			delete[] ErrorStr;
			ErrorStr = nullptr;
			set(pText);
		}
		else {
			set(nullptr);
		}
		return *this;
	}

	//store the pText to Errorstr, like a constructor 
	void ErrorState::message(const char* pText) {
		bool valid = (pText != nullptr && strlen(pText) != 0);
		if (valid) {
			delete [] ErrorStr;
			ErrorStr = nullptr;
			set(pText);
		}
		else {
			set(nullptr);
		}
	}

	//return the address of the Errorstr 
	const char* ErrorState::message() const {
 
	//	return (ErrorStr != nullptr) ? ErrorStr : nullptr;
		return ErrorStr;
	} 

	//helper function, pr
	std::ostream&  operator<<(std::ostream& os, const ErrorState& error) {
		if (error.message() == nullptr)
			os << "";
		else
			os << error.message();
		return os;
	}
}