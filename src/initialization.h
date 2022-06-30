#pragma once
#include <bitset>
#include <string>
using std::bitset;
using std::string;

typedef bitset<8> byte;
class Key_gen {

private:
	char* subkey = new char[176]{ 0 };
public:
	
	void printing(char* to_print, int size);
	char* get();
	char* xor (char* str1, char* str2);
	void rcon(char* str, int round);
	void substitue(char* str,int inverse);
	void shift_left(char* str,int shift);
	void key_expanse();
	void word_create();
	char* g_func(char* w, int x);
	byte sbox(uint32_t row, uint32_t col);
	byte inverse_sbox(uint32_t row, uint32_t col);
};
class AES {
private:
	string text;
	char block[4][4];
	char subkey[4][4];
	Key_gen ptr;
	
	void xor (char operand[4][4], char operand2[4][4]);
	void add_padding(int offset,string text_to_copy);
	void encrypt_block();
	void shift_rows_left(int shift, char* temp);
	void convert_2d(char* temp,char[4][4]);
	void mix_col();
	void printing_4(char to_print[4][4]);
	void inv_mix_col();
	char* to_oneD(char temp[4][4]);
public:
	AES(string text_);
	std::pair<char*,int> encrypt();
	char* decrypt(char* cipher,int size);
};