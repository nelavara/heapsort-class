//Evan Perry
//Data Structures

#include <iostream>
#include <string>
#include "phonebook.hpp"
#include <limits>

using namespace std;

void menu(void);   //Function prototypes
void run_program(int&, person&, phonebook&);
void verify_entry(int&);

int main()  //main function
{
	int entry; //user entry
	person temp; //temp type of person
	phonebook tempIndi; //temp Individual of type phone book.

	while (entry != 4)  //executes until user selects 6.
	{
		menu();  //calls menu function
		verify_entry(entry); //Verifies user entry for the menu
		run_program(entry, temp, tempIndi); //Different driver commands, called by user selection.
	}
	return 0;
}

void menu(void)  //displays the menu
{

	cout << "Evan Perry" << endl << "Data Structures Assignment 3" << endl << "Dr. Tookey" << endl;
	cout << "------------------Menu---------------------" << endl;
	cout << "Please pick one of the following options." << endl;
	cout << "1. Read From File" << endl;
	cout << "2. Print Phone Book to the Screen." << endl;
	cout << "3. Search List by name." << endl;
	cout << "4. Quit" << endl;
	cout << "Enter 1 through 4 to make a selection: ";

}

void run_program(int& entry, person& temp, phonebook& tempIndi) //executes the program, calls functions from phonenumbers to help.
{
	if (entry == 1)
	{
		tempIndi.ReadFromFile(temp);
	}
	else if (entry == 2)
	{
		tempIndi.PrintList();
	}
	else if (entry == 3)
	{
		tempIndi.SearchName();
	}

}

void verify_entry(int& entry)  //Verifies the entry from the main menu.
{
	while (entry == 0 || entry != '\0' || cin.get() != '\n')  //while cin not equal to null or forces program to wait until entry is received.
	{

		while (!(cin >> entry))  //while bad cin
		{
			cout << "Incorrect entry, try again: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}
		if (entry <= 0)
		{
			cout << "No negative numbers or 0, please try again: ";

		}
		else if (entry > 4)
		{
			cout << "Out of bounds, please try again: ";
		}
		else
			break;
	}

}
