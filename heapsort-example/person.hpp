#ifndef PERSON_HPP_INCLUDED
#define PERSON_HPP_INCLUDED

#include <string>
#include <iostream>
using namespace std;

class person {
private:
	string name;
	string phone_number;
public:
	string getName(void); //gets the name of the individual.
	string getPhone(void); //gets the phone number of the individual
	void setName(string nname); //sets the name.
	void setPhone(string pphone); //sets the phone
	void PrintPerson(void); //prints the contents of the person class
};



#endif // PERSON_HPP_INCLUDED
