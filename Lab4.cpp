#include <iostream>
using namespace std;

int getInd(char c){
    return c - 'A';
}

char getAscii(int c){
    return c + 'A';
}

string getNewKey(string key, int length){
    int i = 0;
    string res;
    while(i<length){
        if(i == key.size()){
            i = 0;
        }
        res.push_back(key[i]);
        i++;
    }
    return res;
}

string encrypt(string text, string key){
    string res;
    for(int i = 0; i<text.size(); i++){
        int c = (getInd(text[i]) + getInd(key[i])) % 26;
        res.push_back(getAscii(c));
    }
    return res;
}

string decrypt(string cipher, string key){
    string res;
    for(int i = 0; i<cipher.size(); i++){
        int num = getInd(cipher[i]) - getInd(key[i]);
        if(num<0){
            num += 26;
        }
        char c = getAscii(num % 26);
        res.push_back(c);
    }
    return res;
}

int main(){
    string text;
    cout<<"Enter Plain Text: ";
    cin>>text;
    string key;
    cout<<"Enter Key: ";
    cin>>key;
    key = getNewKey(key, text.size());
    string cipher = encrypt(text, key);
    string pText = decrypt(cipher, key);
    cout<<cipher<<endl;
    cout<<pText<<endl;
    
    return 0;
}