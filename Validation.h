/*
	This class validates the string input of the state, telephone, and date entered when creating a new record.
*/
#ifndef VALIDATION_H 
#define VALIDATION_H 
#include <string>
#include <cctype>

class Validation{
public:
	bool checkState(std::string&);    //This string is passed by reference because we change the state postal code characters to uppercase
	bool checkTelephone(std::string);
	bool checkDate(std::string);
};
#endif
