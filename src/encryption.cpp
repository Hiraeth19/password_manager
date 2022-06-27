# include <iostream>
# include <vector>
# include <string>
#include <bitset>   
#include "initialization.h"
# include "Utilities.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::bitset;

typedef bitset<8> byte;


   
AES::AES(string text_) {
    text = text_;
}
void AES::printing_4(char to_print[4][4]) {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            to_hex(to_print[x][y]);
        }
        cout << endl;
    }
    cout << "-------------------------------------------------------" << endl;
}
    
void AES:: xor (char operand[4][4], char operand2[4][4]) {       // row wise data
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


void AES::shift_rows_left(int shift,char * temp) {
    for (int x = 0; x < shift; x++) {
        ptr.shift_left(temp,8);
    }
}
int GFMul(int a, int b) {
    const int overflow = 0x100, modulus = 0x11B;
    int sum = 0;
    for (int counter = 0; counter < 8;counter ++) {
        if (b & 1) sum = sum ^ a;             // if last bit of b is 1, add a to the sum
        b = b >> 1;                           // divide b by 2, discarding the last bit
        a = a << 1;                           // multiply a by 2
        if (a & overflow) a = a ^ modulus;    // reduce a modulo the AES polynomial
    }
    
    return sum;
}
void AES::mix_col() {
    char multiplier[4][4] = {
        {02,03,01,01},
        {01,02,03,01},
        {01,01,02,03},
        {03,01,01,02}
    };
    char res[4][4];
    for (int i = 0; i < 4; ++i)
    {   
        res[0][i] = GFMul(0x02, block[0][i]) ^GFMul(0x03, block[1][i])^block[2][i]^block[3][i];
        res[1][i] = block[0][i] ^ GFMul(0x02, block[1][i]) ^ GFMul(0x3, block[2][i]) ^ block[3][i];
        res[2][i] = block[0][i] ^ block[1][i] ^ GFMul(0x02,block[2][i]) ^ GFMul(0x03,block[3][i]);
        res[3][i] = GFMul(0x03,block[0][i]) ^ block[1][i] ^ block[2][i] ^ GFMul(0x02,block[3][i]);
        //ptr.to_hex(GFMul(0x02, block[i][i]) ^ GFMul(0x03, block[i][i]) ^ block[i][i] ^ block[i][i]);
    }
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            block[x][y] = res[x][y];
        }
    }
    //printing_4(block);
}
  // AES GF(2^8) representation
void AES::convert_2d(char *temp) {
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
void AES::encrypt_block() {
    char* key = new char[16]{0};
    for (int round = 0; round <= 10; round++) {      // rounds 10
        cout << "ROUND: " << round << endl;
        strncpy(key, ptr.get() + round * 16, 16);
        convert_2d(key);
        //cout << "KEY: " << endl;
        //printing_4(subkey);
        if (round == 0) {
            xor (block, subkey);
            //printing_4(block);
            continue;
        }
        //char* temp = new char[4];
        for (int x = 0; x < 4; x++) {       //substitute & shifting bytes
            //temp = block[x];
            ptr.substitue(block[x]);
            shift_rows_left(x, block[x]);            // shift rows round 8 randomly one byte lost
            //strncpy(block[x], temp, 4);
        }
        
        if(round != 10) 
            mix_col();
        xor (subkey,block);
        printing_4(block);
    }
    delete[]key;
}
string AES::encrypt() {
    ptr.key_expanse();
    for (int offset = 0; offset < text.length(); offset = offset + 16) {
        add_padding(offset);        
        encrypt_block();
    }
    return text;
}

void AES::add_padding(int offset) {
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

