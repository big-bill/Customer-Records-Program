#include "AlterRecords.h"
//-----------------------------------------------------------------------------------------------------
//This constructor sets the oldDate and newestDate fields to the same value, which is the value of the date that is in the record currently selected
AlterRecords::AlterRecords(std::string oldDate) {
	
	newDate = "";
	newestDate = this->oldDate = oldDate; 
}
//-----------------------------------------------------------------------------------------------------
void AlterRecords::setNewDate(std::string newDate) {

	this->newDate = newDate;
	findNewestDate();
}
//-----------------------------------------------------------------------------------------------------
void AlterRecords::findNewestDate(){

	//These declaration statements get the month, day, and year in numeric forms of the new and old date
	int oldMonth = std::stoi(oldDate.substr(0, 2));
	int oldDay = std::stoi(oldDate.substr(3, 2));
	int oldYear = std::stoi(oldDate.substr(6));

	int newMonth = std::stoi(newDate.substr(0, 2));
	int newDay = std::stoi(newDate.substr(3, 2));
	int newYear = std::stoi(newDate.substr(6));

	//These if-statements compare the year, month, and day of the date just entered and the date found in the record
	//If none of the if statements executed, then the old date was a more recent date
	if (newYear > oldYear)
		newestDate = newDate;

	else if (newYear == oldYear)
	{
		if (newMonth > oldMonth)
			newestDate = newDate;

		else if (newMonth == oldMonth)
		{
			if (newDay > oldDay)
				newestDate = newDate;
		}
	}
}
//-----------------------------------------------------------------------------------------------------