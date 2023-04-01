// Doruk Dulger

#include "BitRepresentation.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
BitRepresentation<T>::BitRepresentation(vector<bool> v){
    data = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i]) {
            data = data | (1 << i);
        }
    }
}

template <typename T>
string BitRepresentation<T>::getBinary() {
    string result;
    for (int i = 0; i < sizeof(T) * 8; i++) {
       // int x = (1 << i);
        if (data & (1 << i)) {
            result = "1" + result;
        } else {
            result = "0" + result;
        }
    }
    return result;
}

template <typename T>
string BitRepresentation<T>::getHexadecimal() {
    string result;
    for (int i = 0; i < sizeof(T) * 8; i += 4) {
        int n = 0;
        for (int j = 0; j < 4; j++) {
            if (data & (1 << (i + j))) {
                n = n | (1 << j);
            }
        }
        if (n < 10) {
            result = char(n + '0') + result;
        } else {
            result = char(n - 10 + 'A') + result;
        }
    }
    return result;
}

template <typename T>
void BitRepresentation<T>::setBit(unsigned int location) {
        if (location < sizeof(T) * 8) {
            data = data | (1 << location);
        }
    }

template <typename T>
void BitRepresentation<T>::unsetBit(unsigned int location) {
    if (location >= sizeof(T) * 8) {
        return;
    }
    data = data & ~(1 << location);
}

    
template <typename T>
bool BitRepresentation<T>::isBitSet(unsigned int location) {
    if (location >= sizeof(T) * 8) {
        return false;
    }
    return (data & (1 << location)) != 0;
}
