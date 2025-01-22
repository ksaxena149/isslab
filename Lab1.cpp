#include <iostream>
#include <string>
using namespace std;

string caesar_cipher_encrypt(string text, int key){
    string res = "";
    for(int i = 0; i<text.size(); i++){
        res.push_back(((text[i] - 'A' + key) % 26) + 'A');
    }
    return res;
}

string caesar_cipher_decrypt(string text, int key){
    string res = "";
    for(int i = 0; i < text.size(); i++){
        char decrypted_char = ((text[i] - 'A' - key) % 26);
        if (decrypted_char < 0) {
            decrypted_char += 26;
        }
        res.push_back(decrypted_char + 'A');
    }
    return res;
}

// caesar cipher
int main(){
    string text;
    int key;
    cout<<"Enter a string: ";
    cin>>text;
    cout<<"Enter key value: ";
    cin>>key;
    string encrypted = caesar_cipher_encrypt(text, key);
    cout<<"Encrypted Text: "<<encrypted<<endl;
    cout<<"Decrypted Text: "<<caesar_cipher_decrypt(encrypted, key);
    return 0;
}