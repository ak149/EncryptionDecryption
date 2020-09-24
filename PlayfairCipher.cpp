#include<iostream>
#include<vector>
using namespace std;

pair<int, int> getposition(vector<vector<char>> key, char c){
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            if(key[i][j]==c)
                return {i,j};
}

string encrypt(vector<vector<char>> key, string plaintext){
    string encrypted;
    char a,b;
    int i=0;
    while(i<plaintext.size()){
        a=plaintext[i];
        if(i==plaintext.size()-1 || (plaintext[i]==plaintext[i+1])){
            b='x';
            i++;
        }
        else{
            b=plaintext[i+1];
            i+=2;
            }
        pair<int, int> positiona=getposition(key, a), positionb=getposition(key, b);
        if(positiona.first==positionb.first){
                encrypted+=key[positiona.first][(positiona.second+1)%5];
                encrypted+=key[positionb.first][(positionb.second+1)%5];
        }
        else if(positiona.second==positionb.second){
                encrypted+=key[(positiona.first+1)%5][positiona.second];
                encrypted+=key[(positionb.first+1)%5][positionb.second];
        }
        else{
                encrypted+=key[positiona.first][positionb.second];
                encrypted+=key[positionb.first][positiona.second];
        }
    }
    return encrypted;
}

string decrypt(vector<vector<char>> key, string ciphertext){
    string decrypted;
    char a,b;
    int i=0;
    while(i<ciphertext.size()){
        a=ciphertext[i];
        if(i==ciphertext.size()-1 || (ciphertext[i]==ciphertext[i+1])){
            b='x';
            i++;
        }
        else{
            b=ciphertext[i+1];
            i+=2;
            }
        pair<int, int> positiona=getposition(key, a), positionb=getposition(key, b);
        if(positiona.first==positionb.first){
                if(positiona.second==0)
                    positiona.second=4;
                else positiona.second--;
                if(positionb.second==0)
                    positionb.second=4;
                else positionb.second--;
                decrypted+=key[positiona.first][positiona.second];
                decrypted+=key[positionb.first][positionb.second];
        }
        else if(positiona.second==positionb.second){
                if(positiona.first==0)
                    positiona.first=4;
                else positiona.first--;
                if(positionb.first==0)
                    positionb.first=4;
                else positionb.first--;
                decrypted+=key[positiona.first][positiona.second];
                decrypted+=key[positionb.first][positionb.second];
        }
        else{
                decrypted+=key[positiona.first][positionb.second];
                decrypted+=key[positionb.first][positiona.second];
        }
    }
    return decrypted;
}

void fillKeyMatrix(vector<vector<char>> &key, string keyword){
    keyword.append("abcdefghijklmnopqrstuvwxyz");
    vector<bool> filled(26, false);
    int index=0;
    for(int i=0; i<keyword.size(); i++){
            if(filled[keyword[i]-97]==false){
                key[index/5][index%5]=keyword[i];
                filled[keyword[i]-97]=true;
                if(keyword[i]=='i' || keyword[i]=='j'){
                    filled['i'-97]=true;
                    filled['j'-97]=true;
                }
                index++;
                }
    }
}

int main(){
    vector<vector<char>> key(5, vector<char>(5));
    fillKeyMatrix(key, "gravityfalls");
    for(int i=0; i<5; i++)
    {   for(int j=0; j<5; j++)
            cout<<key[i][j]<<' ';
        cout<<'\n';
    }
    cout<<encrypt(key,"attackatdawn");
    cout<<decrypt(key,"gffgbmgfnfaw");
}
