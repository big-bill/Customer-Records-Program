/*
					C++ II Final Project

	Write a program that uses a structure to store the following information about a customer account:
	•	Name
	•	Address
	•	City, state, ZIP
	•	Telephone number
	•	Account Balance
	•	Date of last payment

	The structure should be used to store customer account records to a file. The program should have a menu that lets the user perform the following operations:
	•	Enter new records to a file
	•	Search for a particular customer’s record and display it
	•	Search for a particular customer’s record and change it
	•	Search for a particular customer’s record and delete it
	•	Display the contents of the entire file
	The specifications also asked for “at least” two classes.

	Written by Andrew Smith and Billy Matthews, April 2016.
*/

#include "AlterRecords.h"
#include "Validation.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

//-----------------------------------------------------------------------------------------------------
void splashScreen();
void clearScreen();
void searchRecord(struct CustomerAccount);
void displayContents(struct CustomerAccount);
void newRecord(struct CustomerAccount);
void addPayment(struct CustomerAccount);
bool checkYN(std::string&);
void changeRecord(struct CustomerAccount);
void removeRecord(struct CustomerAccount);
void userInput(struct CustomerAccount, long);

//-----------------------------------------------------------------------------------------------------
const int NAME_SIZE = 32, ADDRESS_SIZE = 40, CITY_SIZE = 32, STATE_SIZE = 3, TELE_SIZE = 13, DATE_SIZE = 11;
struct CustomerAccount {

	char name[NAME_SIZE];		 //Holds the name of the customer
	char address[ADDRESS_SIZE];  //Holds the address of the customer
	char state[STATE_SIZE];		 //Customer's current state
	char city[CITY_SIZE];		 //Customer's current city
	int zip;					 //Customer's zip
	char telephone[TELE_SIZE];   //Customer's telephone number (EX: 555-555-5555)
	double accountBalance;       //New customer's acccount balance (Can't be negative)
	char lastPayment[DATE_SIZE]; //Date of the last payment
};

