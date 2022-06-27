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
	void rcon(char* str, int round);
	void substitue(char* str);
	void shift_left(char* str,int shift);
	void key_expanse();
	void word_create();
	char* g_func(char* w, int x);
};
class AES {
private:
	string text;
	char block[4][4];
	char subkey[4][4];
	key_gen ptr;
	
	void xor (char operand[4][4], char operand2[4][4]);
	void add_padding(int offset);
	void encrypt_block();
	void shift_rows_left(int shift, char* temp);
	void convert_2d(char* temp);
	void mix_col();
	void printing_4(char to_print[4][4]);
public:
	AES(string text_);
	string encrypt();

};