#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "Stack.hpp"
#include "XMLParser.hpp"
#include <fstream>

/* Provided test cases*/
TEST_CASE("XMLParser: Test int Stack push and size", "[Stack]")
{
	Stack<int> intStack;
	int testSize = 3;
	int stackSize;
	bool correctPush, correctSize;
	for (int i = 0; i < testSize; i++)
	{
		correctPush = intStack.push(i);
		stackSize = intStack.size();
		correctSize = (stackSize == (i + 1));
		if (!correctPush || !correctSize)
		{
			break;
		}
	}
	REQUIRE(correctPush);
	REQUIRE(correctSize);
}

TEST_CASE("XMLParser: Test int Stack peek and pop", "[Stack]")
{
	Stack<char> charStack;
	int testSize = 10;
	int stackSize;
	bool correctSizeAfterPush;
	for (char c = 'a'; c < 'a' + testSize; c++)
	{
		charStack.push(c);
		stackSize = charStack.size();
		correctSizeAfterPush = (stackSize == (c - 'a' + 1));
		if (!correctSizeAfterPush)
		{
			break;
		}
	} // should be 'a' to 'j'
	REQUIRE(correctSizeAfterPush);
	bool notEmptyYetAfterPop, correctItem, notEmptyYetAfterPeek;
	for (char i = 'a' + testSize - 1; i >= 'a'; i--)
	{
		notEmptyYetAfterPop = !charStack.isEmpty();
		char elem = charStack.peek();
		correctItem = (elem == i);
		notEmptyYetAfterPeek = !charStack.isEmpty();
		charStack.pop();
		if (!notEmptyYetAfterPop || !correctItem || !notEmptyYetAfterPeek)
		{
			break;
		}
	}
	REQUIRE(notEmptyYetAfterPop);
	REQUIRE(correctItem);
	REQUIRE(notEmptyYetAfterPeek);
	REQUIRE(charStack.isEmpty() == true);
}

TEST_CASE("XMLParser: Test std::string Stack peek, pop and clear", "[Stack]")
{
	Stack<std::string> stringStack;
	std::vector<std::string> vec = {"Touching", "you", "touching", "me", "sweet", "Caroline"};
	int i = 1;
	bool correctSize;
	for (std::string s : vec)
	{
		stringStack.push(s);
		correctSize = (stringStack.size() == i);
		if (!correctSize)
		{
			break;
		}
		i++;
	}
	REQUIRE(correctSize);
	bool notEmptyYetAfterPop, correctItem, notEmptyYetAfterPeek;
	for (i = 0; i < 4; i++)
	{
		notEmptyYetAfterPop = !stringStack.isEmpty();
		std::string c = stringStack.peek();
		correctItem = (c == vec[vec.size() - 1 - i]);
		notEmptyYetAfterPeek = !stringStack.isEmpty();
		stringStack.pop();
		if (!notEmptyYetAfterPop || !correctItem || !notEmptyYetAfterPeek)
		{
			break;
		}
	}
	REQUIRE(notEmptyYetAfterPop);
	REQUIRE(correctItem);
	REQUIRE(notEmptyYetAfterPeek);
	REQUIRE(stringStack.size() == 2);
	stringStack.clear();
	REQUIRE(stringStack.isEmpty() == true);
}


TEST_CASE("XMLParser: Test tokenize <test>stuff</test>", "[XMLParser]") // passed
{
	// You can assume that the beginning and the end of CONTENT will not be filled with whitespace
	XMLParser myXMLParser;
	std::string testString = "<test>stuff</test>";
	REQUIRE(myXMLParser.tokenizeInputString(testString));
	std::vector<TokenStruct> result = {TokenStruct{StringTokenType::START_TAG, std::string("test")},
																		 TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
																		 TokenStruct{StringTokenType::END_TAG, std::string("test")}};
	std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
	REQUIRE(result.size() == output.size());
	for (int i = 0; i < result.size(); i++)
	{
		REQUIRE(result[i].tokenType == output[i].tokenType);
		REQUIRE(result[i].tokenString == output[i].tokenString);
	}
}

TEST_CASE("XMLParser: Test tokenize with invalid chars", "[XMLParser]")
{
	XMLParser myXMLParser;
	std::string testString = "<test>stuff</3test>";
	REQUIRE_FALSE(myXMLParser.tokenizeInputString(testString)); // first char being number in tag

	testString = "<te$t>stuff</te$t>";                
	REQUIRE_FALSE(myXMLParser.tokenizeInputString(testString)); // $ in tag

	testString = "<test>stuff< hi/></test>";            
	REQUIRE_FALSE(myXMLParser.tokenizeInputString(testString)); // space in tag

	testString = "<start";
	REQUIRE_FALSE(myXMLParser.tokenizeInputString(testString)); // example in project description

	testString = "  >";                              
	REQUIRE_FALSE(myXMLParser.tokenizeInputString(testString));

	testString = " ";                               
	REQUIRE_FALSE(myXMLParser.tokenizeInputString(testString));

	testString = "< /end>";
	REQUIRE_FALSE(myXMLParser.tokenizeInputString(testString));

	testString = "<>";
	REQUIRE_FALSE(myXMLParser.tokenizeInputString(testString));

	testString = "<start <stuff>>";
	REQUIRE_FALSE(myXMLParser.tokenizeInputString(testString));

	testString = "</test>stuff<test>";                   
	REQUIRE(myXMLParser.tokenizeInputString(testString)); // example in project description, true even not valid
}

