#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
bool compare(const int &a, const int &b){return a < b;}
int main()
{
    list<int> horses;
    int min;
    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        int Pi;
        cin >> Pi; cin.ignore();
        cerr << Pi << endl;
        horses.push_back(Pi);
    }
    horses.sort(compare);
    list<int>::iterator it = horses.begin();
    min = horses.back();
    cerr << "min : " << min << endl;
    while(it != horses.end()){
        list<int>::iterator nx = next(it,1);
        int a = *it;       
        int b = *nx;
        if(b - a <= min && b > 0)
        {
            min = b - a;
        }
        it++;
    }
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << min << endl;
}