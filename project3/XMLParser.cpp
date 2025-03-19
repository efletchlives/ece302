// Project 3 -- XML Parser

/** @file XMLParser.cpp */

#include <string>
#include "XMLParser.hpp"

// default constructor
XMLParser::XMLParser() : elementNameBag(), parseStack(), tokenizedInputVector()
{
}

// Then finish this function to pass the 4th~6th unit tests
// tokenizeInputString method: returns if the tokenizing worked or not
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	int i=0;
	int length = inputString.length();
	bool valid_char = false;

	// prepare containers in the class to tokenize input string by clearing
	clear();

	
	while(i < length) {

		/* part 1: checks for valid tag and stores token */

		char current_char = inputString[i]; // stores current character

		// check for beginning of tag
		if(current_char == '<') {
			valid_char = true;
			std::string token_str; // contains the characters inside the '<' and '>' otherwise known as a token
			i++;

			// exception: tag is empty
			if (inputString[i] == '>') {
				return false;
			}

			// exception: contains an open tag '<'
			if(i >= length) {
				return false;
			}

			current_char = inputString[i];
			// loop through characters after '<' to store possible valid token
			while(current_char != '>' && i < length) {
				token_str += current_char; // add character to token (add them in a 0-index fashion, storing '<' first)
				i++;

				// exception: no '>'
				if(i >= length) {
					return false;
				}
				current_char = inputString[i];
			}


			/* part 2: checks if token is valid and stores valid tokens in vector */
			bool valid = valid_token1(token_str);
			if(valid) {
				// find type of token and store type in token
				StringTokenType type = type_token(token_str);
				TokenStruct token;
				token.tokenType = type;

				// sorted by tag
				if(type == END_TAG) {
					token_str.erase(0,1); // remove '/'
					// remove everything but tag name
					if(check_tagname(token_str) == false) {
						return false;
					}
					std::string tagname = find_tagname(token_str);
					// check tag name for invalid char
					if(valid_token2(tagname) == false) {
						return false;
					}
					token_str = tagname;
					i++;
				}

				if(type == EMPTY_TAG) {
					token_str.erase(token_str.length()-1);
					// remove everything but tag name
					if(check_tagname(token_str) == false) {
						return false;
					}
					std::string tagname = find_tagname(token_str);
					// check tag name for invalid char
					if(valid_token2(tagname) == false) {
						return false;
					}
					token_str = tagname;
					i++;
				}

				if(type == START_TAG) {
					// remove everything but tag name
					if(check_tagname(token_str) == false) {
						return false;
					}
					std::string tagname = find_tagname(token_str);
					// check tag name for invalid char
					if(valid_token2(tagname) == false) {
						return false;
					}
					token_str = tagname;
					i++;
				}

				if(type == DECLARATION) {
					// remove the question marks at beginning and end from the string
					token_str.erase(token_str.length()-1);
					token_str.erase(0,1);

					/* maybe keep idk yet, come back to fix me evan */
					// std::string tagname = find_tagname(token_str);
					// if(valid_token2(tagname) == false)  {
					// 	return false;
					// }
					// token_str = tagname;
					i++;
				}

				token.tokenString = token_str;
				tokenizedInputVector.push_back(token);
				token_str.clear(); // reset string to take in the next tag/content
			}
			else {
				return false;
			}
		}

		// exception: open tag
		else if(current_char == '>') {
			return false;
		}

		else if(current_char != '<' && current_char != 32) { // if not a space or start of tag
			valid_char = true;
			std::string content_str;
			while(current_char != '<' && i < length) {
				content_str += current_char;
				i++;
				current_char = inputString[i];
			}

			TokenStruct token;
			token.tokenType = CONTENT; // must be content since it doesn't start with '<' and it doesn't start with a space
			token.tokenString = content_str;
			tokenizedInputVector.push_back(token);
			content_str.clear(); // reset string to take in the next tag/content

		}

		// increment if only a space
		else if(current_char == ' ') {
			i++;
		}

		else {
			i++;
		}

	} // end length while loop

	if(valid_char == false){
		return false;
	}

	// exception: a content token cannot exist alone
	if(tokenizedInputVector.size() == 1 && tokenizedInputVector[0].tokenType == CONTENT) {
		return false;
	}

	token_flag = true;
	return true; // string successfully tokenized
} // end

