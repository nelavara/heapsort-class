#include "phonebook.hpp"
#include <fstream>
#include <algorithm>

phonebook::phonebook()
{
	counter = 0;
	comparisons = 0;
	moves = 0;
}

void phonebook::ReadFromFile(person& input)  //reads data from file into the array.
{
	string fileName;
	if (counter == MAX_PERSONS)  //This will display a message if the array is full, array was set to size of 1001.
	{
		cout << "List is full, no more entries accepted, try running again later." << endl;
	}
	cout << "Please enter the name of the file you would like to import the contents of." << endl;
	cout << "Please note the file you would like to import, must be in the same directory as the source code." << endl;
	cout << "Example: 'readin.txt'" << endl;
	cout << "File name please: ";
	cin.ignore();
	getline(cin, fileName);  //Ask user for name of file

	ifstream ReadFile;
	ReadFile.open(fileName.c_str());  //Opens file to read contents
	string phonenumber;  //These three variables are temporary variables, which will later go into the array.
	string name;
	person temp;
	if (ReadFile.is_open())
	{
		for (;;)
		{
			getline(ReadFile, name); //Reads the name from file
			temp.setName(name);  //Temporary Person object has name set.
			getline(ReadFile, phonenumber);  //Reads the phone number for the file
			temp.setPhone(phonenumber);  //Temporary Person object has phone number set.

			if (ReadFile.good())  //If read from file is good.
			{
				input = temp;  //temporary person object is added to the array.
				individual[counter] = input;
				counter++;  //The count is then incremented so data is not overwritten.
				Heapify(0, counter);
			}
			else if (ReadFile.eof())  //At the end of the file, check if anything else to read.
			{
				input = temp;
				individual[counter] = input;
				counter++;
				Heapify(0, counter);
				HeapSort();
				cout << counter << " entries have been read into the program from file." << endl;  //Display message of how many items have been read from the file.
				cout << "The Phone Book has been sorted and written to Phonebook.txt" << endl;
				cout << "Moves: " << moves << endl;  //Displays on the screen the number of moves.
				cout << "Comparisons:" << comparisons << endl;  //Displays on the screen the number of comparisons made.
				WriteToFile();  //Calls write to file, and writes the sorted list to a file, however WriteToFile can be called by main if the user would like to write an unsorted list to a file instead.
				break;
			}
			else
			{
				cout << "FATAL ERROR!!!!" << endl; //If there is an error, please display it.
				break;
			}
		}
	}
}

void phonebook::PrintList(void)  //This function prints the entire list of the phone book.
{ //This function was useful for debugging to see the list before and after the data was sorted, but I thought I would leave it, because I like it.
	for (int index = 0; index < counter; index++)
	{
		individual[index].PrintPerson();  //Uses PrintPerson function in class person to print each item in the array.
	}
	cout << counter << " entries in Phonebook." << endl;  //Displays the number of people in the array.
}

void phonebook::WriteToFile(void)  //Writes the contents of the array to a file.
{
	ofstream WriteFile("Phonebook.txt"); //A new file named Phonebook.txt is created.
	if (WriteFile.is_open())  //First we check to make sure the file is open and we can read to it.
	{
		WriteFile << "Evan Perry" << endl << "Data Structures" << endl << "Dr.Tookey" << endl;  //These first few lines are the header of the file.
		WriteFile << "**********************Phone Book*****************************" << endl;
		WriteFile << "Moves: " << moves << endl;
		WriteFile << "Comparisons: " << comparisons << endl;
		for (int index = 0; index < counter; index++)  //This for loop writes the entire contents of array to a file.
		{
			WriteFile << individual[index].getName() << endl;  //First the name, then an end line.
			WriteFile << individual[index].getPhone() << endl;  //Second the phone, then an end line.
		}
	}
	else
		cout << "ERROR!!!" << endl;  //If we are are unable to write to the file, an error is displayed.
	WriteFile.close();  //The file is closed when writing is finished.
}

