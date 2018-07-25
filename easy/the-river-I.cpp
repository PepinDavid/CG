#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    long long r1;
    cin >> r1; cin.ignore();
    long long r2;
    cin >> r2; cin.ignore();

    bool find = false;

    string s1 = to_string(r1);
    string s2 = to_string(r2);
    int r;


    while(!find){
        if(r1 < r2){
            for(int i = 0; i < s1.size(); i++)
                r1 +=  (s1[i] - '0' );
            s1 = to_string(r1);
        }else if(r1 > r2){
            for(int i = 0; i < s2.size(); i++)
                r2 +=  (s2[i] - '0');
            s2 = to_string(r2);
        }
        cerr << "r1 " << r1 << endl;
        cerr << "r2 " << r2 << endl;
        if(r1 == r2){
            r = r1;
            find = true;
        }
    }

    cout << r << endl;
}