//-----------------------------------------------------------------------------------------------------
int main() {

	splashScreen();
	clearScreen();

	CustomerAccount customer = { " ", " ", " ", " ", 0, " ", 0.0, " " };
	std::string choice;

	std::fstream record("CustomerAccount.dat", std::ios::in);
	if (!record)
	{
		std::cout << "Could not find \"CustomerAccount.dat\". Creating the file.";
		std::cout << "\nPress enter to continue the program. . .";
		record.open("CustomerAccount.dat", std::ios::out);
		std::getline(std::cin, choice);
	}
	record.close();

	do
	{
		while (true)
		{
			clearScreen();
			std::cout << "\n\n\t---------------- Main Menu ----------------------";
			std::cout << "\n\t|          (E)nter a new record                 |";
			std::cout << "\n\t|          (A)dd payment to record              |";
			std::cout << "\n\t|          (S)earch for a record                |";
			std::cout << "\n\t|          (C)hange a record                    |";
			std::cout << "\n\t|          (R)emove a record                    |";
			std::cout << "\n\t|          (D)isplay contents of the file       |";
			std::cout << "\n\t|          (Q)uit the program                   |";
			std::cout << "\n\t-------------------------------------------------\n";
			std::cout << "\n\tChoice: ";
			std::getline(std::cin, choice);
			if (choice.length() == 1)
			{
				choice[0] = toupper(choice[0]);
				if (choice[0] == 'E' || choice[0] == 'A' || choice[0] == 'S' || choice[0] == 'C' || 
					choice[0] == 'D' || choice[0] == 'R' || choice[0] == 'Q')
					break;
			}
			std::cout << "\n\nInvalid input! Please re-enter your choice.\nPress enter to continue. . .";
			std::getline(std::cin, choice);
		}

		switch (choice[0])
		{
		case 'E':
			newRecord(customer);
			break;
		case 'A':
			addPayment(customer);
			break;
		case 'S':
			searchRecord(customer);
			break;
		case 'C':
			changeRecord(customer);
			break;
		case 'R':
			removeRecord(customer);
			break;
		case 'D':
			displayContents(customer);
			break;
		default:
			std::cout << "\n\nThanks for using the program!\n";
			break;
		}

	} while (choice[0] != 'Q');

	std::cout << "\nPress enter to exit the program. . .";
	std::cin.get();
	return 0;
}
//-----------------------------------------------------------------------------------------------------
//Splashscreen that welcomes the user
void splashScreen() {

	std::cout << "\n";

	std::cout << "  #####                                                         " << std::endl;
	std::cout << " #     #  #    #   ####   #####   ####   #    #  ######  #####  " << std::endl;
	std::cout << " #        #    #  #         #    #    #  ##  ##  #       #    # " << std::endl;
	std::cout << " #        #    #   ####     #    #    #  # ## #  #####   #    # " << std::endl;
	std::cout << " #        #    #       #    #    #    #  #    #  #       #####  " << std::endl;
	std::cout << " #     #  #    #  #    #    #    #    #  #    #  #       #   #  " << std::endl;
	std::cout << "  #####    ####    ####     #     ####   #    #  ######  #    # " << std::endl;
	std::cout << "                                                                " << std::endl;
	std::cout << "    #                                                           " << std::endl;
	std::cout << "   # #     ####    ####    ####   #    #  #    #  #####   ####  " << std::endl;
	std::cout << "  #   #   #    #  #    #  #    #  #    #  ##   #    #    #      " << std::endl;
	std::cout << " #     #  #       #       #    #  #    #  # #  #    #     ####  " << std::endl;
	std::cout << " #######  #       #       #    #  #    #  #  # #    #         # " << std::endl;
	std::cout << " #     #  #    #  #    #  #    #  #    #  #   ##    #    #    # " << std::endl;
	std::cout << " #     #   ####    ####    ####    ####   #    #    #     ####  " << std::endl;

	std::cout << "\nThis program is desigend to create a customer account with the following info\n";
	std::cout << "Name, Address, City, state, ZIP, Telephone number, Account Balance, and Date of last payment.";
	std::cout << "\nPress the enter key to continue.";
	std::string line = "";
	std::getline(std::cin, line);
}
//-----------------------------------------------------------------------------------------------------
//This function clears the screen by printing 100 blank lines on the command line
void clearScreen() {

	//clears the screen
	std::cout << std::string(100, '\n');
}
//-----------------------------------------------------------------------------------------------------
bool checkYN(std::string &userInput) {

	//The choice of 'Y' or 'N' was used a lot, so this function was made
	//This will check if the string is one character
	if (userInput.length() == 1)
	{
		//Sets that one character to its uppercase version
		userInput[0] = toupper(userInput[0]);
		if (userInput[0] == 'Y' || userInput[0] == 'N')
			return true;
	}
	return false;
}
//-----------------------------------------------------------------------------------------------------
void searchRecord(CustomerAccount acc) {

	clearScreen();
	std::string tempString;
	tempString = "";
	long length = 0;
	long recordNum = 0;

	std::string x;
	std::cout << "Enter your name";
	std::getline(std::cin, x);
	std::cout << "Hello, " << x;

	std::ifstream record("CustomerAccount.dat", std::ios::in | std::ios::binary);

	//First checks to see if the file exists, if not this will create it and return back to the main menu
	if (!record)
	{
		std::cout << "Could not find \"CustomerAccount.dat\". Creating the file.";
		std::cout << "\nPress enter to return to the main menu. . .";
		record.open("CustomerAccount.dat", std::ios::out);
		record.close();

		std::getline(std::cin, tempString);
		return;
	}

	//since the text file did exist before this function was accessed, we will now check if the file is empty or not
	record.seekg(0, std::ios::end);
	length = record.tellg();
	if (length == 0L)
	{
		std::cout << "\nThere were no records found in the file." << std::endl;
		std::cout << "Press enter to return to the main menu. . .";
		std::getline(std::cin, tempString);
	}
	else
	{
		do
		{
			clearScreen();
			while (true)
			{
				std::cout << "\nEnter the record number of the account you wish to search."
					<< "\nEnter 'M' if you wish to return to the main menu.\nRecord Number: ";
				std::getline(std::cin, tempString);

				//If the user wishes to return to the main menu, this will allow them to do so.
				if (tempString.length() == 1 && (tempString[0] == 'M' || tempString[0] == 'm'))
					return;

				std::stringstream myStream(tempString);
				if (myStream >> recordNum && recordNum > 0)
					break;

				clearScreen();
				std::cout << "\nInvalid record ID entered, please enter a valid record ID.\n\n";
			}

			record.seekg(recordNum, std::ios::cur);
			length = record.tellg();
			record.clear();
			if (length < 1)
				std::cout << "\n\nRecord not found.\n\n";
			else
			{
				//If the user entered 1, the second record would be read, not the first
				//So we'll decrement the record number
				recordNum--;

				//record puts the reading position to the record number specified and then read the contents
				record.seekg(recordNum * sizeof(acc), std::ios::beg);
				record.read(reinterpret_cast<char *>(&acc), sizeof(acc));
				std::cout << "\nRecord " << (recordNum + 1) << std::endl;
				std::cout << "\n\nName:                 " << acc.name << std::endl;
				std::cout << "Address:              " << acc.address << std::endl;
				std::cout << "State:                " << acc.state << std::endl;
				std::cout << "City:                 " << acc.city << std::endl;
				std::cout << "ZIP:                  " << acc.zip << std::endl;
				std::cout << "Telephone:            " << acc.telephone << std::endl;
				std::cout << "Account Balance:      $" << acc.accountBalance << std::endl;
				std::cout << "Date of last payment: " << acc.lastPayment << std::endl;
				std::cout << "------------------------------------------------------\n";
			}

			//Asks if the user would like to search for anothe record.
			while (true)
			{
				std::cout << "Would you like to search for another record? (Y / N)";
				std::cout << "\nChoice:";
				std::getline(std::cin, tempString);
				if (checkYN(tempString)) //checkYN checks if the string entered is either 'Y' or 'N'
					break;
				else
					std::cout << "Invalid choice! Please re-enter your decision.\n";
			}

		} while (tempString[0] == 'Y');

		std::cout << "\nPress enter to return to the main menu. . . ";
		std::getline(std::cin, tempString);
	}
}
//-----------------------------------------------------------------------------------------------------
//This function opens the dat file for input and reads in the entire file onto the command line
void displayContents(CustomerAccount acc) {

	clearScreen();
	//Opens the file for input
	std::ifstream displayFile("CustomerAccount.dat", std::ios::in | std::ios::binary);
	std::string line = "";

	if (!displayFile)
	{
		std::cout << "Could not find \"CustomerAccount.dat\". Creating the file.";
		std::cout << "\nPress enter to return to the main menu. . .";
		displayFile.open("CustomerAccount.dat", std::ios::out);
		displayFile.close();

		std::getline(std::cin, line);
		return;
	}

	std::cout << "Contents of \"CustomerAccount.dat\"\n";

	displayFile.read(reinterpret_cast<char *>(&acc), sizeof(acc));

	//Outputs all the content in the file
	for (int count = 0; !displayFile.eof(); count++)
	{
		std::cout << "\nRecord " << (count + 1) << std::endl;
		std::cout << "Name:                 " << acc.name << std::endl;
		std::cout << "Address:              " << acc.address << std::endl;
		std::cout << "State:                " << acc.state << std::endl;
		std::cout << "City:                 " << acc.city << std::endl;
		std::cout << "ZIP:                  " << acc.zip << std::endl;
		std::cout << "Telephone:            " << acc.telephone << std::endl;
		std::cout << "Account Balance:      $" << acc.accountBalance << std::endl;
		std::cout << "Date of last payment: " << acc.lastPayment << std::endl << std::endl;

		displayFile.read(reinterpret_cast<char *>(&acc), sizeof(acc));
	}

	std::cout << "The entire document has been read.";
	displayFile.close();

	std::cout << "\n\nPress enter to return to the menu. . .";
	std::getline(std::cin, line);
}
//-----------------------------------------------------------------------------------------------------
//This function allows for the user to enter a new record onto the end of the CustomerAccount file
void newRecord(CustomerAccount acc) {
	
	clearScreen();
	std::string input = "";

	std::cout << "Please have your information ready.\n";

	do
	{
		clearScreen();
		//0L is passed to signify that we want to put the record at the end of the file
		userInput(acc, 0L);

		while (true)
		{
			std::cout << "\nWould you like to enter another customer account? (Y / N)\nChoice: ";
			std::getline(std::cin, input);
			if (checkYN(input)) //checkYN checks if the string entered is either 'Y' or 'N'
				break;
			else
				std::cout << "Invalid choice! Please re-enter your decision.\n";
		}

	} while (input[0] == 'Y');
}
//-----------------------------------------------------------------------------------------------------
/*
	This function adds a payment to a record, and will use both Validation and AlterRecords classes to
	validate the user input and check if the newly entered date is more recent than the date in the record.
*/
void addPayment(CustomerAccount acc) {

	clearScreen();

	std::string tempString, depositDate;
	tempString = depositDate = "";
	long length = 0;
	long recordNum = 0;
	double oldBalance, newBalance;
	oldBalance = newBalance = 0.0;

	Validation validate;

	std::ifstream record("CustomerAccount.dat", std::ios::in | std::ios::out | std::ios::binary);

	//First checks to see if the file exists, if not this will create it and return back to the main menu
	if (!record)
	{
		std::cout << "Could not find \"CustomerAccount.dat\". Creating the file.";
		std::cout << "\nPress enter to return to the main menu. . .";
		record.open("CustomerAccount.dat", std::ios::out);
		record.close();

		std::getline(std::cin, tempString);
		return;
	}

	//since the text file did exist before this function was accessed, we will now check if the file is empty or not
	record.seekg(0, std::ios::end);
	length = record.tellg();
	if (length == 0L)
	{
		std::cout << "\nThere were no records found in the file." << std::endl;
		std::cout << "Press enter to return to the main menu. . .";
		std::getline(std::cin, tempString);
	}
	else
	{
		record.close();
		do
		{
			clearScreen();

			std::fstream record("CustomerAccount.dat", std::ios::in | std::ios::out | std::ios::binary);
			while (true)
			{
				std::cout << "\nEnter the record number of the account you wish to deposit to."
					<< "\nEnter 'M' if you wish to return to the main menu.\nRecord Number: ";
				std::getline(std::cin, tempString);

				//If the user wishes to return to the main menu, this will allow them to do so.
				if (tempString.length() == 1 && (tempString[0] == 'M' || tempString[0] == 'm'))
					return;

				std::stringstream myStream(tempString);
				if (myStream >> recordNum && recordNum > 0)
					break;

				clearScreen();
				std::cout << "\nInvalid record ID entered, please enter a valid record ID.\n\n";
			}

			clearScreen();

			record.seekg(recordNum, std::ios::cur);
			length = record.tellg();
			record.clear();
			if (length < 1)
				std::cout << "\n\nRecord not found.\n\n";
			else
			{
				recordNum--;
				record.seekg(recordNum * sizeof(acc), std::ios::beg);
				record.read(reinterpret_cast<char *>(&acc), sizeof(acc));


				std::cout << "Account: " << (recordNum + 1);
				std::cout << "\n\nName:                 " << acc.name << std::endl;
				std::cout << "Account Balance:      $" << acc.accountBalance << std::endl;
				std::cout << "Date of last payment: " << acc.lastPayment << std::endl;
				std::cout << "------------------------------------------------------\n\n";

				//We hold the current balance of the account in oldBalance
				oldBalance = acc.accountBalance;

				//This obect is used to check the date of the deposit to check if it is more recent than the one in the record
				AlterRecords checkDateOfDeposit(acc.lastPayment);

				//This loop gets the customer's deposit
				while (true)
				{
					std::cout << "\nEnter the deposit amount.\n";
					std::cout << "Deposit: ";
					std::getline(std::cin, tempString);

					if (tempString.length() == 0)
					{
						std::cout << "\nYou didn't enter a valid balance!\n";
						continue;
					}

					std::stringstream myStream(tempString);
					//Converts the string to the appropriate data type and checks that it is a positive number
					if (myStream >> acc.accountBalance && acc.accountBalance >= 0.0)
					{
						while (true)
						{
							std::cout << "\nYou entered $" << std::showpoint << std::setprecision(2) << std::fixed << acc.accountBalance << "\nIs this correct? (Y/N)\nChoice: ";
							std::getline(std::cin, tempString);
							if (checkYN(tempString))
								break;
							else
								std::cout << "\nInvalid choice! Please re-enter your decision.\n";
						}
						if (tempString[0] == 'Y')
							break;
					}
					else
					{
						std::cout << "\nYou didn't enter a valid deposit amount!\nNo negative values may be entered.\n";
						continue;
					}
				}

				//Adds the deposit to account
				acc.accountBalance += oldBalance;

				//This loop gets the customer's date of last payment
				while (true)
				{
					std::cout << "\nEnter the date of this deposit. The format for the date is \"MM/DD/YYYY\"\n";
					std::cout << "Date: ";
					std::getline(std::cin, depositDate);

					//Checks if the date entered follows the correct format
					if (!(validate.checkDate(depositDate)))
					{
						std::cout << "\nYou didn't enter a valid date!\n";
						continue;
					}
					checkDateOfDeposit.setNewDate(depositDate);

					//returns the date of the last payment
					tempString = checkDateOfDeposit.getNewestDate();
					//Converts that date string to c-string
					strcpy_s(acc.lastPayment, tempString.c_str());

					while (true)
					{
						std::cout << "\nYou entered " << depositDate << ".\nIs this correct? (Y/N)\nChoice: ";
						std::getline(std::cin, tempString);
						if (checkYN(tempString))
							break;
						else
							std::cout << "\nInvalid choice! Please re-enter your decision.\n";
					}
					if (tempString[0] == 'Y')
						break;
				}

				//Finds the position of the record number and enters the accounts new information
				record.seekp(recordNum * sizeof(acc), std::ios::beg);
				record.write(reinterpret_cast<char *>(&acc), sizeof(acc));
				record.close();
			}

			while (true)
			{
				std::cout << "\nWould you like to enter another deposit? (Y/N)";
				std::cout << "\nChoice:";
				std::getline(std::cin, tempString);
				if (checkYN(tempString)) //checkYN checks if the string entered is either 'Y' or 'N'
					break;
				else
					std::cout << "Invalid choice! Please re-enter your decision.\n";
			}
		} while (tempString[0] == 'Y');
	}

	std::cout << "\nPress enter to return to the main menu. . . ";
	std::getline(std::cin, tempString);
}
//-----------------------------------------------------------------------------------------------------
/*
	changeRecord allows the user to change the contents of a single record.
*/
void changeRecord(CustomerAccount acc) {

	clearScreen();

	std::string tempString;
	tempString = "";
	long length = 0;
	long recordNum = 0;

	std::ifstream record("CustomerAccount.dat", std::ios::in | std::ios::binary);

	//First checks to see if the file exists, if not this will create it and return back to the main menu
	if (!record)
	{
		std::cout << "Could not find \"CustomerAccount.dat\". Creating the file.";
		std::cout << "\nPress enter to return to the main menu. . .";
		record.open("CustomerAccount.dat", std::ios::out);
		record.close();

		std::getline(std::cin, tempString);
		return;
	}

	//since the text file did exist before this function was accessed, we will now check if the file is empty or not
	record.seekg(0, std::ios::end);
	length = record.tellg();
	if (length == 0)
	{
		std::cout << "\nThere were no records found in the file." << std::endl;
		std::cout << "Press enter to return to the main menu. . .";
		std::getline(std::cin, tempString);
	}
	else
	{
		do
		{
			clearScreen();
			while (true)
			{
				std::cout << "\nEnter the record number of the account you wish to change."
					<< "\nEnter 'M' if you wish to return to the main menu.\nRecord Number: ";
				std::getline(std::cin, tempString);

				//If the user wishes to return to the main menu, this will allow them to do so.
				if (tempString.length() == 1 && (tempString[0] == 'M' || tempString[0] == 'm'))
					return;

				std::stringstream myStream(tempString);
				if (myStream >> recordNum && recordNum > 0)
					break;

				clearScreen();
				std::cout << "\nInvalid record ID entered, please enter a valid record ID.\n\n";
			}

			record.seekg(recordNum, std::ios::cur);
			length = record.tellg();
			if (length == 0L)
				std::cout << "\n\tRecord not found.";
			else
			{
				//If the user entered 1, the second record would be read, not the first
				//So we'll decrement the record number
				recordNum--;

				record.seekg(recordNum * sizeof(acc), std::ios::beg);
				record.read(reinterpret_cast<char *>(&acc), sizeof(acc));

				std::cout << "\nThis is the current record information.";
				std::cout << "\nRecord " << (recordNum + 1) << std::endl;
				std::cout << "\n\nName:                 " << acc.name << std::endl;
				std::cout << "Address:              " << acc.address << std::endl;
				std::cout << "State:                " << acc.state << std::endl;
				std::cout << "City:                 " << acc.city << std::endl;
				std::cout << "ZIP:                  " << acc.zip << std::endl;
				std::cout << "Telephone:            " << acc.telephone << std::endl;
				std::cout << "Account Balance:      $" << acc.accountBalance << std::endl;
				std::cout << "Date of last payment: " << acc.lastPayment << std::endl;
				std::cout << "------------------------------------------------------\n";

				//Since the record numbers in the file start out at 0, we need to increment it once more
				//This is because in userInput() it checks if the recordNum is 0, and if it is it opens the file for appended output.
				recordNum++;
				record.close();
			}

			while (true)
			{
				std::cout << "Are you sure you would like to edit ? (Y / N)";
				std::cout << "\nChoice:";
				std::getline(std::cin, tempString);
				if (checkYN(tempString)) //checkYN checks if the string entered is either 'Y' or 'N'
					break;
				else
					std::cout << "Invalid choice! Please re-enter your decision.\n";
			}

			if (tempString[0] == 'Y'){

				userInput(acc, recordNum);

			}

			while (true)
			{
				std::cout << "Would you like to change another record? (Y / N)";
				std::cout << "\nChoice:";
				std::getline(std::cin, tempString);
				if (checkYN(tempString)) //checkYN checks if the string entered is either 'Y' or 'N'
					break;
				else
					std::cout << "Invalid choice! Please re-enter your decision.\n";
			}

		} while (tempString[0] == 'Y');

		std::cout << "\nPress enter to return to the main menu. . . ";
		std::getline(std::cin, tempString);
	}

}
//-----------------------------------------------------------------------------------------------------
void removeRecord(CustomerAccount acc) {

	std::string tempString;
	tempString = "";
	long length = 0;
	long recordNum = 0;

	std::ifstream record("CustomerAccount.dat", std::ios::in | std::ios::binary);

	//First checks to see if the file exists, if not this will create it and return back to the main menu
	if (!record)
	{
		std::cout << "Could not find \"CustomerAccount.dat\". Creating the file.";
		std::cout << "\nPress enter to return to the main menu. . .";
		record.open("CustomerAccount.dat", std::ios::out);
		record.close();

		std::getline(std::cin, tempString);
		return;
	}

	//since the text file did exist before this function was accessed, we will now check if the file is empty or not
	record.seekg(0, std::ios::end);
	length = record.tellg();
	if (length == 0)
	{
		record.close();
		std::cout << "\nThere were no records found in the file." << std::endl;
		std::cout << "Press enter to return to the main menu. . .";
		std::getline(std::cin, tempString);
	}
	else
	{
		record.close();
		do
		{
			std::ifstream record("CustomerAccount.dat", std::ios::in | std::ios::binary);
			clearScreen();
			while (true)
			{
				std::cout << "\nEnter the record number of the item you wish to remove."
					<< "\nEnter 'M' if you wish to return to the main menu.\nRecord Number: ";
				std::getline(std::cin, tempString);

				//If the user wishes to return to the main menu, this will allow them to do so.
				if (tempString.length() == 1 && (tempString[0] == 'M' || tempString[0] == 'm'))
					return;

				std::stringstream myStream(tempString);
				if (myStream >> recordNum && recordNum > 0)
					break;

				clearScreen();
				std::cout << "\nInvalid record ID entered, please enter a valid record ID.\n\n";
			}

			record.seekg(recordNum, std::ios::cur);
			length = record.tellg();
			if (length == 0L)
				std::cout << "\n\tRecord not found.";
			else
			{
				recordNum--;

				record.seekg(recordNum * sizeof(acc), std::ios::beg);
				record.read(reinterpret_cast<char *>(&acc), sizeof(acc));

				std::cout << "\nThis is the current record information.";
				std::cout << "\nRecord " << (recordNum + 1) << std::endl;
				std::cout << "\n\nName:                 " << acc.name << std::endl;
				std::cout << "Address:              " << acc.address << std::endl;
				std::cout << "State:                " << acc.state << std::endl;
				std::cout << "City:                 " << acc.city << std::endl;
				std::cout << "ZIP:                  " << acc.zip << std::endl;
				std::cout << "Telephone:            " << acc.telephone << std::endl;
				std::cout << "Account Balance:      $" << acc.accountBalance << std::endl;
				std::cout << "Date of last payment: " << acc.lastPayment << std::endl;
				std::cout << "------------------------------------------------------\n";
			}

			record.close();

			//Asks one last time that the user is sure that they are OK with removing the selected record
			while (true)
			{
				std::cout << "Are you sure you would like to remove this record? (Y / N)";
				std::cout << "\nChoice:";
				std::getline(std::cin, tempString);
				if (checkYN(tempString)) //checkYN checks if the string entered is either 'Y' or 'N'
					break;
				else
					std::cout << "Invalid choice! Please re-enter your decision.\n";
			}

			if (tempString[0] == 'Y'){

				CustomerAccount tempStruct;

			//We open two files, and now store all the content in CustomerAccount to tempFile EXCEPT for the record the user wants to remove
				std::fstream record("CustomerAccount.dat", std::ios::in | std::ios::binary);
				std::fstream tempFile("tempFile.dat", std::ios::out | std::ios::binary);
				if (record.fail() || tempFile.fail())
				{
					std::cout << "\nError opening file.\n";
					return;
				}

				long count = 0L;
				while (record.read((char*)&tempStruct, sizeof(tempStruct)))
				{
					if (!count == recordNum)
						tempFile.write((char*)&tempStruct, sizeof(tempStruct));
					
					count++;
				}
				std::cout << "\nDeletion Successful. \n";

				//We close the two files
				record.close();
				tempFile.close();

				//Now that tempFile contains all the contents of CustomerAccount besides the 
				//specified record, we will now rename tempFile and delete the original file.
				remove("CustomerAccount.dat");
				rename("tempFile.dat", "CustomerAccount.dat");
			}

			while (true)
			{
				std::cout << "Would you like to remove another record? (Y / N)";
				std::cout << "\nChoice:";
				std::getline(std::cin, tempString);
				if (checkYN(tempString)) //checkYN checks if the string entered is either 'Y' or 'N'
					break;
				else
					std::cout << "Invalid choice! Please re-enter your decision.\n";
			}

		} while (tempString[0] == 'Y');

		std::cout << "\nPress enter to return to the main menu. . . ";
		std::getline(std::cin, tempString);
	}

}
//-----------------------------------------------------------------------------------------------------
void userInput(CustomerAccount acc, long recordNumChosen) {

	std::fstream record("CustomerAccount.dat", std::ios::in | std::ios::out | std::ios::binary);

	if (!recordNumChosen == 0L)
	{
		recordNumChosen--;
		record.seekp(recordNumChosen * sizeof(acc), std::ios::beg);
	}
	//If the recordNumChosen is 0L, that means the newRecord() function was called, and we will add the new record to the EOF
	else
	{
		record.seekp(0L, std::ios::end);
	}

	std::string input = "";

	Validation validate;

	//This loop gets the customer's name
	while (true)
	{
		std::cout << "\nEnter the customer's name.\n";
		std::cout << "Name: ";
		std::getline(std::cin, input);

		if (input.length() == 0 || input.length() >= NAME_SIZE)
		{
			std::cout << "\nYou didn't enter a valid name!\n";
			continue;
		}

		//stores the string into the structure's name C-String
		strcpy_s(acc.name, input.c_str());

		while (true)
		{
			std::cout << "\nYou entered " << acc.name << ".\nIs this correct? (Y/N)\nChoice: ";
			std::getline(std::cin, input);
			if (checkYN(input)) //checkYN checks if the string entered is either 'Y' or 'N'
				break;
			else
				std::cout << "Invalid choice! Please re-enter your decision.\n";
		}
		if (input[0] == 'Y')
			break;
	}

	clearScreen();  //Clears the screen
	//This loop gets the customer's state
	while (true)
	{
		std::cout << "\nEnter the customer's state. For example, Florida would be \"FL\"\n";
		std::cout << "State: ";
		std::getline(std::cin, input);

		if (!validate.checkState(input))
		{
			std::cout << "\nInvalid state entered! Please re-enter a valid state name.\n";
			continue;
		}

		strcpy_s(acc.state, input.c_str());

		while (true)
		{
			std::cout << "\nYou entered " << acc.state << ".\nIs this correct? (Y/N)\nChoice: ";
			std::getline(std::cin, input);
			if (checkYN(input))
				break;
			else
				std::cout << "\nInvalid choice! Please re-enter your decision.\n";
		}
		if (input[0] == 'Y')
			break;
	}


	clearScreen();
	//This loop gets the customer's city
	while (true)
	{
		std::cout << "\nEnter the customer's city.\n";
		std::cout << "City: ";
		std::getline(std::cin, input);

		if (input.length() == 0 || input.length() >= CITY_SIZE)
		{
			std::cout << "\nYou didn't enter a valid city!\n";
			continue;
		}

		strcpy_s(acc.city, input.c_str());

		while (true)
		{
			std::cout << "\nYou entered " << acc.city << ".\nIs this correct? (Y/N)\nChoice: ";
			std::getline(std::cin, input);
			if (checkYN(input))
				break;
			else
				std::cout << "\nInvalid choice! Please re-enter your decision.\n";
		}
		if (input[0] == 'Y')
			break;
	}

	clearScreen();
	//This loop gets the customer's address
	while (true)
	{
		std::cout << "Enter the customer's address.\n";
		std::cout << "Address: ";
		std::getline(std::cin, input);

		if (input.length() == 0 || input.length() >= ADDRESS_SIZE)
		{
			std::cout << "\nYou didn't enter a valid address!\n";
			continue;
		}

		strcpy_s(acc.address, input.c_str());

		while (true)
		{
			std::cout << "\nYou entered " << acc.address << ".\nIs this correct? (Y/N)\nChoice: ";
			std::getline(std::cin, input);
			if (checkYN(input))
				break;
			else
				std::cout << "\nInvalid choice! Please re-enter your decision.\n";
		}
		if (input[0] == 'Y')
			break;
	}

	clearScreen(); 
	//This loop gets the customer's ZIP
	while (true)
	{
		std::cout << "\nEnter the customer's ZIP.\n";
		std::cout << "ZIP: ";
		std::getline(std::cin, input);

		if (input.length() == 0)
		{
			std::cout << "\nYou didn't enter a valid ZIP code!\n";
			continue;
		}

		std::stringstream myStream(input);
		if (myStream >> acc.zip && acc.zip >= 10000 && acc.zip <= 99999)
		{
			while (true)
			{
				std::cout << "\nYou entered " << acc.zip << ".\nIs this correct? (Y/N)\nChoice: ";
				std::getline(std::cin, input);
				if (checkYN(input))
					break;
				else
					std::cout << "\nInvalid choice! Please re-enter your decision.\n";
			}
			if (input[0] == 'Y')
				break;
		}
		else
			std::cout << "\nYou didn't enter a valid ZIP code!\n";
	}


	clearScreen();  //Clears the screen
	//This loop gets the customer's telephone #
	while (true)
	{
		std::cout << "\nEnter the customer's telephone number.\nThe format for the phone number is \"###-###-####\"\n";
		std::cout << "Number: ";
		std::getline(std::cin, input);

		if (!(validate.checkTelephone(input)))
		{
			std::cout << "\nYou didn't enter a valid telephone number!\n";
			continue;
		}

		strcpy_s(acc.telephone, input.c_str());

		while (true)
		{
			std::cout << "\nYou entered " << acc.telephone << ".\nIs this correct? (Y/N)\nChoice: ";
			std::getline(std::cin, input);
			if (checkYN(input))
				break;
			else
				std::cout << "\nInvalid choice! Please re-enter your decision.\n";
		}
		if (input[0] == 'Y')
			break;
	}

	clearScreen();
	//This loop gets the customer's current account balance
	while (true)
	{
		std::cout << "\nEnter the customer's current account balance.\n";
		std::cout << "Account Balance: ";
		std::getline(std::cin, input);

		if (input.length() == 0)
		{
			std::cout << "\nYou didn't enter a valid balance!\n";
			continue;
		}

		std::stringstream myStream(input);
		//Converts the string to the appropriate data type and checks that it is a positive number
		if (myStream >> acc.accountBalance && acc.accountBalance >= 0.0)
		{
			while (true)
			{
				std::cout << "\nYou entered $" << std::showpoint << std::setprecision(2) << std::fixed << acc.accountBalance << "\nIs this correct? (Y/N)\nChoice: ";
				std::getline(std::cin, input);
				if (checkYN(input))
					break;
				else
					std::cout << "\nInvalid choice! Please re-enter your decision.\n";
			}
			if (input[0] == 'Y')
				break;
		}
		else
		{
			std::cout << "\nYou didn't enter a valid account balance!\nNo negative values may be entered.\n";
			continue;
		}
	}

	clearScreen();  //Clears the screen
	//This loop gets the customer's date of last payment
	while (true)
	{
		std::cout << "\nEnter the date of the last payment. The format for the date is \"MM/DD/YYYY\"\n";
		std::cout << "Date: ";
		std::getline(std::cin, input);

		//Checks if the date entered follows the correct format
		if (!(validate.checkDate(input)))
		{
			std::cout << "\nYou didn't enter a valid date!\n";
			continue;
		}

		strcpy_s(acc.lastPayment, input.c_str());

		while (true)
		{
			std::cout << "\nYou entered " << acc.lastPayment << ".\nIs this correct? (Y/N)\nChoice: ";
			std::getline(std::cin, input);
			if (checkYN(input))
				break;
			else
				std::cout << "\nInvalid choice! Please re-enter your decision.\n";
		}
		if (input[0] == 'Y')
			break;
	}

	record.write(reinterpret_cast<char *>(&acc), sizeof(acc));
	record.close();
}