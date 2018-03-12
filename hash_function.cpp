
/**
 * @file hash_function.cpp   
 *
 * @brief
 *	Contains the hashing algorithm for placing 5 letter words in a hash table
 *
 * @author Cole Warner
 * @date 3/5/18
 */
 
#include <string>
#include <cmath>
#include <iostream>
#include "hash.h"
using std::string;


// for testing
#include <fstream>
using std::endl;
using std::ofstream;
using std::cout;

// This is only a sample hash function (and a bad one at that). You will
// need to replace the contents of this hash function with your own 
// hash function



/* original hash function
int Hash::hf ( string ins ) {

	// place your hash function here....
	return ( (int) ins[0] ) % HASH_TABLE_SIZE;
}
*/


/**
 * @brief	my custom hash function
 * @param	string ins - a string gathered from either the remove, search, 
 *			or processFile function
 * @Return  an integer representing the index of an array; designed for a high
 * 			level of randomization
 *
 *		I started out thinking of the golden ratio theroem that used: 
 *		(1+sqrt(5))/2
 *		then continued with a mod 1 (taking advantage of the irrational number
 *		created by the golden ratio, and then multiplying by 
 *		the HASH_TABLE_SIZE.)
 *
 *		I ran into some problems with this idea (nowhere near as much 
 *		randomization as I had hoped for), so I switched gears. I knew that
 *		prime numbers are important for hash functions, so I decided to use them
 *		in a novel way: I created an array of 52 prime numbers (from 631 to 983)
 *		and decided to convert each of the 5 letters into one of the 52 prime 
 *		numbers.
 *		
 *		As I read in the letters so that each prime number is then multiplied by 
 *		one thousand raised to the power of its position in the array:
 *			i.e. 'A' (631) at the beginning of the string will be 631 * 1000^0
 *
 *		I then take this very large number and get the modulus after dividing by
 *		a large prime number (39751 - to improve randomization) and then do the
 *		same thing using HASH_TABLE_SIZE to make sure I get a number that 
 *		coresponds to an index on the hash table.
 *
 *		This approach led to pretty good results. I tested it with the hash
 *		table size being triple the number of words (load factor of 1/3rd), with 
 *		both sgb-words.txt and random.txt and the number of collisions was only 
 *		15% of the total number of words, with an average list length of 1.18.
 *		
 *		With a 50% load factor, the average list length was 1.27 and the number
 *		of collisions was only 21% of the total number of words.
*/
int Hash::hf ( string ins ) {
	
 	long total = 0;
 	long ascii = 0;
 	long prime = 0;

 	// list of 52 prime numbers
 	int primes52[] = {631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 
 		701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 
 		809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 
 		887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983};
 		


	for(int i = 0; i < 5; i++)
	{
		ascii = (int)ins[i];	// reads the ascii characters
		ascii -= 65;			// sets A to 0 and Z = 25

		if(ascii > 25)
		{
			ascii -= 6;			// sets a to 26	and z = 51
		}

		// picks the prime number from primes52 that corresponds to the 
		// character.
		prime = primes52[ascii];

		
		// Multiply the prime number by 1000 raised to the power of i (0 to 4)
		// this will place the numbers one after the other (i.e. 'AAAAA' would
		// be 631631631631631)
		
		prime = prime * pow(1000, i); 

		// add the number to the total
		total += prime;

	}

	// get the modulus of the total divided by a large prime number 
	total %= 39751; 	
	
	// return a number which can be used as the index for the hash table, which
	// depends on the size of the table
	total %= HASH_TABLE_SIZE;

	return total;
	
}




