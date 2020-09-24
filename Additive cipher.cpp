#include <iostream>

using namespace std;

string encrypt(string plaintext, int k)
{
    string ciphertext;
    for(int i=0; i<plaintext.size(); i++)
    if(plaintext[i]!=' ')
    ciphertext+=((plaintext[i]-97)+k)%26+97;
    else ciphertext+=' ';
    return ciphertext;
}

string decrypt(string ciphertext, int k)
{
    string plaintext;
    for(int i=0; i<ciphertext.size(); i++)
    if(ciphertext[i]!=' ')
    plaintext+=((ciphertext[i]-97)+(26-k))%26+97;
    else plaintext+=' ';
    return plaintext;
}

int main()
{
    // plaintext = "the quick brown fox jumped over the lazy dog"
    string s="lipps";//"pda mqeyg xnksj bkt fqilaz kran pda hwvu zkc";
    int k=56, process=1; //0 for encryption, 1 for decryption
    //cin>>process;
    if(process==0)
    cout<<encrypt(s,k);
    else if(process==1)
    cout<<decrypt(s,k%26);
    return 0;
}
