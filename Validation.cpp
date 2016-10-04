#include "Validation.h"
//-----------------------------------------------------------------------------------------------------
bool Validation::checkState(std::string &state){

	bool flag = false;
	std::string statePostalCode[] = { "AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE", "FL", "GA",
								   	  "HI", "ID", "IL", "IN", "IA", "KS", "KY", "LA", "ME", "MD",
									  "MA", "MI", "MN", "MS", "MO", "MT", "NE", "NV", "NH", "NJ",
									  "NM", "NY", "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC",
									  "SD", "TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY" };

	//checks if the state is only two characters
	if (state.length() != 2)
		return flag;

	//sets the two characters in the state input to uppercase
	state[0] = toupper(state[0]);
	state[1] = toupper(state[1]);

	//steps through each array value and checks if the state input is one of the postal codes
	for (int count = 0; (count < 50 && !flag); count++)
		if (state == statePostalCode[count])
			flag = true;


	return flag;
}
//-----------------------------------------------------------------------------------------------------
bool Validation::checkTelephone(std::string phone){

	//The phone number is in format of ###-###-####
	std::string phoneNumber = phone;
	
	//checks if the phone string is 12 characters long
	if (phoneNumber.length() != 12)
		return false;
	else
	{
		//Steps through each character of the phone number and checks if the valid spots are digits
		for (int count = 0; count <= 11; count++)
		{
			if (count == 3 || count == 7)
				continue;

			if (isdigit(phoneNumber[count]))
				continue;
			else
				return false;
		}

		//Checks if the string contains the dashes in the correct spot
		if (phoneNumber[3] != '-' || phoneNumber[7] != '-')
			return false;


		//Since none of the return statements executed, the phone string is valid
		return true;
	}
}
//-----------------------------------------------------------------------------------------------------
bool Validation::checkDate(std::string dateChosen){

	//The date is the format of MM/DD/YYYY
	std::string date = dateChosen;
	if (date.length() != 10)
		return false;
	else
	{
		for (int count = 0; count <= 9; count++)
		{
			if (count == 2 || count == 5)
				continue;

			if (isdigit(date[count]))
				continue;
			else
				return false;
		}

		//Checks if the string contains the forward slash in the correct spot
		if (date[2] != '/' || date[5] != '/')
			return false;
		
		bool goodDate = false;
		//Now that we know all the characters are following the format, now we need to validate if the date entered is valid.
		//Found this way from: http://stackoverflow.com/questions/28545031/take-input-of-date-in-format-mm-dd-yyyy-and-split-into-3-separate-variables
		int month = std::stoi(date.substr(0, 2));
		int day = std::stoi(date.substr(3, 2));
		int year = std::stoi(date.substr(6));

		switch (month)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (day >= 1 && day <= 31)
				goodDate = true;
			break;
	
		case 4:
		case 6:
		case 9:
		case 11:
			if (day >= 1 && day <= 30)
				goodDate = true;
			break;

		//Since this last case is February, we will check whether or not the entered year is a leap year or not
		case 2:
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
				if (day >= 1 && day <= 29)
					goodDate = true;
			
			else if (day >= 1 && day <= 28)
				goodDate = true;

			break;

		default:
			break;
		}
		return goodDate;
	}
}
//-----------------------------------------------------------------------------------------------------