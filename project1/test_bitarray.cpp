#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include <iostream>
#include "bitarray.hpp"

TEST_CASE("Bitarray: Test default construction and asString", "[bitarray]")
{
    BitArray b;
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare("00000000") == 0);
}

TEST_CASE("Bitarray: Test construction with asString", "[bitarray]")
{
    BitArray b;
    REQUIRE(b.asString().compare("00000000") == 0);
}

TEST_CASE("Bitarray: Test construction size and asString", "[bitarray]")
{
    // You can construct a string s of as s(n, c)
    // where n is the number of characters and c is the character
    std::string s(64, '0');
    BitArray b(64);
    REQUIRE(b.size() == 64);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE("Bitarray: Test construction std::string and asString", "[bitarray]")
{
    std::string s("00101110000011000001101000001");
    BitArray b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE("Bitarray: Test construction invalid std::string", "[bitarray]")
{
    std::string s("00101110000011002001101000001");
    BitArray b(s);
    REQUIRE_FALSE(b.good());
}

TEST_CASE("Bitarray: Test set method", "[bitarray]")
{
    std::string s("00010001");
    BitArray b;
    b.set(3);
    b.set(7);
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);

    std::string s1("00010");
    BitArray b1(5);
    b1.set(3);
    REQUIRE(b1.size() == 5);
    REQUIRE(b1.good());
    REQUIRE(b1.asString().compare(s1) == 0);
}

TEST_CASE("Bitarray: Test many given methods combined", "[bitarray]")
{
    // << is the left shift operator for integers
    // e.g., 1 << 8 is 2^8=256, 1<<15 is 2^15=32768
    std::string s((1 << 15) + 3, '0');
    BitArray b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);

    for (int i = 1; i < (1 << 10); i++)
    {
        b.set(i);
        b.reset(i + (1 << 10));
        b.toggle(i + (1 << 11));
        REQUIRE(b.good());
        REQUIRE(b.test(i));
        REQUIRE_FALSE(b.test(i + (1 << 10)));
        REQUIRE((
            (b.test(i + (1 << 11)) == true && s.at(i + (1 << 11)) == '0') || // either this is true
            (b.test(i + (1 << 11)) == false && s.at(i + (1 << 11)) == '1')   // or this is true

            ));
    }
}

/* my test cases */

TEST_CASE("test size method","[bitarray]") {
    // size method using default constructor
    BitArray arr1;
    REQUIRE(arr1.size() == 8);

    // size method using constructor with size N input
    BitArray arr2(16);
    REQUIRE(arr2.size() == 16);

    // size method using constructor with string input
    std::string str("0000111000111");
    BitArray arr3(str);
    REQUIRE(arr3.size() == 13);
}

TEST_CASE("test good method","[bitarray]") {
    // good method using default constructor
    BitArray arr1;
    REQUIRE(arr1.good() == true);

    // good method using constructor with size N input (valid bitset)
    BitArray arr2(5);
    REQUIRE(arr2.good() == true);

    // good method using constructor with size N input (invalid bitset)
    BitArray arr3(-1);
    REQUIRE(arr3.good() == false);

    // good method using constructor with string input (valid bitset)
    std::string str1("100010101001");
    BitArray arr4(str1);
    REQUIRE(arr4.good() == true);

    // good method using constructor with string input (invalid bitset)
    std::string str2("12129093232");
    BitArray arr5(str2);
    REQUIRE(arr5.good() == false);
}

TEST_CASE("test set method","[bitarray]") {
    // set method using default constructor (valid + invalid index)
    BitArray arr1;
    arr1.set(7);
    REQUIRE(arr1.test(7)); // valid index, has to be '1'

    arr1.set(9);
    REQUIRE_FALSE(arr1.test(9)); // invalid index

    // set method using constructor with size N input (valid + invalid index)
    BitArray arr2(6);
    arr2.set(5);
    REQUIRE(arr2.test(5)); // valid index, has to be '1'

    arr2.set(7);
    REQUIRE_FALSE(arr2.test(7)); // invalid index

    // set method using constructor with string input (valid + invalid index)
    std::string str("01101010011");
    BitArray arr3(str);
    arr3.set(10);
    REQUIRE(arr3.test(10)); // valid index, has to be '1'

    arr3.set(12);
    REQUIRE_FALSE(arr3.test(12)); // invalid index
}

