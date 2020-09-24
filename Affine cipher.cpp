#include <iostream>

using namespace std;

int inverse(int a, int m=26)
{
    a = a%m;
    for (int x=1; x<m; x++)
       if ((a*x) % m == 1)
          return x;
}

string encrypt(string plaintext, int k1, int k2)
{
    string ciphertext;
    for(int i=0; i<plaintext.size(); i++)
    if(plaintext[i]!=' ')
    ciphertext+=(k1*(plaintext[i]-97)+k2)%26+97;
    else ciphertext+=' ';
    return ciphertext;
}

string decrypt(string ciphertext, int k1, int k2)
{
    string plaintext;
    for(int i=0; i<ciphertext.size(); i++)
    if(ciphertext[i]!=' ')
    plaintext+=(((ciphertext[i]-97)+(26-k2))*inverse(k1))%26+97;
    else plaintext+=' ';
    return plaintext;
}

int main()
{
    string s="zebbw";
    s="rmw";
    int k1=7, k2=2, process=1;
    //cin>>process;
    if(process==0)
    cout<<encrypt(s,k1,k2);
    else if(process==1)
    cout<<decrypt(s,5,10);
    return 0;
}
