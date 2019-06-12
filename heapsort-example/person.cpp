#include "person.hpp"

string person::getName(void)   //Gets name
{
	return name;
}

string person::getPhone(void)  //Gets phone
{
	return phone_number;
}

void person::setName(string nname) //Sets the name
{
	name = nname;
}

void person::setPhone(string pphone)  //Sets the phone
{
	phone_number = pphone;
}

void person::PrintPerson(void)  //Prints the contents of the Person class.
{
	cout << "Name: " << name << endl;
	cout << "Phone: " << phone_number << endl;
}
