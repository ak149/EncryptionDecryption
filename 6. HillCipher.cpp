#include<iostream>
#include<vector>
using namespace std;

int inverse(int a, int m=26)
{
    a = a%m;
    for (int x=1; x<m; x++)
       if ((a*x) % m == 1)
          return x;
}


string encode(vector<vector<int>> key, string plaintext){
    vector<int> pt(plaintext.size());
    vector<int> ct(plaintext.size(),0);
    string ciphertext;
    for(int i=0; i<pt.size(); i++)
        pt[i]=plaintext[i]-'a';
    for(int i=0; i<key.size(); i++)
        for(int j=0; j<key[0].size(); j++)
            ct[i]+=key[i][j]*pt[j];
    for(int i=0; i<ct.size(); i++)
        ciphertext+=ct[i]%26+'a';
    return ciphertext;
}

string encrypt(string plaintext, vector<vector<int>> key){
    int bogus=plaintext.size()%key.size()==0?0:key.size()-plaintext.size()%key.size();
    cout<<"Bogus = "<<bogus<<'\n';
    string ciphertext;
    for(int i=0; i<bogus; i++)
        plaintext+='z';
    for(int i=0; i<=plaintext.size()-key.size(); i+=key.size()){
        ciphertext.append(encode(key, plaintext.substr(i, key.size())));
    }
    return ciphertext;
}

vector<vector<int>> invertkey(vector<vector<int>> key){
    int d=key[0][0]*key[1][1]-key[0][1]*key[1][0];
    d=inverse(d);
    int temp=key[0][0];
    key[0][0]=key[1][1]*d%26;
    key[1][1]=temp*d%26;
    key[0][1]=(26-key[0][1])*d%26;
    key[1][0]=(26-key[1][0])*d%26;

    return key;
}

int main(){
    vector<vector<int>> key(vector<vector<int>>(2,vector<int>(2)));
    cout<<"Enter 4 numbers for key ";
    cin>>key[0][0]>>key[0][1]>>key[1][0]>>key[1][1];
    string plaintext;
    cout<<"Enter plaintext";
    cin>>plaintext;
    cout<<encrypt(encrypt(plaintext, key), invertkey(key));
}
