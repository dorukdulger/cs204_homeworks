// Doruk Dulger

#ifndef BitRepresentation_h
#define BitRepresentation_h

#include <string>
#include <vector>

using namespace std;

template <typename T>
class BitRepresentation {
public:
    BitRepresentation(T number) : data(number) {}
    BitRepresentation(vector<bool> v);
    string getBinary();
    string getHexadecimal();
    void setBit(unsigned int location);
    void unsetBit(unsigned int location);
    bool isBitSet(unsigned int location);
    T getNumber(){return data;}
private:
    T data;
};

//#include "BitRepresentation.cpp"

#endif /* BitRepresentation_h */
