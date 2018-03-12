
/**
 * @file hash.cpp   
 *
 * @brief
 *	Contains the functions for adding words to a hash table using the hashing
 *	algorithm in hash_function.cpp
 *
 * @author Cole Warner
 * @date 3/5/18
 */

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include "hash.h"

using std::cout;
using std::endl;
using std::ofstream;


/**
 * @brief	Hash constructor
 * @param	none		
 * @Return   none
 */
Hash::Hash()
{	
	collisions = 0;                 // total number of collisions
	longestList = 0;        		// longest list ever generated
	runningAvgListLength = 0.0;     // running average of average list length
}                         


/**
 * @brief	removes a word from the hash table
 * @param	word - a string that holds the word to be removed
 * @return  none
 */
void Hash::remove(string word)
{
	// hash the word to be removed, to get the appropriate index
	int index = hf(word);
	
	// iterate through the appropriate list and compare strings
	for(list<string>::iterator itr = hashTable[index].begin(); 
		itr != hashTable[index].end(); itr++)
	{
		if(*itr == word)
		{
			// erase the node containing the matching word
			itr = hashTable[index].erase(itr);

			// calculate the running average list length
			runningAvgListLength = calcRunningAve();
		}

	}

}             


/**
 * @brief	prints the entire hash table
 * @param	none
 * @return  none
 */
void Hash::print()
{
	// iterate through the indices of the array
	for(int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		cout << i << ":\t";

		// iterate through the list to print strings with a given index
		for(list<string>::iterator itr = hashTable[i].begin(); 
			itr != hashTable[i].end(); itr++)
		{
			cout << *itr << ", ";

		}
		// newline at the end of each list
		cout << endl;
	}
}                   


/**
 * @brief	processes an input file and adds the words to the hash table
 * @param	string filename - a string with the name of the file containing 
 *			the data
 * @return  none
 */
void Hash::processFile(string filename)
{

	std::ifstream fin(filename);

	string str;	// holds the input string
	int index;	// holds the index
	
	while(fin.peek() != EOF)
	{
	 	// gets new word from file
	 	fin >> str;
	 	// Hash function to calculate the appropriate index
	 	index = hf(str);

	 	if(!hashTable[index].empty())
	 	{
	 		unsigned int count = 0;		// variable to hold the count 
	 		collisions++;				// increment collisions 	 		
	 		count++;					// increment count
	 		
	 		// step through the list at index and add up the additional words
	 		for(list<string>::iterator itr = hashTable[index].begin(); 
			itr != hashTable[index].end(); itr++)
			{
				count++;
			}

			// update longestList if the current count is greater 
			if(count > longestList)
			{
				longestList = count;
			}

	 	}
	 	// add the string to the index
	 	hashTable[index].push_back(str);

	 	// ignores newline character
	 	fin.ignore();

	 	// calculate the running average list length
		runningAvgListLength = calcRunningAve();

	}
 	
}       


/**
 * @brief	searches for a word in the hash table
 * @param	string word - the key value to be searched for
 * @return  true if the word is found and false if it is not found.
 */
bool Hash::search(string word)
{
	// hash the word being searched for, to get the appropriate index
	int index = hf(word);
	// boolean variable to track whether the word has been found in the list
	bool found = false;

	// iterate through the appropriate list and compare strings
	for(list<string>::iterator itr = hashTable[index].begin(); 
		itr != hashTable[index].end(); itr++)
	{
		if(*itr == word)
		{
			found = true;
		}

	}

	return found;
}             


/**
 * @brief	output entire hash table to a file, using the same format as print()
 * @param	string filename - for the output of the hash table
 * @return  none
 */
void Hash::output(string filename)
{
	ofstream fout(filename);

	// iterate through the indices of the array
	for(int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		fout << i << ":\t";

		// iterate through the list to print strings with a given index
		for(list<string>::iterator itr = hashTable[i].begin(); 
			itr != hashTable[i].end(); itr++)
		{
			fout << *itr << ", ";

		}

		// newline at the end of each list
		fout << endl;
	}
}


/**
 * @brief	prints the hash table statistics to standard output
 * @param	none
 * @return  none
 */
void Hash::printStats()
{
	int totalWords = countTotalWords();	

	cout << "Total Collisions = " << collisions << endl;
	cout << "Longest List Ever = " << longestList << endl;
	cout << "Average List Length Over Time = " << runningAvgListLength << endl;
	cout << "Load Factor = " << ((double)totalWords/HASH_TABLE_SIZE) << endl;

}


/**
 * @brief	traverses the hash table and counts the number of words
 * @param	none
 * @return  int totalWords - the final word count of the hash table
 */
int Hash::countTotalWords()
{
	int totalWords = 0; // total number of words in hash table
	
	for(int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		for(list<string>::iterator itr = hashTable[i].begin(); 
		itr != hashTable[i].end(); itr++)
		{
			totalWords++;

		}
	}

	return totalWords;

}


/**
 * @brief	traverses the hash table and counts the number of non-empty lists
 * @param	none
 * @return  int nonEmpty - the number of non-empty lists
 */
int Hash::countNonEmpty()
{
	int nonEmpty = 0; 	// number of non-empty lists

	// add up the words in the lists and number of non-empty lists
 	for(int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if(!hashTable[i].empty())
		{
			nonEmpty++;
		}

	}
	return nonEmpty;
}


/**
 * @brief	calculate the new running average length of the std::list chains
 * @param	none
 * @return  double runningAvgListLength - new average of the length of the lists
 */
double Hash::calcRunningAve()
{
	double currentAvgListLen = 0.0;	

	// calculate current average list length
	currentAvgListLen = (double)countTotalWords() / countNonEmpty();

	// update list length running average
 	return (currentAvgListLen + runningAvgListLength) / 2.0; 

}


