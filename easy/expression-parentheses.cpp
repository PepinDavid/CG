#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <map>
using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    string expression;
    string s;
    map<char,char> correspondances = {
        make_pair('{','}'),
        make_pair('[',']'),
        make_pair('(',')'),
    };
    cin >> expression; cin.ignore();
    size_t i = 0;
    int len = expression.size();
    while(i < len){
        if(isalnum(expression[i])){
            expression.erase(i,1);
            len--;
        }else
            i++;
    }
    cerr << expression << endl;
    while(expression.size() >= 2){
        int ind1 = -1, ind2 = -1;
        for(size_t i = 0; i < expression.size()-1; ++i){
            char a = expression[i], b = expression[i+1];
            if(correspondances[a] == b){
                ind1 = i, ind2 = i+1;
                break;
            }
        }
        if(ind2 != -1 && ind1 != -1){
            expression.erase(expression.begin()+ind2);
            expression.erase(expression.begin()+ind1);
        }else{
            break;
        }
    }
    cerr << expression.size() << endl;
    if(expression.size() == 0)
        cout << "true" << endl;
    else
        cout << "false" << endl;
}
