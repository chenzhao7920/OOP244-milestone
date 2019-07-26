//student name:Chen Zhao
//student Id:120122189
//Section:SAA
#ifndef AMA_UTILITIES_H
#define AMA_UTILITIES_H
#include "iProduct.h"
#include "Product.h"
#include "ErrorState.h"


namespace ama {
	//helper functions
	double& operator+=(double& total, const iProduct& prod);
	ostream& operator<<(ostream& out, const iProduct& prod);
	istream& operator>>(istream& in, iProduct& prod);
    //   why can't make this funciton here???	
	//	iProduct* createInstance(char tag);

}
#endif
