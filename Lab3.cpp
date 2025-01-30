#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

vector<vector<int>> getKeyMatrix(string key, int n){
    vector<vector<int>> res(n, vector<int>(n, 0));
    int strInd = 0;
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            res[i][j] = (key[strInd] - 'A') % 26;
            strInd++;
        }
    }
    return res;
}

vector<vector<int>> getMessageVector(string message){
    vector<vector<int>> res(message.size(), vector<int>(1, 0));
    for(int i = 0; i<message.size(); i++){
        res[i][0] = (message[i] - 'A') % 26;
    }
    return res;
}

vector<vector<int>> encrypt(vector<vector<int>> keyMatrix, vector<vector<int>> messageVector){
    int n = keyMatrix.size();
    vector<vector<int>> cipher(n, vector<int>(1, 0));
    for(int i = 0; i<n; i++){
        for(int j = 0; j<1; j++){
            cipher[i][j] = 0;
            for(int k = 0; k<n; k++){
                cipher[i][j] += keyMatrix[i][k] * messageVector[k][j];
            }
            cipher[i][j] = cipher[i][j] % 26;
        }
    }
    return cipher;
}

int determinant(vector<vector<int>> mat, int n){
    if (n == 1) return mat[0][0];

    int det = 0;
    int sign = 1;

    for (int i = 0; i < n; i++){
        vector<vector<int>> subMat(n - 1, vector<int>(n - 1));
        for (int row = 1; row < n; row++){
            int colIndex = 0;
            for (int col = 0; col < n; col++){
                if (col == i) continue;
                subMat[row - 1][colIndex] = mat[row][col];
                colIndex++;
            }
        }
        det += sign * mat[0][i] * determinant(subMat, n - 1);
        sign = -sign;
    }

    return det;
}

vector<vector<int>> adjugateMatrix(vector<vector<int>> mat, int n){
    vector<vector<int>> adj(n, vector<int>(n, 0));

    if (n == 1) {
        adj[0][0] = 1;
        return adj;
    }

    int sign = 1;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            vector<vector<int>> subMat(n - 1, vector<int>(n - 1));
            int rowIndex = 0;
            for (int row = 0; row < n; row++){
                if (row == i) continue;
                int colIndex = 0;
                for (int col = 0; col < n; col++){
                    if (col == j) continue;
                    subMat[rowIndex][colIndex] = mat[row][col];
                    colIndex++;
                }
                rowIndex++;
            }
            adj[j][i] = sign * determinant(subMat, n - 1);
            sign = -sign;
        }
    }

    return adj;
}

vector<vector<int>> getKeyMatrixInverse(vector<vector<int>> keyMatrix, int n){
    int det = determinant(keyMatrix, n) % 26;
    if (det < 0) det += 26;

    int detInverse = -1;
    for(int i = 1; i < 26; i++){
        if((det * i) % 26 == 1){
            detInverse = i;
            break;
        }
    }

    if (detInverse == -1){
        throw invalid_argument("Key matrix is not invertible.");
    }

    vector<vector<int>> adj = adjugateMatrix(keyMatrix, n);

    vector<vector<int>> inv(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            inv[i][j] = (adj[i][j] * detInverse) % 26;
            if (inv[i][j] < 0) inv[i][j] += 26;
        }
    }
    return inv;
}

vector<vector<int>> decrypt(vector<vector<int>> keyMatrixInverse, vector<vector<int>> cipherVector){
    int n = keyMatrixInverse.size();
    vector<vector<int>> messageVector(n, vector<int>(1, 0));
    for(int i = 0; i<n; i++){
        for(int j = 0; j<1; j++){
            messageVector[i][j] = 0;
            for(int k = 0; k<n; k++){
                messageVector[i][j] += keyMatrixInverse[i][k] * cipherVector[k][j];
            }
            messageVector[i][j] = messageVector[i][j] % 26;
            if (messageVector[i][j] < 0) messageVector[i][j] += 26;
        }
    }
    return messageVector;
}

string hillCipher(string message, string key){
    int keySize = sqrt(key.size());
    if (keySize * keySize != key.size()) {
        throw invalid_argument("Key length must be a perfect square.");
    }

    vector<vector<int>> keyMatrix = getKeyMatrix(key, keySize);
    vector<vector<int>> messageVector = getMessageVector(message);
    vector<vector<int>> cipherMatrix = encrypt(keyMatrix, messageVector);

    string cipherText = "";
    for(int i = 0; i<messageVector.size(); i++){
        cipherText += cipherMatrix[i][0] + 'A'; 
    }
    return cipherText;
}

string hillCipherDecrypt(string cipherText, string key){
    int keySize = sqrt(key.size());
    if (keySize * keySize != key.size()) {
        throw invalid_argument("Key length must be a perfect square.");
    }

    vector<vector<int>> keyMatrix = getKeyMatrix(key, keySize);
    vector<vector<int>> keyMatrixInverse = getKeyMatrixInverse(keyMatrix, keySize);
    vector<vector<int>> cipherVector = getMessageVector(cipherText);
    vector<vector<int>> messageMatrix = decrypt(keyMatrixInverse, cipherVector);

    string message = "";
    for(int i = 0; i<cipherVector.size(); i++){
        message += messageMatrix[i][0] + 'A';
    }
    return message;
}

int main(){
    string message = "ACT";
    string key = "GYBNQKURP";
    
    string cipherText = hillCipher(message, key);
    cout<<"Encrypted Text: "<<cipherText<<endl;

    string decryptedText = hillCipherDecrypt(cipherText, key);
    cout<<"Decrypted Text: "<<decryptedText<<endl;

    return 0;
}
