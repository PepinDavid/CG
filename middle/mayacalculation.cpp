#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
void drawCharactere(map<int, string>& numbers, int numNb, int H, int L){
    for (int i = 0; i < H; i++) {
        cerr << numbers[numNb].substr(i*L, L) << endl;
    }
}
int giveNumbers(map<int, string>& numbers, string& num, int H, int L){
    int numTot = -1;
    if(num.size()/(H*L) > 1){
        int quo = (num.size()/(H*L))-1;
        for(auto& v: numbers){
            if(v.second == num.substr(0,(H*L))){
                numTot = v.first;
            }
        }
        drawCharactere(numbers, numTot, H, L);
        num = num.substr((H*L), num.size());
        return (numTot*pow(20,quo)) + giveNumbers(numbers, num, H, L);
    }else{
        for(auto& v: numbers){
            if(v.second == num){
                numTot = v.first;
            }
        }
        drawCharactere(numbers, numTot, H, L);
        return numTot;
    } 
}
string giveMaya(map<int, string>& numbers, long& num){
    string numMaya = "answer";
    if(num > 20){
        long remain = num / 20;
        long rest = num - 20 * remain;
        if(remain < 20)
            return numbers[remain] + giveMaya(numbers, rest);
        else
            return giveMaya(numbers, remain) +  numbers[rest];
    }else{
        return numbers[num];
    }
    
}
int main()
{
    int L;
    int H;
    map<int, string> numbers;
    cin >> L >> H; cin.ignore();
    for (int i = 0; i < H; i++) {
        int cpt = 0;
        string numeral;
        cin >> numeral; cin.ignore();
        for(int j = 0; j < numeral.size(); j+=L){
            numbers[cpt] += numeral.substr(j, L);
            cpt++;            
        }       
    }
    
    int S1;
    cin >> S1; cin.ignore();    
    string num1;
    for (int i = 0; i < S1; i++) {
        string num1Line;
        cin >> num1Line; cin.ignore();
        for(int k = 0 ; k < L; k++)
            num1 += num1Line[k];
    }
    int S2;
    string num2;
    cin >> S2; cin.ignore();
    for (int i = 0; i < S2; i++) {
        string num2Line;
        cin >> num2Line; cin.ignore();        
        for(int k = 0 ; k < L; k++)
            num2 += num2Line[k];
    }
    string operation;
    cin >> operation; cin.ignore();
    cerr << operation << endl;
    long n1 = giveNumbers(numbers,num1, L, H), 
    n2=giveNumbers(numbers,num2, L, H),
    ntot = 0; 
    if(operation == "+")
        ntot = n1+n2;
    else if(operation == "-")
        ntot = n1-n2;
    else if(operation == "*")
        ntot = n1*n2;
    else if(operation == "/")
        ntot = n1/n2;
        
    cerr << "ntotal " << ntot << endl;
    string rep = giveMaya(numbers,ntot);
    for(int i = 0; i < rep.size(); i+=L){
        string s;
        for(int j = 0; j < H; j++){
            s += rep[i+j];
        }
        cout << s << endl;
    }

}