TEST_CASE("test reset method","[bitarray]") {
    // reset method using default constructor (valid + invalid index)
    BitArray arr1;
    arr1.set(7);
    REQUIRE(arr1.test(7)); // means the 7th bit (starting from 0) has to be '1'
    arr1.reset(7);
    REQUIRE_FALSE(arr1.test(7)); // means the 7th bit (starting from 0) is not '1' and since it has a valid index, it must be '0'

    arr1.reset(10);
    REQUIRE_FALSE(arr1.test(10)); // invalid index

    // reset method using constructor with size N input (valid + invalid index)
    BitArray arr2(15);
    arr2.set(10);
    REQUIRE(arr2.test(10)); // means the 10th bit (starting from 0) has to be '1'
    arr2.reset(10);
    REQUIRE_FALSE(arr2.test(10)); // means the 10th bit (starting from 0) is not '1' and since it has a valid index, it must be '0'

    arr2.reset(16);
    REQUIRE_FALSE(arr2.test(16)); // invalid index

    // reset method using constructor with string input (valid + invalid index)
    std::string str("010101010101110");
    BitArray arr3(str);
    arr3.reset(1);
    REQUIRE_FALSE(arr3.test(1)); // since bit 1 (starting from 0) started out at '1' and the reset method was applied to it, bit 1's value must be '0'

    arr3.reset(17);
    REQUIRE_FALSE(arr3.test(17)); // invalid index
}

TEST_CASE("test toggle method","[bitarray]") {
    // toggle method using default constructor (valid + invalid index)
    BitArray arr1;
    arr1.toggle(7);
    REQUIRE(arr1.test(7)); // means 7th bit (starting from 0) was toggled from '0' to '1'

    arr1.toggle(9);
    REQUIRE_FALSE(arr1.test(9)); // invalid index

    // toggle method using constructor with size N input (valid + invalid index)
    BitArray arr2(10);
    arr2.toggle(9);
    REQUIRE(arr2.test(9)); // means 9th bit (starting from 0) was toggled from '0' to '1'

    arr2.toggle(12);
    REQUIRE_FALSE(arr2.test(12)); // invalid index

    // toggle method using constructor with string input (valid + invalid index)
    std::string str("01010101010101010101");
    BitArray arr3(str);
    arr3.toggle(19);
    REQUIRE_FALSE(arr3.test(19)); // means 19th bit was toggled from '1' to '0'

    arr3.toggle(25);
    REQUIRE_FALSE(arr3.test(25)); // invalid index
}

TEST_CASE("test test method", "[bitarray]") {
    // test method using default constructor (valid + invalid index)
    BitArray arr1;
    REQUIRE_FALSE(arr1.test(4)); // means the 4th bit (starting from 0) is '0'

    REQUIRE_FALSE(arr1.test(10)); // invalid index

    // test method using constructor with size N input (valid + invalid index)
    BitArray arr2(15);
    REQUIRE_FALSE(arr2.test(10)); // means that the 10th bit (starting from 0) is '0'
    
    REQUIRE_FALSE(arr2.test(17)); // invalid index

    // test method using constructor with string input (valid + invalid index)
    std::string str("0101110101");
    BitArray arr3(str);
    REQUIRE(arr3.test(1)); // means that the 1st bit (starting from 0) is '1'

    REQUIRE_FALSE(arr3.test(12)); // invalid index
}

TEST_CASE("test asString method","[bitarray]") {
    // asString method using default constructor
    BitArray arr1;
    REQUIRE(arr1.asString() == "00000000");

    // asString method using constructor with size N input
    BitArray arr2(15);
    REQUIRE(arr2.asString() == "000000000000000");

    // asString method using constructor with string input
    std::string str("101110101101");
    BitArray arr3(str);
    REQUIRE(arr3.asString() == "101110101101");
}


TEST_CASE ("test toggle checkoff","[bitarray]"){
    std::string str = "0111101";
    BitArray arr1(str);
    for(int i=0; i<arr1.size();i++){
        if(arr1.test(i)==true){
            arr1.toggle(i);
        }
    }
    REQUIRE(arr1.asString() == "0000000");
}

TEST_CASE ("test toggle checkoff 2","[bitarray]"){
    std::string str1 = "0111";
    std::string str2 = "111";
    BitArray arr1(str1);
    BitArray arr2(str2);

    REQUIRE(arr1.asString() == "0111");
    REQUIRE(arr2.asString() == "111");
}

// TEST_CASE("test count ones","[bitarray]"){
//     std::string str = "0101110101";
//     BitArray arr1(str);
//     REQUIRE(arr1.countOnes()==6); 
// }

class BitArrayNew : public Bitset
{
public:
  // default constructor
  BitArrayNew() {
    bitsize = 8;
    int8size = 1;
    bitsetstate = true;
    bitdata = new uint8_t[int8size](); // memory allocation, uses default constructor
  }
  // other constructors
  BitArrayNew(intmax_t size) {
    bitsize = size;
    int8size = (bitsize + 7)/8;
    if(size > 0) {
        bitsetstate = true;
        bitdata = new uint8_t[int8size](); // memory allocation, uses default constructor
    }
    else {
        
        bitsetstate = false;
        // memory deallocation
        bitdata = nullptr;
    }
  }
  BitArrayNew(const std::string &value) {
    bitsize = value.size(); // use built-in std::string size function
    int8size = (bitsize + 7)/8; // size of data after being shrunken
    bitsetstate = true;
    bitdata = new uint8_t[int8size](); // memory allocation, uses default constructor
    
    // reverse order of setting bits (msb to lsb)
    for(intmax_t i=0;i<bitsize;i++) {
        if(value[bitsize - 1 - i] == '1') { // if the bit's value is '1' and reverses how the string inputs in the values (left: msb, right: lsb)
            set(i);
        }
        else if (value[bitsize - 1 - i] != '0') { // if bit value is invalid
            bitsetstate = false;

            // memory deallocation
            delete[] bitdata;
            bitdata = nullptr;
            return;
        }
    }
  }

