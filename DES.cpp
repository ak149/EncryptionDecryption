#include<iostream>
#include<vector>
using namespace std;

unsigned long long int initial_permutation(unsigned long long int pt){
    vector<int> table{58, 50, 42, 34, 26, 18, 10, 2,
                      60, 52, 44, 36, 28, 20, 12, 4,
                      62, 54, 46, 38, 30, 22, 14, 6,
                      64, 56, 48, 40, 32, 24, 16, 8,
                      57, 49, 41, 33, 25, 17,  9, 1,
                      59, 51, 43, 35, 27, 19, 11, 3,
                      61, 53, 45, 37, 29, 21, 13, 5,
                      63, 55, 47, 39, 31, 23, 15, 7};
    unsigned long long int result=0;
    for(int i=0; i<64; i++){
        result<<=1;
        result+=(pt>>(64-table[i]))&1;
    }
    return result;
}

unsigned long long int final_permutation(unsigned long long int pt){
    vector<int> table{40, 8, 48, 16, 56, 24, 64, 32,
                      39, 7, 47, 15, 55, 23, 63, 31,
                      38, 6, 46, 14, 54, 22, 62, 30,
                      37, 5, 45, 13, 53, 21, 61, 29,
                      36, 4, 44, 12, 52, 20, 60, 28,
                      35, 3, 43, 11, 51, 19, 59, 27,
                      34, 2, 42, 10, 50, 18, 58, 26,
                      33, 1, 41,  9, 49, 17, 57, 25};
    unsigned long long int ciphertext=0;
    for(int i=0; i<64; i++){
        ciphertext<<=1;
        ciphertext+=(pt>>(64-table[i]))&1;
    }
    return ciphertext;
}

long long int expansion_DBox(unsigned int pt){
    vector<int> table{32,  1,  2,  3,  4,  5,
                       4,  5,  6,  7,  8,  9,
                       8,  9, 10, 11, 12, 13,
                      12, 13, 14, 15, 16, 17,
                      16, 17, 18, 19, 20, 21,
                      20, 21, 22, 23, 24, 25,
                      24, 25, 26, 27, 28, 29,
                      28, 29, 30, 31, 32,  1};

    long long int expanded=0;
    for(int i=0; i<48; i++){
        expanded<<=1;
        expanded+=(pt>>(32-table[i]))&1;
    }
    return expanded;
}

unsigned int straight_DBox(unsigned int pt){
    vector<int> table{16,  7, 20, 21, 29, 12, 28, 17,
                       1, 15, 23, 26,  5, 18, 31, 10,
                       2,  8, 24, 14, 32, 27,  3,  9,
                      19, 13, 30,  6, 22, 11,  4, 25};

    unsigned int output=0;
    for(int i=0; i<32; i++){
        output<<=1;
        output+=(pt>>(32-table[i]))&1;
    }
    return output;
}

void rotate(long long &num, int round){
    num<<=1;
    num+=(num>>28)&1;
    num&=0xfffffff;
    if(round==1 || round==2 || round==9 || round==16)
        return;
    rotate(num,1);
}

vector<long long int> generate_round_keys(unsigned long long int key_with_parity_bits){
    vector<int> parity_bit_drop_table{57, 49, 41, 33, 25, 17,  9,  1,
                                      58, 50, 42, 34, 26, 18, 10,  2,
                                      59, 51, 43, 35, 27, 19, 11,  3,
                                      60, 52, 44, 36, 63, 55, 47, 39,
                                      31, 23, 15,  7, 62, 54, 46, 38,
                                      30, 22, 14,  6, 61, 53, 45, 37,
                                      29, 21, 13,  5, 28, 20, 12,  4 };

    vector<int> compression_DBox     {14, 17, 11, 24,  1,  5,  3, 28,
                                      15,  6, 21, 10, 23, 19, 12,  4,
                                      26,  8, 16,  7, 27, 20, 13,  2,
                                      41, 52, 31, 37, 47, 55, 30, 40,
                                      51, 45, 33, 48, 44, 49, 39, 56,
                                      34, 53, 46, 42, 50, 36, 29, 32};

    long long int cipher_key=0;
    for(int i=0; i<56; i++){
        cipher_key<<=1;
        cipher_key+=(key_with_parity_bits>>(64-parity_bit_drop_table[i]))&1;
    }

    long long int left=cipher_key>>28, right=cipher_key&0xfffffff;
    vector<long long int> round_keys;
    for(int round=1; round<=16; round++){
    rotate(left, round);
    rotate(right, round);

    long long int leftright=(left<<28)+right;

    long long int round_key=0;
    for(int i=0; i<48; i++){
        round_key<<=1;
        round_key+=(leftright>>(56-compression_DBox[i]))&1;
    }
     round_keys.push_back(round_key);
    }
    return round_keys;
}

