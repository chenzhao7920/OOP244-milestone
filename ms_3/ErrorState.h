//student name:Chen Zhao
//student Id:120122189
//Section:SAA
#ifndef _AMA_ERRORSTATE_H_
#define _AMA_ERRORSTATE_H_
#include <iostream>

//name space
using namespace std;
namespace ama {
	class ErrorState
	{

		char * ErrorStr;

	private:
		void set(const char*);

	public:
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState& othre) = delete;
		ErrorState& operator = (const ErrorState& other) = delete;
		~ErrorState();
		operator bool() const;
		ErrorState& operator = (const char* pText);
		void message(const char* pText);
		const char* message() const;
	};

	std::ostream& operator<<(std::ostream& os, const ErrorState& error);


}

#endif
