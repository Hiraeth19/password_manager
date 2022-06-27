#pragma once
#include <iostream>
using std::cout;
void inline copy_string(char* destination, char* source, int length) {
    for (int i = 0; i < length; i++) {
        destination[i] = source[i];
    }
}

void inline to_hex(char to_convert) {
    uint32_t value = (int)to_convert;
    uint32_t left = value & 0xF;
    uint32_t right = value & 0xF0;
    right = right >> 4;
    cout << right << left << " ";
}