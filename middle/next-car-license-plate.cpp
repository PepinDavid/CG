#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> truncatePLate(string plate){
    char sep = '-';
    vector<string> final(3,"");
    int i = 0;
    for(auto a: plate){
        if(a == sep)
            i++;
        else
            final[i] += a;
    }
    return final;
}
string patternNb(string s){
    string p = "000";
    return p.substr(0, p.size() - s.size()) + s;
}
void updateLetter(vector<int> *nbs){
    for(int i = 0; i < (*nbs).size(); i++){
        while((*nbs)[i] > 26){
            if(i < (*nbs).size()-1){
                (*nbs)[i] -= 26;
                (*nbs)[i+1]++;
            }else{

                (*nbs)[i] -= 26;
                (*nbs)[0]++;
            }
        }
    }
}
string calculatePlate(int n, string plate){
    string final = "";
    vector<string> str = truncatePLate(plate);
    int number = stoi(str[1]);
    if(number + n > 999){
        int nbtour = 0;
        int nbFinal = 0;
        n = n + number;
        while( n > 999){
            nbtour++;
            n = n - 999;
        }
        nbFinal = n;

        str[1] = patternNb(to_string(nbFinal));
        vector<char> letters = {str[0][0], str[0][1], str[2][0], str[2][1]};
        vector<int> nbTurnLet(4, 0);
        nbTurnLet[0] = nbtour;
        updateLetter(&nbTurnLet);
        for(int i = 0; i < nbTurnLet.size(); i++){
            int j = nbTurnLet.size() - 1 - i;
            char l = letters[j];
            l += nbTurnLet[i];
            while(l > 90){
                l = l - 90 + 64;
                nbTurnLet[i+1]++;
            }
            letters[j] = l;
        }
        str[0] = "";
        str[2] = "";
        for(int i = 0; i < letters.size(); i++){
            if(i > 1){
                str[2]+=letters[i];
            }else{
                str[0]+=letters[i];
            }
        }
        for(auto s : str)
            final += s +"-";
    }else{
        str[1] = patternNb(to_string(number + n));
        for(auto s : str)
            final += s +"-";
    }
    final = final.substr(0, final.size()-1);
    return final;

}
int main()
{
    string x;
    getline(cin, x);
    int n;
    cin >> n; cin.ignore();
    cout << calculatePlate(n, x) << endl;
}
