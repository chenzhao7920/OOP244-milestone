//Student name: Jiawei Yang
//Student number: 121134183
//email: jyang210@myseneca.ca
//Course section: SAA
//Date: March 28, 2019

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "ErrorState.h"

namespace ama {
	ErrorState::ErrorState(const char* errorMessage) {
		this->errorMessage = nullptr;
		*this = errorMessage;
	}

	ErrorState::~ErrorState() {
		if (this->errorMessage != nullptr) {
			delete[] this->errorMessage;
		}
	}

	ErrorState::operator bool() const {
		return this->message() == nullptr ? false : true;
	}

	ErrorState& ErrorState::operator=(const char* pText) {
		if (this->errorMessage != nullptr) {
			delete[] this->errorMessage;
			this->errorMessage = nullptr;
		}
		if (pText != nullptr && *pText != '\0') {
			int length = strlen(pText);
			this->errorMessage = new (std::nothrow) char[length + 1];
			if (this->errorMessage != nullptr) {
				strncpy(this->errorMessage, pText, length);
				this->errorMessage[length] = '\0';
			}
		}
		return *this;
	}

	void ErrorState::message(const char* pText) {
		*this = pText;
	}

	const char* ErrorState::message() const {
		return this->errorMessage;
	}

	std::ostream& operator<<(std::ostream& os, const ErrorState& errorState) {
		if (errorState) {
			os << errorState.message();
		}
		else {
			os << "";
		}
		return os;
	}
}
