#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <bitset>
using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    string ENCRYPT;
    getline(cin, ENCRYPT);
    stringstream ss(ENCRYPT);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string>vsstring(begin, end);
    string DECRYPT = "";
    string ascii;
    for(int i = 0; i < vsstring.size(); i++){
        if(i == 0 || (i % 2) == 0){
            if(vsstring[i] == "0")
                DECRYPT += "1";
            else
                DECRYPT += "0";
        }else{
            string nbZero = vsstring[i];
            DECRYPT += string(nbZero.size() - 1, DECRYPT[DECRYPT.size() - 1]);
        }
    }
    if(DECRYPT.size() % 7 != 0)
        cout << "INVALID" << endl;
    else{
        stringstream sstream(DECRYPT);
        while(sstream.good()){
            bitset<7> bits;
            bitset<7> verif("1000000"), v("0000000");
            sstream >> bits;
            char c = char(bits.to_ulong());
            if(bits != verif && bits != v)
                ascii += c;
        }
        cerr << ascii.size() << endl;
        if(ascii.size() > 0)
            cout << ascii << endl;
        else
            cout << "INVALID" << endl;
    }
}
