#include <iostream>
#include <vector>
using namespace std;

string encrypt(string text, int key){
    vector<vector<char>> mat(key, vector<char>(text.size(), '#'));
    int i = 0;
    bool goDown = false;
    for(int j = 0; j<text.size(); j++){
        mat[i][j] = text[j];
        if(i == 0 || i == key - 1) goDown = !goDown;
        i += goDown ? 1 : -1;
    }

    string result;
    for(int r = 0; r<key; r++){
        for(int c = 0; c<text.size(); c++){
            if(mat[r][c] != '#'){
                result += mat[r][c];
            }
        }
    }
    return result;
}

string decrypt(string cipher, int key){
    vector<vector<char>> mat(key, vector<char>(cipher.size(), '#'));
    bool goDown = false;
    int i = 0;

    for(int col = 0; col<cipher.size(); col++){
        mat[i][col] = '_';
        if(i == 0 || i == key-1) goDown = !goDown;
        i += goDown ? 1 : -1;
    }

    int ptr = 0;
    for(int i = 0; i<key; i++){
        for(int j = 0; j<cipher.size(); j++){
            if(mat[i][j] == '_') mat[i][j] = cipher[ptr++];
        }
    }

    string res;
    goDown = false;
    i = 0;
    for(int j = 0; j<cipher.size(); j++){
        res += mat[i][j];
        if(i == 0 || i == key - 1) goDown = !goDown;
        i += goDown ? 1 : -1;
    }

    return res;
}

int main(){
    string plain_text = "supersecretmessage";
    int key = 3;
    cout<<"Plain Text: "<<plain_text<<endl;
    string cipher = encrypt(plain_text, key);
    cout<<cipher<<endl;
    plain_text = decrypt(cipher, key);
    cout<<plain_text<<endl;

    return 0;
}