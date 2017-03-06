#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <unordered_map>
using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N; // Number of elements which make up the association table.
    cin >> N; cin.ignore();
    int Q; // Number Q of file names to be analyzed.
    cin >> Q; cin.ignore();
    unordered_map<string, string> mymap; 
    pair <string, string> el;
    for (int i = 0; i < N; i++) {
        string EXT; // file extension
        string MT; // MIME type.
        cin >> EXT >> MT; cin.ignore();
        transform(EXT.begin(), EXT.end(), EXT.begin(), ::tolower);
        el = make_pair(EXT,MT);
        mymap.insert(el);
    }
    for (int i = 0; i < Q; i++) {
        string FNAME; // One file name per line.
        cin >> FNAME;
        transform(FNAME.begin(), FNAME.end(), FNAME.begin(), ::tolower);
        FNAME = string(FNAME.rbegin(), FNAME.rend());
        int index = FNAME.find('\.',0);
        if(index != -1)
        {   
            FNAME = FNAME.substr(0, index);
            FNAME = string(FNAME.rbegin(), FNAME.rend());
            unordered_map<string,string>::const_iterator got = mymap.find(FNAME);
            if(got == mymap.end())
                cout << "UNKNOWN" << endl;
            else
                cout << got->second << endl;
        }
        else
        {
            cout << "UNKNOWN" << endl;
        }
    }
}