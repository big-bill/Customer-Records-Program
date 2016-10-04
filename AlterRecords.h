#ifndef ALTERRECORDS_H 
#define ALTERRECORDS_H
#include <string>

class AlterRecords
{
private:
	std::string oldDate;	   //oldDate holds the value of the date in the record
	std::string newDate;	  //newDate holds the value of the newly entered date, and will be compared to the old date
	std::string newestDate;  //newestDate holds the date of the last payment made to an account. 
public:
	//This constructor sets the oldDate and newestDate fields to the same value, which is the value of the date that is in the record currently selected
	AlterRecords(std::string);
	
	void setNewDate(std::string newDate);  //Sets the newDate field to the date that was entered in the driver program
	void findNewestDate();				   //Finds the newest date between the date in the record and the date entered

	std::string getNewestDate() { return newestDate; }
};

#endif