#ifndef PHONEBOOK_HPP_INCLUDED
#define PHONEBOOK_HPP_INCLUDED
#include "person.hpp"
#define MAX_PERSONS 1001  //Used for max size of array.

class phonebook {
private:
	person individual[MAX_PERSONS];  //Array of class person up to 1001 positions in memory
	int counter;  //Counter to keep track of current position in array.
	int moves;    //Moves, to keep track of moves performed.
	int comparisons;  //Comparison to keep track of comparisons performed.
public:
	phonebook(); //constructor
	void ReadFromFile(person& input); //input data into the array from a file
	void PrintList(void); //prints the contents of the array on the screen
	void HeapSort(void);
	void WriteToFile(void); //writes sorted list to file, only can be called by BubbleSort();
	void SearchName(void);  //Search the array for a person.
	void MakeHeap(int start, int last);  //Makes heap by making sure that children are all less than their parents, changes root if necessary
	void Heapify(int start, int last); //calls make heap while n/2 is less than 0, where n is represented by midEle and is the number of elements in the array

};


#endif // PHONEBOOK_HPP_INCLUDED
