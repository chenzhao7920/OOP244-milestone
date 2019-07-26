//Student name: Jiawei Yang
//Student number: 121134183
//email: jyang210@myseneca.ca
//Course section: SAA
//Date: March 28, 2019
#ifndef AMA_ERRORSTATE_H
#define AMA_ERRORSTATE_H
#include <iostream>

namespace ama {
	class ErrorState {
		char* errorMessage;
	public:
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState&) = delete;
		ErrorState& operator=(const ErrorState&) = delete;
		~ErrorState();
		operator bool() const;
		ErrorState& operator=(const char*);
		void message(const char*);
		const char* message() const;
	};
	std::ostream& operator<<(std::ostream&, const ErrorState&);
}
#endif