unsigned int sbox(long long int input_48bits){
    vector<vector<vector<int>>> s{
                         {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7}, //S-Box 1
                          {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
                          {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
                          {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},

                         {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10}, //S-Box 2
                          {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
                          {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
                          {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},

                         {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8}, //S-Box 3
                          {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
                          {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
                          {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},

                         {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15}, //S-Box 4
                          {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
                          {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
                          {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},

                         {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9}, //S-Box 5
                          {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
                          {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
                          {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},

                         {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11}, //S-Box 6
                          {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
                          {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
                          {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},

                         {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1}, //S-Box 7
                          {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
                          {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
                          {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},

                         {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7}, //S-Box 8
                          {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
                          {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
                          {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}
    };

    unsigned int output_32bits=0;
    for(int i=1; i<=8; i++){
        int p=(input_48bits>>(48-6*i))&0x3f;
        output_32bits+=(s[i-1][((p>>5)<<1)+(p&1)][(p&~(1<<5))>>1]<<(32-4*i));
    }
    return output_32bits;
}

unsigned int DES_function(unsigned int r, long long round_key){
    return straight_DBox(sbox((unsigned long long)expansion_DBox(r)^round_key));
}

unsigned long long int swapper(unsigned long long int input){
    return (input<<32)+(input>>32);
}

unsigned long long int mixer(unsigned long long int input, unsigned long long int roundkey){
    return ((DES_function(input&0xffffffff, roundkey)^(input>>32))<<32)+(input&0xffffffff);
}

unsigned long long int encrypt(unsigned long long int plaintext, unsigned long long int key){
    unsigned long long int ciphertext=initial_permutation(plaintext);
    vector<long long int> roundkey=generate_round_keys(key);
    for(int i=1; i<=15; i++){
        ciphertext=mixer(ciphertext, roundkey[i-1]);
        ciphertext=swapper(ciphertext);
        cout<<hex<<"Round "<<i<<" output = "<<ciphertext<<'\n';
    }
    ciphertext=mixer(ciphertext, roundkey[15]);
    cout<<hex<<"Round "<<16<<" output = "<<ciphertext<<'\n';
    ciphertext=final_permutation(ciphertext);
    return ciphertext;
}

unsigned long long int decrypt(unsigned long long int ciphertext, unsigned long long int key){
    unsigned long long int plaintext=initial_permutation(ciphertext);
    vector<long long int> roundkey=generate_round_keys(key);
    for(int i=1; i<=15; i++){
        plaintext=mixer(plaintext, roundkey[15-(i-1)]);
        plaintext=swapper(plaintext);
        cout<<hex<<"Round "<<i<<" output = "<<plaintext<<'\n';
    }
    plaintext=mixer(plaintext, roundkey[0]);
    cout<<hex<<"Round "<<16<<" output = "<<plaintext<<'\n';
    plaintext=final_permutation(plaintext);
    return plaintext;
}

int main(){
    unsigned long long int plaintext=0x123456abcd132536, key=0xaabb09182736ccdd;
    cout<<hex<<decrypt(encrypt(plaintext, key), key);
}
