#include <string>
#include <cmath>
#include <iostream>
using std::string;


// for testing
#include <fstream>
using std::endl;
using std::ofstream;
using std::cout;

int hf(string); 

int main ( ) {

	string words[] = {"Nelly", "hello", "happy", "heath", "harps", "iiiii", 
				"jjjjj", "kkkkk", "lllll", "mmmmm", "nnnnn", "ooooo", "ppppp", 
				"qqqqq", "rrrrr", "sssss", "ttttt", "uuuuu"};

	for(int i = 0; i < 18; i++)
	{
		cout << "word: " << words[i] << endl;
		cout << "index: " << hf(words[i]) << endl;

	}



 }

int hf ( string ins ) {
	const double e = 2.7182818284590452353602874713527;
	const double pi = 3.14159265358979323846264338327950;
 
 	long letters[5];
 	long total = 0;

	// make each letter correspond to a number between 0 and 25
	for(int i = 0; i < 5; i++)
	{

		letters[i] = ((int)ins[i] * (97 ^ i)) + 1; //pow((int)ins[i], i + 1);

		total += (double)letters[i];
		//cout << "total of letter[" << ins[i] << "]: " << total << endl;
	}
	//cout << "total: " << total << endl;
	
	float result1 = total;
	//cout << "result1: " << result1 << endl;

	int integer = result1 / 1;
	//cout << "integer: " << integer << endl;
	
	int result2 = integer;
	//cout << "result2: " << result2 << endl;

	int result3 = result2 % 10;
	//cout << "result3: " << result3 << endl;

	
	
	return result3;
	
}