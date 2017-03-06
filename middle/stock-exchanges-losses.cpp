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
    int n;
    cin >> n; cin.ignore();
    int * line = new int[n];
    int min = 0, maxMin = 0;
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v; cin.ignore();
        line[i] = v;
    }
    cerr << n << endl;
    for (int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++){
            if(line[j] - line[i] < 0){
                min = line[j] - line[i];
                if(min < maxMin)
                    maxMin = min;
            }else{
                break;
            }
        } 
    }
    
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << maxMin << endl;
}