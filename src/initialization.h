#pragma once
#include <bitset>
#include <string>
using std::bitset;
using std::string;

typedef bitset<8> byte;
class key_gen {

private:
	char* subkey = new char[176]{ 0 };
public:
	
	void printing(char* to_print, int size);
	byte sbox(uint32_t row, uint32_t col);
	char* get();
	char* xor (char* str1, char* str2);
	void rcon(char*& str, int round);
	void substitue(char*& str);
	void shift_left(char*& str,int shift);
	void key_expanse();
	void word_create();
	char* g_func(char* w, int x);
};
class aes {
private:
	string text;
	char block[4][4];
	char subkey[4][4];
	key_gen ptr;
public:
	aes(string text_);
	void xor (char operand[4][4], char operand2[4][4]);
	void add_padding(int offset);
	string encrypt();
	void working();
	void shift_rows(int shift, char*& temp);
	void convert_2d(char* temp);
};