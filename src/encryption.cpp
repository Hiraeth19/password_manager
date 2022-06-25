# include <iostream>
# include <vector>
# include <string>
#include <bitset>   
#include "initialization.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::bitset;

typedef bitset<8> byte;


   
aes::aes(string text_) {
    text = text_;
}
void printing_4(char to_print[4][4]) {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            uint32_t value = (int)to_print[x][y];
            uint32_t left = value & 0xF;
            uint32_t right = value & 0xF0;
            right = right >> 4;
            cout << right << left << " ";
        }
        cout << endl;
    }
    cout << "-------------------------------------------------------" << endl;
}
    
void aes:: xor (char operand[4][4], char operand2[4][4]) {       // row wise data
    int k = 0;
    char result[4][4];
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            block[x][y] = operand[x][y] ^ operand2[x][y];
            //cout  << result[x][y] << operand[x][y] << operand2[k] << endl;
            k++;
        }
    }

}
/*
void copy_to(int x,char *temp) {
    for (int y = 0; y < 4; y++) {
        block[x][y] = temp[y];
    }
}
*/
void aes::shift_rows(int shift,char * &temp) {
    for (int x = 0; x < shift; x++) {
        ptr.shift_left(temp,8);
    }
}
void multiplication() {

}
void mix_col() {
    char multiplier[4][4] = {
        {02,03,01,01},
        {01,02,03,01},
        {01,01,02,03},
        {03,01,01,02}
    };

}
void aes::convert_2d(char *temp) {
    int k = 0;
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            subkey[y][x] = (char)temp[k];
            //cout << block[y][x];
            k++;
        }
        //cout << endl;
    }
    //printing_4(subkey);
}
void aes::working() {
    char* key = new char[16]{0};
    for (int round = 0; round < 1; round++) {      // rounds 10
        strncpy(key, ptr.get() + round * 16, 16);
        convert_2d(key);
        if (round == 0) {
            xor (block, subkey);
            printing_4(block);
        }
        char* temp = new char[4];
        for (int x = 0; x < 4; x++) {       //substitute & shifting bytes
            temp = block[x];
            ptr.substitue(temp);
            shift_rows(x, temp);
            strncpy(block[x], temp, 4);
        }
        //xor (block, subkey);
        //ptr.printing(subkey, 16);
        printing_4(block);
        
    }
    delete[]key;
}
string aes::encrypt() {
    ptr.key_expanse();
    for (int offset = 0; offset < text.length(); offset = offset + 16) {
        add_padding(offset);        // add round key with subkey 0
       // printing_4(block);
        working();
    }
    /*

    */
    return text;
}

void aes::add_padding(int offset) {
    constexpr int sizeof_block = 16;
    char* text_ = new char[sizeof_block]{0};
    strncpy(text_, text.substr(offset, 16).c_str(), sizeof_block);
       
    int k = 0;
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            block[y][x] = (char)text_[k];
            //cout << block[y][x];
            k++;
        }
        //cout << endl;
    }
  
    delete[] text_;
    text_ = nullptr;
   
}