TEST_CASE("XMLParser: Test tokenize string with more elements", "[XMLParser]")
{
	XMLParser myXMLParser;
	std::string testString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Note src='gmail'>  <From>Tom</From> <To>Alice</To> </Note>";
	REQUIRE(myXMLParser.tokenizeInputString(testString));
	std::vector<TokenStruct> result = {TokenStruct{StringTokenType::DECLARATION, std::string("xml version=\"1.0\" encoding=\"UTF-8\"")},
																		 TokenStruct{StringTokenType::START_TAG, std::string("Note")},
																		 TokenStruct{StringTokenType::START_TAG, std::string("From")},
																		 TokenStruct{StringTokenType::CONTENT, std::string("Tom")},
																		 TokenStruct{StringTokenType::END_TAG, std::string("From")},
																		 TokenStruct{StringTokenType::START_TAG, std::string("To")},
																		 TokenStruct{StringTokenType::CONTENT, std::string("Alice")},
																		 TokenStruct{StringTokenType::END_TAG, std::string("To")},
																		 TokenStruct{StringTokenType::END_TAG, std::string("Note")}};
	std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();

	REQUIRE(result.size() == output.size());
	bool correctType, correctString;
	for (int i = 0; i < result.size(); i++)
	{
		correctType = (result[i].tokenType == output[i].tokenType);
		correctString = (result[i].tokenString.compare(output[i].tokenString) == 0);
		if (!correctType || !correctString)
		{
			break;
		}
	}
	REQUIRE(correctType);
	REQUIRE(correctString);
}


TEST_CASE("XMLParser: Test parseTokenizedInput", "[XMLParser]")
{
	XMLParser myXMLParser;
	std::string testString = "<test myattr='abcdef'>stuff<this_is_empty_tag/></test>";
	REQUIRE(myXMLParser.tokenizeInputString(testString));
	std::vector<TokenStruct> result = {TokenStruct{StringTokenType::START_TAG, std::string("test")},
																		 TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
																		 TokenStruct{StringTokenType::EMPTY_TAG, std::string("this_is_empty_tag")},
																		 TokenStruct{StringTokenType::END_TAG, std::string("test")}};
	std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
	REQUIRE(result.size() == output.size());
	REQUIRE(myXMLParser.parseTokenizedInput());
	output = myXMLParser.returnTokenizedInput();
	REQUIRE(result.size() == output.size());
	bool correctType, correctString;
	for (int i = 0; i < result.size(); i++)
	{
		correctType = (result[i].tokenType == output[i].tokenType);
		correctString = (result[i].tokenString.compare(output[i].tokenString) == 0);
		if (!correctType || !correctString)
		{
			break;
		}
	}
	REQUIRE(correctType);
	REQUIRE(correctString);
}

// Refer to online parser https://jsonformatter.org/xml-parser#Sample
TEST_CASE("XMLParser: Test XMLParser tokenize then parse various strings", "[XMLParser]")
{
	XMLParser myXMLParser;

	REQUIRE_FALSE(myXMLParser.parseTokenizedInput()); // Hint: Can't parse empty

	REQUIRE(myXMLParser.tokenizeInputString(" <someTag>Content</someTag> ")); // Hint: Tokenize then parse \" <someTag>Content</someTag> \""
	REQUIRE(myXMLParser.parseTokenizedInput());

	REQUIRE(myXMLParser.tokenizeInputString("<?xml version =\"1.0\"?><html><head>Content here</head><body>Content here<empty src=\"f\"/></body></html>"));
	REQUIRE(myXMLParser.parseTokenizedInput());

	REQUIRE(myXMLParser.tokenizeInputString("<?xml version =\"1.0\"?><head>sometext</head>\n<body>sometext</body>"));
	REQUIRE_FALSE(myXMLParser.parseTokenizedInput());
}

