# include <iostream>
# include <vector>
# include <string>
#include <bitset>   
using std ::cout;
using std ::cin;
using std ::endl;
using std ::string;
using std ::vector;
using std:: bitset;

class aes{
    string text;
    public:
     aes(string text_){
        text = text_;
    }
    string encrypt(){
        for(int offset = 0; offset < text.length();offset = offset + 16){
            cout <<padding(offset) << endl;
        }
        /*
        
        */
    }
    string padding(int offset){
        while(sizeof(text) % 16 != 0){
            text += "\0";
        }
        cout << text;
        return text.substr(offset,16);
    }
};
int main(){
    aes obj("Aarushi Chauhan is best");
    obj.encrypt();
    return 0;
}