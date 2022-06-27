# include <iostream>
# include <fstream>
# include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::fstream;
using std::ios;

void error(int e){
    switch(e){
        case 1:
            cout << "There was some error in opening the manager, try again later" << endl;
            break;
        case 2:
             cout << "Sorry the key dosent exist" << endl;
             break;
}
}
int hashfunc(string key, int mode){
    int i = key.length();
    if (mode == 0)      // encryption
        return i % 19;
    else
        return (26 - (i % 19));     // decryption
}
string encrypt(string key, string value, int mode){
    int shift = hashfunc(key, mode);
    string cipher_txt;
    for(int x = 0; x < value.length(); x ++){
        if(!isalpha(value[x])){
            cipher_txt += (value[x]);
        }
        else if (isupper(value[x]))
            cipher_txt += char(int(value[x]+shift-65)%26 +65);
    // Encrypt Lowercase letters
        else
            cipher_txt += char(int(value[x]+shift-97)%26 +97);
    }
    return cipher_txt;
}

void find(string key){
    string entry;
    fstream fin;
    bool found = false;
    fin.open("cache.txt", ios::in);
    fin.seekg(0,ios::beg);
    while(!fin.eof()){
        getline(fin,entry);
        string slice1,slice2;
        int pos = entry.find("-");
        slice1 = entry.substr(0,pos);
        if(slice1 == key){
            slice2 = entry.substr(pos+1);
            slice2 = encrypt(key,slice2,1);
            cout << "Password is " << slice2<< endl;
            found = true;
        }
    }
    if(found == false){
        error(2);
    }
}
void put(string key, string value){
    fstream fout;
    fout.open("cache.txt", ios::out | ios::app);
    fout.seekp(0,ios::end);
    fout << key << "-" << value << endl;
}
void life(bool status){
    cout << "Welcome to Password manager" << endl;
    while(status){
            cout << "--------------------------------------------" << endl;
        cout << "Enter 1 for adding a new password" << endl;
        cout << "Enter 2 for retrieving an old password" << endl;
        cout << "Enter 3 for exit" << endl;
        cout << "--------------------------------------------" << endl;
        int ch;
        string key,value;
        cin >> ch;
        switch(ch){            
            case 1:         // cant add spaces in password
                cin >> key >> value;
                value = encrypt(key,value,0);
                put(key,value);
                break;
            case 2:
            {
            cin >> key;
            find(key);
            break;
            }
        
            case 3:
                status = false;
                break;
            default:
                cout << "Wrong input. Enter 1,2 or 3" << endl;
        }
    }
}
//int main(){
  //  life(true);
//}