TEST_CASE("XMLParser: Test XMLParser parse, contains and frequency", "[XMLParser]")
{
	XMLParser myXMLParser;
	std::ifstream myfile("../TestFile.txt");
	std::string inputString((std::istreambuf_iterator<char>(myfile)), (std::istreambuf_iterator<char>()));

	REQUIRE(myXMLParser.tokenizeInputString(inputString));
	REQUIRE(myXMLParser.parseTokenizedInput());
	REQUIRE(myXMLParser.containsElementName("catalog"));
	REQUIRE(myXMLParser.frequencyElementName("catalog") == 1);
	REQUIRE(myXMLParser.containsElementName("product"));
	REQUIRE(myXMLParser.frequencyElementName("product") == 1);
	REQUIRE(myXMLParser.containsElementName("catalog_item"));
	REQUIRE(myXMLParser.frequencyElementName("catalog_item") == 2);
	REQUIRE(myXMLParser.containsElementName("item_number"));
	REQUIRE(myXMLParser.frequencyElementName("item_number") == 2);
	REQUIRE(myXMLParser.containsElementName("size"));
	REQUIRE(myXMLParser.frequencyElementName("size") == 6);
	REQUIRE(myXMLParser.containsElementName("color_swatch"));
	REQUIRE(myXMLParser.frequencyElementName("color_swatch") == 15);
}


// TEST_CASE("XMLParser: Test XMLParser with XML file workflow", "[XMLParser]")
// {
// 	// Test a workflow with a valid XML file (e.g., one Canvas page)
// 	XMLParser myParser;
// 	std::string inputString;
// 	std::ifstream myfile("../xmlFile.txt");
// 	char c;

// 	// read in the test file
// 	if (myfile.is_open())
// 	{
// 		while (!myfile.eof())
// 		{
// 			myfile.get(c);
// 			inputString.push_back(c);
// 		}
// 		myfile.close();
// 	}
// 	else
// 	{
// 		std::cout << "Unable to open (find) the input file" << std::endl;
// 	}

// 	// try to tokenize the input string      
// 	bool success = myParser.tokenizeInputString(inputString);
// 	//REQUIRE(success == true);

// 	// look at the tokenized input string
// 	std::vector<TokenStruct> tokenizedInput = myParser.returnTokenizedInput();
// 	//REQUIRE(tokenizedInput.size() == 88);

// 	// try to parse the tokenized input string to see if it is valid XML
// 	success = myParser.parseTokenizedInput();
// 	REQUIRE(success == true);

// 	// see if the element named "strong" was there
// 	success = myParser.containsElementName("strong");
// 	REQUIRE(success == true);

// 	// see how many times the element named "span" was there
// 	int number = myParser.frequencyElementName("span");
// 	REQUIRE(number == 16);
// }


/* /////////////////////// test cases above passed \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ */

/* my test cases below crafted around the other test cases on the autograder */

