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

// do not touch, this works!
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
	num_factorial = 0;
	words.clear();
	final_palindromes.clear();
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
    // combine the words in the string vector
    string word_combination;
    for (int i = 0; i < stringVector.size(); i++) {
        word_combination += stringVector[i];
    }
    convertToLowerCase(word_combination);

    // count the number of times each character appears (0 - 'a' through to 25 - 'z')
    int charCounts[26] = {0}; // Only lowercase letters are considered

    for (int i = 0; i < word_combination.size(); i++) {
        if (isalpha(word_combination[i])) { // checks if character is readable
            charCounts[word_combination[i] - 'a']++; // increments the specific character 
        }
    }

    // count number of characters with odd number
    int oddCount = 0;
    for (int i = 0; i < 26; i++) { // loops through the characters ('a' to 'z')
        if (charCounts[i] % 2 != 0) { // checks if the character appears 
            oddCount++;
        }
    }
    
    if (word_combination.length() % 2 == 0) { // if the length is even, all characters must appear even times
        return oddCount == 0;
    } else { // if the length is odd, only one character appear an odd number of times
        return oddCount == 1;
    }
}


bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{
	// count the amount of times characters appear in left side
	vector<int> charCounts1(26,0); // only lowercase letters are considered
	for(int i=0;i<stringVector1.size();i++) {
		for(int j=0;j<stringVector1[i].size();j++) {
			char normal_char = stringVector1[i][j];

			if(isalpha(normal_char)) {
				char lowercase_char = tolower(normal_char);
				charCounts1[lowercase_char - 'a']++;
			}
		}
	}
    
	// count the amount of times characters appear in right side
	vector<int> charCounts2(26,0); // only lowercase letters are considered
	for(int i=0;i<stringVector2.size();i++) {
		for(int j=0;j<stringVector2[i].size();j++) {
			char normal_char = stringVector2[i][j];

			if(isalpha(normal_char)) {
				char lowercase_char = tolower(normal_char);
				charCounts2[lowercase_char - 'a']++;
			}
		}
	}

	// loop through the character lists
	for(int i=0;i<26;i++) {
		if(charCounts1[i]>charCounts2[i]) { // check that characters in left side do not appear more than in right side
			return false;
		}
	}
	return true; // all characters in left substring occur in reversed order in right substring
}


// do not touch, this works!
bool FindPalindrome::add(const string & value)
{
	// convert input string to lowercase
	string input_string = value;
	convertToLowerCase(input_string);

	// verification that it is valid (if the value is a number or space, return false)
	if(!valid_word(input_string)){ // checks if the character is within the ascii value range ('a'-'z' or 'A'-'Z')
		return false;
	}

	// test if it is unique (for loop through the words vector to look for the same)
	for(int i=0;i<words.size();i++) {
		string lowercase_words = words[i];
		convertToLowerCase(lowercase_words); // you must convert the strings to lowercase
		if(input_string == lowercase_words) {
			return false; // if word already exists within
		}
	}

	// otherwise add to the palindrome
	words.push_back(input_string); // copy string into candidate vector

	// makes sure you aren't counting previous palindrome possibilities without the new string since you are adding another string
	final_palindromes.clear();
	num_factorial=0;

	// thing i learned: i was originally trying to enter in an empty vector for current and the candidates filled with the words
	// it should be the other way around like shown below
	recursiveFindPalindromes({},words); // start recursion to find if palindromes exist with this new word
	
	return true; // the input string is a palindrome
}


// do not touch, this works!
bool FindPalindrome::add(const vector<string> & stringVector)
{
	// verification that it is valid (if the value is a number or space, return false)
	for(int i=0; i<stringVector.size();i++){
		if(!valid_word(stringVector[i])){ // checks if the word is a space or within the ascii value range
			return false;
		}
	}

	// since every string is valid, copy the stringVector into a new string vector that we can modify
	vector<string> temp_vector = stringVector;

	// change string vector to lowercase
	for(int i=0;i<stringVector.size();i++) {
		string lowercase_string = temp_vector[i];
		convertToLowerCase(lowercase_string);
		temp_vector[i] = lowercase_string; // put new lowercase string in temp_vector

		// test to make sure that there aren't repeats within the stringVector
		for(int j=0;j<stringVector.size();j++) {
			if(i==j) { // if it is at its index, skip over
				continue;
			}
			if(temp_vector[i] == temp_vector[j]) { // checks the stringVector against itself to make sure there aren't repeats
				return false; // there is a duplicate in temp_vector
			}
		}		
	}

	// test if each new word added from stringVector is unique
	for(int i=0; i<words.size();i++) {
		for(int j=0;j<words.size();j++) {
			string lowercase_string = words[i];
			convertToLowerCase(lowercase_string);
			if(temp_vector[i] == lowercase_string) {
				return false;
			}
		}
	}

	// put the words in the stringVector into the words vector for portability and to be used for recursion palindrome searching
	for(int i=0;i<stringVector.size();i++) {
		words.push_back(stringVector[i]);
	}

	// makes sure you aren't counting previous add palindrome possibilities since you are adding a string vector
	final_palindromes.clear();
	num_factorial=0;

	recursiveFindPalindromes({},words); // start recursion to find if palindromes exist with these new words in stringVector

	return true; // the input string is a palindrome
}


// this does not work
vector< vector<string> > FindPalindrome::toVector() const
{
	return final_palindromes;
}

