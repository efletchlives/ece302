#include <string>
#include <vector>
#include <iostream>
#include "FindPalindrome.hpp"

using namespace std;

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

// a helper function to check if a word is valid (isalpha but for strings)
static bool valid_word(string word) {
	for(int i=0;i<word.size();i++) { // loop through the word
		if(!isalpha(word[i])) { // check if word is a character from 'a'-'z' and 'A'-'Z'
			return false;
		}
	}
	return true; // word is valid
}

// helper function to convert string to lower case
static void convertToLowerCase(string & value)
{
	for (int i=0; i<value.size(); i++) {
		value[i] = tolower(value[i]);
	}
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(vector<string>
        candidateStringVector, vector<string> currentStringVector)
{

	// only applies when you have used all of words to form a palindrome 
	if(currentStringVector.empty()) {
		string word_combination; // create a string to store the possible palindrone combinations

		// concatenate the words together to form the palindrome
		for (int i=0;i<candidateStringVector.size();i++) {
			word_combination += candidateStringVector[i];
		}

		// then test if it is a palindrome
		if(isPalindrome(word_combination)) {
			

			// avoid adding duplicates loop below might be unnecessary
			// look through the final palindrome vector to see if the combination found already exists in the final list
			for(int i=0;i<final_palindromes.size();i++) {
				if(final_palindromes[i] == candidateStringVector) {
					return;
				}
			}

			final_palindromes.push_back(candidateStringVector); // store into the final list of palindromes since it is a palindrome
			num_factorial++; // increment number of palindromes
		}
		return; // another thing i learned: i didn't have return here so it was counting multiple of the same combination
	}

		// recursion portion (loop through each possible combination of words)
		for(int i=0;i<currentStringVector.size();i++) { // loop through the candidate vector
			swap(currentStringVector[0], currentStringVector[i]); // swap the first string with the string you are on

			vector<string> possible_candidate = candidateStringVector;
			possible_candidate.push_back(currentStringVector[0]); // add word to candidates

			vector<string> possible_current = vector<string>(currentStringVector.begin()+1,currentStringVector.end()); // create current without the character just pushed into candidates 

			recursiveFindPalindromes(possible_candidate,possible_current); // recursion to do the same with the next possible palindrome words

			swap(currentStringVector[0], currentStringVector[i]); // swap the strings back
			

			// all the stuff ive tried previously in comments
			
			// // create temporary vectors so it doesn't mess with the order and storage in the candidate and current string vectors
			// vector<string> temp_candidates = candidateStringVector;
			// vector<string> temp_current = currentStringVector;
			// temp_candidates.push_back(temp_current[i]); // push the word into the candidate vector
			// temp_current.erase(temp_current.begin()+i); // erase word from current string vector (does what the table provided says to do)
			//recursiveFindPalindromes(temp_candidates,temp_current); // recursion statement
	
			//swap(currentStringVector[0], currentStringVector[i]); // swap the word at index 0 with the word at the index to test if the switched order is a palindrome
			//candidateStringVector.push_back(currentStringVector[0]);
			//recursiveFindPalindromes(candidateStringVector,vector<string>(currentStringVector.begin()+1, currentStringVector.end()));
			//candidateStringVector.pop_back(); // remove last word
			//swap(currentStringVector[0],currentStringVector[i]); // change it back to the original order
		}
}

// private function to determine if a string is a palindrome (given, you
// may change this if you want)
bool FindPalindrome::isPalindrome(string currentString) const
{
	locale loc;
	// make sure that the string is lower case...
	convertToLowerCase(currentString);
	// see if the characters are symmetric...
	int stringLength = currentString.size();
	for (int i=0; i<stringLength/2; i++) {
		if (currentString[i] != currentString[stringLength - i - 1]) {
			return false;
		}
	}
	return true;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

// default constructor
FindPalindrome::FindPalindrome()
{
	// clear candidate + current vector to prepare for palindrome finding
	words.clear();
	final_palindromes.clear();
	num_factorial=0;
}

// destructor
FindPalindrome::~FindPalindrome()
{
	clear(); // just clear since destructor
}

// return size of candidate vector to keep track of words in palindrome
int FindPalindrome::number() const
{
	return num_factorial; // N! number of palindrome possiblities with the words currently in final_palindrome
}

// clear the private members
void FindPalindrome::clear()
{
	words.clear();
	final_palindromes.clear();
	num_factorial = 0; // reset number of palindromes to 0
}

// checks that only one character at most can appear an odd number of times and that the characters on each side match respectively
bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	// use modulus to test if even or odd
	// if stringVector is even
	if(stringVector.size() % 2 == 0) { // if string is even
		for(int i=0;i<(stringVector.size()/2);i++) { // loop through the right side of the palindrome
				// compare opposite characters (left side to right side)
				if(stringVector[i] != stringVector[stringVector.size()-1-i]) { // if the characters don't match, it is not a palindrome
					return false;
				}
		}
		return true;
	}

	// if stringVector is odd 
	else {
		
		int middle_count = 0; // counter for middle character
		int odd_count = 0; // counts how many strings appear an odd number of times

		for(int i=0;i<(stringVector.size()/2);i++) {
				// compare the characters minus the middle character (left side to right side)
				if(stringVector[i] != stringVector[stringVector.size()-1-i]) {
					return false;
				}
		}

		// store the middle character 
		string middle_char = stringVector[stringVector.size()/2];

		// count times that the middle character appears
		for(int i=0;i<stringVector.size();i++) {
			// testing for middle character
			if(stringVector[i] == middle_char) {
				middle_count++;
			}
		}

		// check if middle character appears odd number of times
		if(middle_count % 2 == 1){
			return true;
		}

		// check if there is more than one character that appears odd number of times
		int count = 0;
		for(int i=0; i<stringVector.size();i++) {
			for(int j=0;j<stringVector.size();j++) {
				// direct comparison
				if(stringVector[i] == stringVector[j]) {
					count++;
				}
			}
		}

		if(count % 2 == 1) {
			odd_count++;
		}

		// if more than one string appears an odd number of times
		if(odd_count > 1) {
			return false;
		}

		return true;
	}
}

// DO THIS!!!!
bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{
	// TODO need to implement this...
	return false;
}

bool FindPalindrome::add(const string & value)
{
	// makes sure you aren't counting previous add palindrome possibilities since you are adding another string
	final_palindromes.clear();
	num_factorial=0;

	// verification that it is valid (if the value is a number or space, return false)
	if(!valid_word(value)){ // checks if the character is within the ascii value range ('a'-'z' or 'A'-'Z')
		return false;
	}

	std::vector<std::vector<std::string>> value_cutTest = {{value}};
	if(!cutTest1(value_cutTest[0])) {
		return false;
	}
	// that's what the recursion is for
	// // check if string is a palindrome
	// if(!isPalindrome(value)) {
	// 	return false;
	// }

	// otherwise add to the palindrome
	words.push_back(value); // copy string into candidate vector

	// thing i learned: i was originally trying to enter in an empty vector for current and the candidates filled with the words
	// it should be the other way around like shown below
	recursiveFindPalindromes({},words); // start recursion to find if palindromes exist with this new word
	
	return true; // the input string is a palindrome
}

bool FindPalindrome::add(const vector<string> & stringVector)
{
	// makes sure you aren't counting previous add palindrome possibilities since you are adding a string vector
	final_palindromes.clear();
	num_factorial=0;

	// verification that it is valid (if the value is a number or space, return false)
	for(int i=0; i<stringVector.size();i++){
		if(!valid_word(stringVector[i])){ // checks if the word is a space or within the ascii value range
			return false;
		}
	}

	// put the words in the stringVector into the words vector for portability and to be used for recursion palindrome searching
	for(int i=0;i<stringVector.size();i++) {
		words.push_back(stringVector[i]);
	}

	recursiveFindPalindromes({},words); // start recursion to find if palindromes exist with these new words in stringVector

	return true; // the input string is a palindrome
}

vector< vector<string> > FindPalindrome::toVector() const
{
	return final_palindromes;
}