TEST_CASE("new autograder test cases","[XMLParser]") {
	XMLParser myXMLParser;

	// Test #16: passed
	REQUIRE_FALSE(myXMLParser.tokenizeInputString("abc")); 

	// Test #17: passed
	REQUIRE_FALSE(myXMLParser.tokenizeInputString(" \n >"));

	// Test #18: passed
	// Tokenize then parse "<?xml-script version="1.0"?><enclosed><head>Content</head><body>More Content<div>Div Content</div><empty src="dontworryaboutit"/></body></enclosed>"

	// Test #19: passed

	// Test #20: Can tokenize but cannot parse content outside of tag    passed
	// part 1: can tokenize but can't parse content outside of tags: word<someTag>Content</someTag>
	REQUIRE(myXMLParser.tokenizeInputString("word<someTag>Content</someTag>"));
	REQUIRE_FALSE(myXMLParser.parseTokenizedInput());

	// part 2: can't parse declarations inside element      passed
	REQUIRE(myXMLParser.tokenizeInputString(R"(<start><?xml version="1.0"?></start>)"));
	REQUIRE_FALSE(myXMLParser.parseTokenizedInput());

	// part 3: can't parse reversed order in "</tag>reversed<tag>"      passed
	REQUIRE(myXMLParser.tokenizeInputString("</tag>reversed<tag>"));
	REQUIRE_FALSE(myXMLParser.parseTokenizedInput());

	// part 4: can't parse standalone start tag in "<tag>"    passed
	REQUIRE(myXMLParser.tokenizeInputString("<tag>"));
	REQUIRE_FALSE(myXMLParser.parseTokenizedInput());
	
	// part 5: tokenize then parse "<empty/>\n<tag>content</tag>"          passed
	// can't parse empty tag in the front, followed by a pair of start and end tags          
	REQUIRE(myXMLParser.tokenizeInputString("<empty/>\n<tag>content</tag>"));
	REQUIRE_FALSE(myXMLParser.parseTokenizedInput());

	// part 6: tokenize then parse "<tag>content</tag><empty/>"       passed
	REQUIRE(myXMLParser.tokenizeInputString("<tag>content</tag><empty/>"));
	REQUIRE_FALSE(myXMLParser.parseTokenizedInput());

	// passed
	// part 7: can't parse two or multiple standalone empty tags: "<empty/><empty/>"
	REQUIRE(myXMLParser.tokenizeInputString("<empty/><empty/>"));
	REQUIRE_FALSE(myXMLParser.parseTokenizedInput());

	// passed
	// part 8: can't parse crossed tags "<tag1>content<tag2cross></tag1></tag2cross>"
	REQUIRE(myXMLParser.tokenizeInputString("<tag1>content<tag2cross></tag1></tag2cross>"));
	REQUIRE_FALSE(myXMLParser.parseTokenizedInput());

	// passed
	// part 9: can't tokenize "<tag1 <anothertag/>>content</tag1>" and parse
	REQUIRE_FALSE(myXMLParser.tokenizeInputString("<tag1 <anothertag/>>content</tag1>"));
	REQUIRE_FALSE(myXMLParser.parseTokenizedInput());

	// passed
	// part 10: can't parse two parallel elements without root: "<?xml version ="1.0"?><head>sometext</head>\n<body>sometext</body>"
	REQUIRE(myXMLParser.tokenizeInputString(R"(<?xml version ="1.0"?><head>sometext</head>\n<body>sometext</body>)"));
	REQUIRE_FALSE(myXMLParser.parseTokenizedInput());

	// passed
	// part 11: can't parse declaration inside root element: 
	// "<?xml version ="1.0"?><eclosed><?xml-spreadsheet?><head>sometext</head>\n<body>sometext</body></enclosed>"
	REQUIRE(myXMLParser.tokenizeInputString(R"(<?xml version ="1.0"?><eclosed><?xml-spreadsheet?><head>sometext</head>\n<body>sometext</body></enclosed>)"));
	REQUIRE_FALSE(myXMLParser.parseTokenizedInput());

	// passed
	// part 12: can't parse multiple standalone empty tags even with declaration in the front
	REQUIRE(myXMLParser.tokenizeInputString("<?xml version?><empty/><empty/>"));
	REQUIRE_FALSE(myXMLParser.parseTokenizedInput());

	// passed
	// part 13: can't parse just declaration
	REQUIRE(myXMLParser.tokenizeInputString("<?xml version?>"));
	REQUIRE_FALSE(myXMLParser.parseTokenizedInput());

	// passed
	// part 14: can't parse declaration then content then a pair of tags: <?xml version="1.1"?>content1<tag>content2</tag>
	REQUIRE(myXMLParser.tokenizeInputString(R"(<?xml version="1.1"?>content1<tag>content2</tag>)"));
	REQUIRE_FALSE(myXMLParser.parseTokenizedInput());

	// passed
	// Test #21: can tokenize but can't parse declaration + empty tag + empty tag
	REQUIRE(myXMLParser.tokenizeInputString(R"(<?xml version="1.1"?><empty/><empty/>)"));
	REQUIRE_FALSE(myXMLParser.parseTokenizedInput());

	// passed
	// part 2: can tokenize and parse declaration + empty tag
	REQUIRE(myXMLParser.tokenizeInputString(R"(<?xml version="1.1"?><empty/>)"));
	REQUIRE(myXMLParser.parseTokenizedInput());
	REQUIRE(myXMLParser.containsElementName("empty"));

	// part 3: Inside "<?xml version="1.1"?><head><xml></xml>xml<xml/><xml></xml></head>", xml count is 3, including two start tags and one empty tag
	REQUIRE(myXMLParser.tokenizeInputString(R"(<?xml version="1.1"?><head><xml></xml>xml<xml/><xml></xml></head>)"));
	REQUIRE(myXMLParser.parseTokenizedInput());
	REQUIRE(myXMLParser.frequencyElementName("xml") == 3);
 
	// Test #22: passed

	// Test #23: passed

	// Test #24:      
	myXMLParser.clear();
	myXMLParser.tokenizeInputString(R"(<?xml version="1.1"?><tag><empty/><empty/><empty/><empty/>content3<empty/><empty/><file><empty/><empty/></file>content5<empty/><empty/></tag>)");
	myXMLParser.parseTokenizedInput();
	REQUIRE(myXMLParser.containsElementName("empty"));
}

// 2 declarations, 3 empty tags, 1 content, whatever else

TEST_CASE("false and true case") {
	XMLParser myXMLparser;
	// false case
	REQUIRE(myXMLparser.tokenizeInputString(R"(<?xml?>content<?xml?><empty/><empty/><empty/>)"));
	REQUIRE_FALSE(myXMLparser.parseTokenizedInput());

	// true case
	REQUIRE(myXMLparser.tokenizeInputString(R"(<?xml?><?xml?><start><empty/><empty/><empty/>content</start>)"));
	REQUIRE(myXMLparser.parseTokenizedInput());
}


// count tags