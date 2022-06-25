# include <iostream>
# include <vector>
# include <string>
# include <bitset> 
# include "initialization.h"
#include <sstream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::bitset;

typedef bitset<8> byte;


byte key_gen :: sbox(uint32_t row,uint32_t col) {
    byte S_Box[16][16] = {
    {0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76},
    {0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0},
    {0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15},
    {0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75},
    {0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84},
    {0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF},
    {0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8},
    {0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2},
    {0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73},
    {0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB},
    {0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79},
    {0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08},
    {0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A},
    {0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E},
    {0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF},
    {0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16}
    };
    //cout << row << " " << col<<" " << S_Box[row][col] << endl;
    return S_Box[row][col];
}
void key_gen::printing(char* to_print, int size) {
    for (int x = 0; x < size; x++) {
        //cout << (int)to_print[x] << endl;
        uint32_t value = (int)to_print[x];
        //cout << str[x];
        uint32_t left = value & 0xF;
        uint32_t right = value & 0xF0;
        right = right >> 4;
        cout <<  right <<  left <<" ";
    }
    cout <<endl<< "------------------------------------------------" << endl;
}
char* key_gen::get() {
    return subkey;
}
char * key_gen:: xor (char * str1,char* str2) {     // check XOR
    //printing(str1, 4);
    //printing(str2, 4);
    char* result = new char[4];
    for (int y = 0; y < 4; y++) {
        result[y] = str1[y] ^ str2[y];
    }
    //printing(result, 4);
    return result;
}
void key_gen::rcon(char * &str,int round) {
    char Rcon[10] = { 0x01, 0x02, 0x04, 0x08, 0x10,
                0x20, 0x40, 0x80, 0x1b, 0x36 };
    //uint32_t value = *((uint32_t*)str);
    /*unsigned long i = Rcon[round].to_ulong();
    i = i << 24;
    unsigned char c = static_cast<unsigned char>(i);
    c = Rcon[round].to_string()[0];
    // cout << (unsigned int)str[0] << endl;
    //cout << sizeof(unsigned long) << endl;
    */
    char c = Rcon[round];
    c = c ^ str[0];
    str[0] = c;
    //cout << (int)c << endl;
    //printing(str, 4);
}
void key_gen::substitue(char *&str) {
    for (int x = 0; x < 4; x++) {
        uint32_t value = (int)str[x];
        //cout << str[x];
        uint32_t left  = value & 0xF;
        uint32_t right = value & 0xF0; 
        right = right >> 4;
        byte sub = sbox(right, left);
        unsigned long i = sub.to_ulong();
        unsigned char c = static_cast<unsigned char>(i);
        str[x] = c;
    
    }
    //printing(str, 4); 
}
void key_gen::shift_left(char* &str,int shift)
{   
    uint32_t value = *((uint32_t *)str);
    uint32_t discard = 0xFF & value;
    value = value >> shift;
    discard = discard << 32 - shift;
    value = value | discard;
    strncpy(str, (char*)&value, 4);
    //printing(str, 4);

}
char * key_gen::g_func(char * w,int x) {
 
    shift_left(w,8);
    substitue(w);
    //printing(w, 4);
    rcon(w, x);
    //printing(w, 4);
    return w;
}
void key_gen::word_create() {
    char* w1 = new char[4];
    char* w2 = new char[4];
    char* w3 = new char[4];
    char* w4 = new char[4];
    char* w5 = new char[4];
    strncpy(w1, subkey, 4);
    strncpy(w2, subkey + 4, 4);
    strncpy(w3, subkey + 8, 4);
    strncpy(w4, subkey + 12, 4);
    strncpy(w5, w4, 4);
    //printing(w5, 4);
    for (int x = 0; x < 10; x++) {
        //printing(w4, 4);
        w1 = xor (g_func(w4,x), w1); 
       // printing(w1, 4);
        strncpy(subkey + (16 * (x+1)), w1, 4);
        w2 = xor (w1, w2);
        strncpy(subkey + (16 * (x+1)) + 4, w2, 4);
        //cout << x << ": ";
       // printing(w2, 4);
        w3 = xor (w2, w3);
        strncpy(subkey + (16 * (x+1)) + 8, w3, 4);
        //printing(w3, 4);
        w4 = xor (w3, w5);
        strncpy(subkey + (16 * (x+1)) + 12, w4, 4);
        //cout << "w8: ";
        //printing(w3, 4);
        //printing(w5, 4);
        strncpy(w5, w4, 4);
        //printing(subkey+16*(x),16);
    }
    delete[] w1;
    delete[] w2;
    delete[] w3;
    delete[] w4;
}
void key_gen::key_expanse() {
    strncpy(subkey, "Thats my Kung Fu", 16);      
    word_create();
    //printing(subkey, 176);
}
    