// Then finish this function to pass the 7th~9th unit test
// parseTokenizedInput method: checks that the TokenizedInputVector follows the correct XML grammar and order
// involves pushing to and popping off the parseStack
bool XMLParser::parseTokenizedInput()
{
	int length = tokenizedInputVector.size();

	// exception: input vector has no items in it
	if(length == 0) {
		return false;
	}

	/* part 1: check that the input starts with a declaration or start tag */ 

	////////////////////// special exceptions below \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ 
	// exception: not able to be parsed if starts with something other than declaration or start tag
	else if(tokenizedInputVector[0].tokenType != DECLARATION && tokenizedInputVector[0].tokenType != START_TAG) {
		return false;
	}

	// exception: declaration is only item
	else if(tokenizedInputVector[0].tokenType == DECLARATION && length == 1) {
		return false;
	}

	// exception: declaration, followed by content, followed by tags
	else if(tokenizedInputVector[0].tokenType == DECLARATION && tokenizedInputVector[1].tokenType == CONTENT && tokenizedInputVector[2].tokenType == START_TAG) {
		return false;
	}

	// exception: declaration and empty tag only in that order is possible
	else if(tokenizedInputVector[0].tokenType == DECLARATION && tokenizedInputVector[1].tokenType == EMPTY_TAG && length == 2) {
		elementNameBag.add(tokenizedInputVector[0].tokenString);
		elementNameBag.add(tokenizedInputVector[1].tokenString);
		parse_flag = true;
		return true;
	}
	//\\\\\\\\\\\\\\\\\\\\\\ special exceptions end ///////////////////////////////////

	/* part 2: loop through the vector to check order */

	// keep track of start and end tags
	int num = 0;

	for(int i = 0; i < length; i++) {

		// check for start tag: push string to stack and add to bag
		if(tokenizedInputVector[i].tokenType == START_TAG) {
			// if previous start tags haven't been matched and the stack is empty, parsing is not possible
			if(num > 0 && parseStack.isEmpty() == true) {
				return false;
			}
			// push start tag name to stack
			parseStack.push(tokenizedInputVector[i].tokenString);
			// add tag name to bag 
			elementNameBag.add(tokenizedInputVector[i].tokenString);
			num++;

		}
		// check for end tag: pop string and check
		else if(tokenizedInputVector[i].tokenType == END_TAG) {
			// compare with end tag and start tag
			if(tokenizedInputVector[i].tokenString != parseStack.peek()) {
				return false;
			}
			// if the start and end tag are equal, pop from the stack
			else {
				parseStack.pop();
			}

		}
		// check for declaration
		else if(tokenizedInputVector[i].tokenType == DECLARATION) {
			// if the declaration is somewhere other than the 1st position
			if(!parseStack.isEmpty()) {
				return false;
			}
		}

		else if(tokenizedInputVector[i].tokenType == EMPTY_TAG) {
			if(tokenizedInputVector[i-1].tokenType == EMPTY_TAG && tokenizedInputVector[length-1].tokenType == EMPTY_TAG) {
				return false;
			}
			/*   ///////// below was added \\\\\\\\\\   */
			else if(tokenizedInputVector[length-1].tokenType == EMPTY_TAG) {
				return false;
			}
			elementNameBag.add(tokenizedInputVector[i].tokenString);
		}
	}

	// if some tags don't have an end tag
	if(!parseStack.isEmpty()) {
		return false;
	}

	// to include declarations, empty tags, and content
	// elementNameBag.clear();
	// for(int i = 0;i < length; i++) {
	// 	elementNameBag.add(tokenizedInputVector[i].tokenString);
	// }
	parse_flag = true;
	return true;
}

// clear method: clears all of the containers + flags in the class
void XMLParser::clear()
{
	// clear all containers
	elementNameBag.clear();
	parseStack.clear();
	tokenizedInputVector.clear();

	// reset flag for checking if passed
	token_flag = false;
	parse_flag = false;
}

// returnTokenizedInput method: returns tokenizedInputVector
std::vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

// containsElementName method: returns if the Bag contains the element
bool XMLParser::containsElementName(const std::string &element) const
{
	// if token and parser pass and contains the element (stack passes all items to bag)
	if(!token_flag || !parse_flag) {
		throw std::logic_error("string cannot be tokenized and/or parsed");
	}
	/* maybe needed later */
	// // if token and/or parser fail, and/or bag does not contain the element
	// if(elementNameBag.isEmpty()) {
	// 	return false;
	// }
	return elementNameBag.contains(element);
}

// frequencyElementName method: returns number of times that the specified element exists in the Bag
int XMLParser::frequencyElementName(const std::string &element) const
{
	/* exceptions begin */
	// if token and parser pass and contains element (stack passes all items to bag)
	if(!token_flag || !parse_flag) {
		throw std::logic_error("string cannot be tokenized and/or parsed");
	}
	// if bag does not contain the element
	if(elementNameBag.contains(element) == false) {
		return 0;
	}
	/* exceptions end */

	/* implemented functions to identify between the different tags/tokens */
	// add identifiers to the tags
	change_bag();

	int freq = elementNameBag.getFrequencyOf(element);

	// change the tags back to their original form
	change_back();

	return freq;
	
}
