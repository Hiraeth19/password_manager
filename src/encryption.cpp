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
    
void AES:: xor (char operand[4][4], char operand2[4][4]) {       
    int k = 0;
    char result[4][4];
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            block[x][y] = operand[x][y] ^ operand2[x][y];
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
    char res[4][4];
    char multiplier[4] = { 0x02,0x03,0x01,0x01 };
    for (int i = 0; i < 4; ++i)
    {
        /*
        res[k][i] = GFMul(multiplier[k], block[0][i]) ^ GFMul(multiplier[k + 1], block[1][i]) ^ GFMul(multiplier[k + 2], block[2][i]) ^ GFMul(multiplier[k + 3], block[3][i]);
        k++;
        shift_rows_left(k, multiplier);
        k = k % 4;
        i = i % 4;
        */
        res[0][i] = GFMul(0x02, block[0][i]) ^ GFMul(0x03, block[1][i]) ^ block[2][i] ^ block[3][i];
        res[1][i] = block[0][i] ^ GFMul(0x02, block[1][i]) ^ GFMul(0x3, block[2][i]) ^ block[3][i];
        res[2][i] = block[0][i] ^ block[1][i] ^ GFMul(0x02,block[2][i]) ^ GFMul(0x03,block[3][i]);
        res[3][i] = GFMul(0x03,block[0][i]) ^ block[1][i] ^ block[2][i] ^ GFMul(0x02,block[3][i]);
        
    }
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            block[x][y] = res[x][y];
        }
    }
}
void AES::convert_2d(char *temp,char key[4][4]) {
    int k = 0;
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            key[y][x] = (char)temp[k];
            k++;
        }
    }
}
void AES::encrypt_block() {
    char* key = new char[16]{0};
    for (int round = 0; round <= 10; round++) {      // rounds 10
        cout << "ROUND: " << round << endl;
        copy_string(key, ptr.get() + round * 16, 16);
        convert_2d(key,subkey);
        if (round == 0) {
            xor (block, subkey);
            continue;
        }
        for (int x = 0; x < 4; x++) {                   //substitute & shifting bytes
            ptr.substitue(block[x],0);
            shift_rows_left(x, block[x]);               
        }

        if(round != 10) 
            mix_col();

        xor (subkey,block);
        printing_4(block);
    }
    delete[]key;
}
void shift_rows_right(int shift,char* str) {
    for (int x = 0; x < shift; x++) {
        uint32_t value = *((uint32_t*)str);
        uint32_t discard = 0xFF000000 & value;
        value = value << 8;
        discard = discard >> 32 - 8;
        value = value | discard;
        copy_string(str, (char*)&value, 4);
    }
}
void AES::inv_mix_col() {
    char res[4][4];
//    char multiplier[4] = {0x0E, 0x0B ,0x0D ,0x09};
//    int k = 0;
    //printing_4(block);
    for (int i = 0; i < 4; ++i)
    {
        res[0][i] = GFMul(0x0E, block[0][i]) ^ GFMul(0x0B, block[1][i]) ^ GFMul(0x0D, block[2][i]) ^ GFMul(0x09, block[3][i]);
        res[1][i] = GFMul(0x09, block[0][i]) ^ GFMul(0x0E, block[1][i]) ^ GFMul(0x0B, block[2][i]) ^ GFMul(0x0D, block[3][i]);
        res[2][i] = GFMul(0x0D, block[0][i]) ^ GFMul(0x09, block[1][i]) ^ GFMul(0x0E, block[2][i]) ^ GFMul(0x0B, block[3][i]);
        res[3][i] = GFMul(0x0B, block[0][i]) ^ GFMul(0x0D, block[1][i]) ^ GFMul(0x09, block[2][i]) ^ GFMul(0x0E, block[3][i]);
        //res[1][i] = block[0][i] ^ GFMul(0x02, block[1][i]) ^ GFMul(0x3, block[2][i]) ^GFMul(0x0D,block[3][i]);
        //res[2][i] = block[0][i] ^ block[1][i] ^ GFMul(0x02, block[2][i]) ^ GFMul(0x03, block[3][i]);
       // res[3][i] = GFMul(0x03, block[0][i]) ^ block[1][i] ^ block[2][i] ^ GFMul(0x02, block[3][i]);
    }
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            block[x][y] = res[x][y];
        }
    }
}
char* AES::decrypt(char* cipher,int size) {
    size += 10;
    char* plain_text = new char[size];
    char* key = new char[16];
    ptr.key_expanse();      // input key to decrypt
    cout << text.length() << endl;
    for (int offset = 0; offset < text.length(); offset = offset + 16) {
        convert_2d(cipher+offset,block);
        for (int round = 10; round >= 0; round--) {
            //cout << "ROUND: " << round << endl;
            copy_string(key, ptr.get() + round * 16, 16);
            convert_2d(key, subkey);
            if (round == 10) {
                xor (block, subkey);
                continue;
            }
            for (int x = 0; x < 4; x++) {                   //substitute & shifting bytes
                shift_rows_right(x, block[x]);
                ptr.substitue(block[x], 1);

            }
            xor (subkey, block);
            if (round != 0)
                inv_mix_col();

        }
        copy_string(plain_text+offset,to_oneD(block),16);      
    }
    
        delete[]key;
        //ptr.printing(plain_text,size);
        //cout << plain_text << endl;
        return plain_text;
    
}
char* AES::to_oneD(char temp[4][4]) {
    //printing_4(temp);
    int k = 0;
    char* oneD = new char[16];
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            oneD[k] = temp[y][x];
            k++;
        }
    }
    //ptr.printing(oneD, 16);
    return oneD;
}
std::pair<char*,int> AES::encrypt() {
    ptr.key_expanse();
    int size = text.length(),offset;
    int pad = size % 16;
    size = size + pad;
    char* cipher_text = new char[size];
    for (offset = 0; offset < text.length(); offset = offset + 16) {
        add_padding(offset,text);        
        encrypt_block();        // cipher text for long texts
        copy_string(cipher_text + offset, to_oneD(block),16);
        //size += 16;
    }
    ptr.printing(cipher_text, size);
    //cout << size << endl;
    return { cipher_text,size };
}

void AES::add_padding(int offset,string text_to_copy) {
    constexpr int sizeof_block = 16;
    char* text_ = new char[sizeof_block]{0};
    strncpy(text_, text_to_copy.substr(offset, 16).c_str(), sizeof_block);
       
    int k = 0;
    for (int x = 0; x < 4; x++) {               // check with padding
        for (int y = 0; y < 4; y++) {
            block[y][x] = (char)text_[k];
            k++;
        }
    }
  
    delete[] text_;
    text_ = nullptr;
   
}