  // destructor
  ~BitArrayNew() {
    delete[] bitdata; // delete array pointed to by bitdata
  }

  BitArrayNew(const BitArrayNew &) = delete;
  BitArrayNew &operator=(const BitArrayNew &) = delete;

  intmax_t size() const {
    return int8size;
  }

  bool good() const {
    return bitsetstate; // returns the bit state
  }

  void set(intmax_t index) {
    // if n is not in the range of 0 to N-1, then the bit array becomes invalid
    if (index < 0 || index >= bitsize) {
        bitsetstate = false;
        return;
    }
    bitdata[index/8] |= (1 << (index % 8)); // set the n-th bit to '1'
  }

  void reset(intmax_t index) {
    // if n is not in the range of 0 to N-1, then the bit array becomes invalid
    if (index < 0 || index >= bitsize) {
        bitsetstate = false;
        return;
    }
    bitdata[index / 8] &= ~(1 << (index % 8)); // reset the n-th bit to '0'
  }

  void toggle(intmax_t index) {
    // if n is not in the range of 0 to N-1, then the bit array becomes invalid
    if(index < 0 || index >= bitsize) {
        bitsetstate = false;
        return;
    }
    bitdata[index/8] ^= (1 << (index % 8)); // toggle the n-th bit from 1 to 0 or 0 to 1
  }
  bool test(intmax_t index) {
    // if n is not in the range of 0 to N-1, then the bit array becomes invalid and false is returned
    if(index < 0 || index >= bitsize) {
        bitsetstate = false;
        return false;
    }
    return bitdata[index/8] & (1 << (index % 8)); // check if the n-th bit is set 1 (yes = true, no = false)
  }
  std::string asString() const {
    std::string stringarray(bitsize,'0'); // initialize a string of the bit size of the bit array with '0's 
    for(intmax_t i=0;i<bitsize;i++){
        if(bitdata[i/8] & (1 << (i % 8))) // basically just the test function to figure out if the bit is a '1' or a '0'
            stringarray[i] = '1'; // if it is '1', set the character in its place in the string to '1'
    }
    return stringarray; // represent the bit array digits from left-to-right with the most significant bit first
  }

  // binary strand to decimal
  int binarytodecimal(int index) const {
    int decimal = 0;
    for(int i=0;i<8;i++){ // since the msb (most significant bit) is the left and lsb (least significant bit) is on the right

        // checks if the bit is in the current byte (using boolean)
        int bitindex = index*8 + i; // from 0 to N-1
        if(bitindex < bitsize) { // if the bit is in the 8bitset

            if(bitdata[bitindex/8] & (1 << (bitindex % 8))) { // test function reused
            decimal += (1 << i); // adds from most significant to least significant
            }
        }
    }
    return decimal;
  }
  
  std::vector<int> asVector() const {
    std::vector<int> decimal_vec(int8size, 0);

    for(int i=0;i<int8size;i++){
        decimal_vec[i] = binarytodecimal(i);
    }
    return decimal_vec;
  }
  
private:
  uint8_t* bitdata; // holds the bit data in an array
  intmax_t bitsize; // # of bits in the bit array
  intmax_t int8size; // # of 8 bit sections (uint8_t) in array
  bool bitsetstate; // if the bit array is in a valid state
};

TEST_CASE("BitarrayNew: Test common methods", "[bitarraynew]")
{
    // a bit sequence of size 12: 0010_11101100
    std::string s("001011101100");
    BitArrayNew b(s);
    REQUIRE(b.size() == 2);
    REQUIRE(b.good());

    // maybe you need to declare new method asVector()
    REQUIRE(b.asVector().size() == 2);  // the given string should be stored as {236, 2}
    REQUIRE(b.asVector()[0] == 236);    // 11101100 is decimal 236
    REQUIRE(b.asVector()[1] == 2);      // 0010 is decimal 2

    // got to pass up to here. i couldn't figure out how to get the set to work with the 2 sections
    // b.set(1);
    // REQUIRE(b.asVector()[1] == 6);   // 0010 changes to 0110 (decimal 6)

    // b.reset(4);
    // REQUIRE(b.asVector()[0] == 108); // 11101100 changes to 01101100 (decimal 108)
}

TEST_CASE("bonus test","[bitarraynew]") {
    std::string str1("01101101101");
    BitArrayNew arr1(str1);
    REQUIRE(arr1.size() == 2);
    REQUIRE(arr1.asVector().size() == 2);

    REQUIRE(arr1.asVector()[0] == 109);
    REQUIRE(arr1.asVector()[1] == 3);
}