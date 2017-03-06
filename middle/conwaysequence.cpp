#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
vector<string> conwaystyle(int R, int L, int loop, vector<string> r){
    loop++;
    if(L > loop){
        vector<string> newR;
        int cpt = 0;
        string temp = *(r.begin());
        for(vector<string>::iterator it = r.begin(); it != r.end(); it++){
            if(temp == *it)
                cpt++;
            else{
                newR.push_back(to_string(cpt));
                newR.push_back(temp);
                cpt = 1;
                temp = *(it);
            }
            if(it+1 == r.end()){
                newR.push_back(to_string(cpt));
                newR.push_back(temp);
            }
        }
        return conwaystyle(R, L, loop, newR);
    }
    return r;
};
int main()
{
    int R;
    cin >> R; cin.ignore();
    int L;
    cin >> L; cin.ignore();
    int a = 0;
    vector<string> s;
    s.push_back(to_string(R));
    s = conwaystyle(R, L, a, s);
    string c = "";
    for(vector<string>::iterator it = s.begin(); it != s.end(); it++){
        if(it+1 != s.end())
            c = c + *(it) + " ";
        else
            c = c + *(it);
    }
    cout << c << endl;
}