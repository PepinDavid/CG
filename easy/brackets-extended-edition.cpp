#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cctype>
using namespace std;

typedef std::multimap<char, char>::iterator MMAPIterator;
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N;
    cin >> N; cin.ignore();
    vector<string> exps;
    multimap<char,char> correspondances = {
        make_pair('{','}'),
        make_pair('}','{'),
        make_pair('{','{'),
        make_pair('}','}'),
        make_pair('[',']'),
        make_pair(']','['),
        make_pair('[','['),
        make_pair(']',']'),
        make_pair('(',')'),
        make_pair(')','('),
        make_pair('(','('),
        make_pair(')',')'),
        make_pair('<','>'),
        make_pair('>','<'),
        make_pair('<','<'),
        make_pair('>','>')
    };
    for (int i = 0; i < N; i++) {
        string expression;
        getline(cin, expression);
        size_t j = 0;
        int len = expression.size();
        while(j < len){
            if(isalnum(expression[j])){
                expression.erase(j,1);
                len--;
            }else
                j++;
        }
        exps.push_back(expression);
    }
    for(auto a:exps)
        cerr << a << endl;
    for (int j = 0; j < N; j++) {
        string expression = exps[j];
        while(expression.size() > 1){
            int ind1 = -1, ind2 = -1;
            for(size_t i = 0; i < expression.size()-1; ++i){
                char a = expression[i], b = expression[i+1];
                pair<MMAPIterator, MMAPIterator> result = correspondances.equal_range(a);
                for (MMAPIterator it = result.first; it != result.second; it++){
                    if(it->second == b){
                        ind1 = i, ind2 = i+1;
                        find = true;
                        break;
                    }
                }
                if(find)
                    break;
            }
            if(ind2 != -1 && ind1 != -1){
                expression.erase(expression.begin()+ind2);
                expression.erase(expression.begin()+ind1);
            }else{
                break;
            }
        }
        cerr << "result : " << expression << endl;
        if(expression.size() == 0)
            cout << "true" << endl;
        else
            cout << "false" << endl;
    }
}
