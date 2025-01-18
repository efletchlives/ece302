#include "bitarray.hpp"
#include <stdexcept>
#include <cstring>

// default constructor of a valid 8bit array, with all bits set to 0
BitArray::BitArray() {
    bitsize = 8;
    bitsetstate = true;
    bitdata = new uint8_t[(bitsize + 7)/8](); // memory allocation, uses default constructor
}

// constructor of a valid bit array of size N, with all bits set to 0
BitArray::BitArray(intmax_t size) {
    bitsize = size;
    bitsetstate = true;

    if(size <= 0) {
        bitsetstate = false;

        // memory deallocation
        bitdata = nullptr;
    }
    else {
        bitdata = new uint8_t[(bitsize + 7)/8](); // memory allocation, uses default constructor
    }
}

// constructor of a valid bit array initialized with a string of 8bits
BitArray::BitArray(const std::string & value) {
    bitsize = value.size(); // use built-in std::string size function
    bitsetstate = true;
    bitdata = new uint8_t[(bitsize + 7)/8](); // memory allocation, uses default constructor
    
    for(intmax_t i=0;i<bitsize;i++) {
        if(value[i] == '1') { // if the bit's value is '1' 
            set(i);
        }
        else if (value[i] != '0') { // if bit value is invalid
            bitsetstate = false;

            // memory deallocation
            delete[] bitdata;
            bitdata = nullptr;
            return;
        }
    }
}

// destructor
BitArray::~BitArray() {
    delete[] bitdata; // delete array pointed to by bitdata
}

// size function 
intmax_t BitArray::size() const {
    return bitsize; // returns the current size of the bit array
}

bool BitArray::good() const {
    return bitsetstate; // returns the bit state
}

// set a bit with in the bit array at the specified index
void BitArray::set(intmax_t index) {
    // if n is not in the range of 0 to N-1, then the bit array becomes invalid
    if (index < 0 || index >= bitsize) {
        bitsetstate = false;
        return;
    }
    bitdata[index/8] |= (1 << (7 - (index % 8))); // set the n-th bit to '1'
}

// reset the bit at the specified index
void BitArray::reset(intmax_t index) {
    // if n is not in the range of 0 to N-1, then the bit array becomes invalid
    if (index < 0 || index >= bitsize) {
        bitsetstate = false;
        return;
    }
    bitdata[index / 8] &= ~(1 << (7 - (index % 8))); // reset the n-th bit to '0'
}

// toggles the n-th bit (1 to 0 or 0 or 1)
void BitArray::toggle(intmax_t index) {
    // if n is not in the range of 0 to N-1, then the bit array becomes invalid
    if(index < 0 || index >= bitsize) {
        bitsetstate = false;
        return;
    }
    bitdata[index/8] ^= (1 << (7 - (index % 8))); // toggle the n-th bit from 1 to 0 or 0 to 1
}

bool BitArray::test(intmax_t index) {
    // if n is not in the range of 0 to N-1, then the bit array becomes invalid and false is returned
    if(index < 0 || index >= bitsize) {
        bitsetstate = false;
        return false;
    }
    return bitdata[index/8] & (1 << (7 - (index % 8))); // check if the n-th bit is set 1 (yes = true, no = false)
}

std::string BitArray::asString() const {
    std::string stringarray(bitsize,'0'); // initialize a string of the bit size of the bit array with '0's 
    for(intmax_t i=0;i<bitsize;i++){
        if(bitdata[i/8] & (1 << (7 - (i % 8)))) // basically just the test function to figure out if the bit is a '1' or a '0'
            stringarray[i] = '1'; // if it is '1', set the character in its place in the string to '1'
    }
    return stringarray; // represent the bit array digits from left-to-right with the most significant bit first
}