void phonebook::SearchName(void)  //This function performs binary search of the entire array, this will only work after bubble sort.
{
	int mid = 0;  //This is the middle variable, which will represent the middle.
	int start = 0;  //This is the starting variable which is set to 0 for the very first element of the array.
	bool found = false;  //This allows for us to check if the item we search for is found or not.
	int totelemt = counter;  //We create an integer and set it equal to the counter, this will allow us to travel through the list.
	int totcompare = 0;  //This integer is used to keep track of the number of comparisons performed.
	string entry;  //This will be the user entry.
	string stored_entry;  //This will be the entry stored in the array.
	cout << "Please enter the name of the individual you would like to search for: ";   //The user is prompted to enter something to search for.
	cin.ignore();
	getline(cin, entry);
	transform(entry.begin(), entry.end(), entry.begin(), ::tolower);  //We convert the users entry to all lower case.
	while (start <= totelemt && !found)
	{
		mid = (start + totelemt) / 2;  //Here the mid index is set to the half way point in the array.
		stored_entry = individual[mid].getName();  //Here we retrieve the name of person[mid]
		transform(stored_entry.begin(), stored_entry.end(), stored_entry.begin(), ::tolower);  //We transform to lower for the comparison.
		entry.compare(stored_entry);  //We compare the user and stored entries.
		if (entry > stored_entry)  //The comparison will return a 1, so if the middle is earlier in the alphabet than entry, entry will be greater.
		{
			start = mid + 1;  //the start will then be set to the middle +1
			totcompare++;  //We increment this value so we can report how many comparison we performed to find what we were looking for.
		}
		else if (entry < stored_entry)  //If entry comes before stored entry in the alphabet.
		{
			totelemt = mid - 1; //We set the counter to the middle -1
			totcompare++;  //This value is incremented so we can report the number of comparisons performed to find what we were looking for.
		}
		else  //If found a message is displayed.
		{
			cout << "Entry found" << endl;
			individual[mid].PrintPerson();  //The person is printer.
			cout << "It took " << totcompare << " comparisons to find this individual" << endl;  //We also print the number of comparisons performed in order to find the entry.
			break;  //We then have to break out of the loop or it will go into infinity.
		}


	}
	if (!found && start > totelemt)  //If we do not find anything we have to display an error message.
	{
		cout << "We could not find the entry you were looking for, try again later." << endl;
	}
}

void phonebook::MakeHeap(int start, int last) //This function will check to make sure that
{ // the children are less than the parents, this function is called by Heapify()
	int root = start; //sets the root to start, start is initalized to counter
	int placeholder = root;  //create a temporary holder.
	while ((root * 2) + 1 <= last)  //while root*2+1 is less than last which is initalized to counter
	{    //example is start = 0, root will be 1.
		int LChild = (root * 2) + 1;  //Left child of root (or parent) is root *2 +1
		int RChild = LChild + 1;  //Right child is root*2+2 or we an just add one to left child.
		string name;  //strings to hold names from the person objects that we will call.
		string name1;
		string name2;
		name = individual[LChild].getName(); //get the name of the Left Child
		name1 = individual[RChild].getName();  // get the name of the right Child
		name2 = individual[placeholder].getName();  //get the name of the element to possibly be swapped, which is set to the root.
		int x = name.compare(name2); //we compare the root to the left child.
		comparisons++; //increment comparisons.
		int y = name1.compare(name2); //we compare the root to the right child.
		comparisons++; //increment comparisons
		if (x == 1) //if x==1 meaning the root is smaller than the left child, the left child takes the place of the root.
		{
			placeholder = LChild;
		}
		if ((RChild <= last) && (y == 1)) //if the right child is not greater than the last element, and the root is smaller than the right child
		{
			placeholder = RChild; //the root and right child are swapped.
		}
		if (placeholder != root)  //if the root and the element to be swapped are no longer the same.
		{
			person temp = individual[root]; //we swap either the RChild or LChild with the root.
			moves++;  //moves are incremented, three moves are needed.
			individual[root] = individual[placeholder];
			moves++;
			individual[placeholder] = temp;
			moves++;
			root = placeholder; //we then set the root back to equal the element to possibly be swapped
		}
		else //if none of the above is true we exit the loop.
		{
			break;
		}
	}
	return;
}

void phonebook::Heapify(int start, int last) //heapify causes thee root to become highest and the children to all be smaller than their parents.
{
	int midEle = (last - start) / 2; //we start with the middle element
	for (; midEle >= 0; --midEle) //while the Middle Element is greater than 0 (for the first element in the array)
	{
		MakeHeap(midEle, last); //we MakeHeap and pass in middle element and thee last which is the counter.
	}
	return;
}

void phonebook::HeapSort(void)  //This function performs the sort.
{
	int last = counter - 1; //the last element is initialized to counter-1, because counter is set to 0 originally.
	Heapify(0, last); //we call heapify to make sure the highest element is in the root, and all children are less than their parents.
	while (last > 0) //while last is greater than 0 for the first element.
	{ //This assumes that heapify has organized the elements from highest to lowest.
		person temp = individual[last];  //the last element is swapped with the first.
		individual[last] = individual[0];
		individual[0] = temp;
		--last; //last is decremented.
		Heapify(0, last); //we make sure the list is still heapified.
		MakeHeap(0, last); //We also have to call MakeHeap or the final list will not be ordered properly.
	}
}
