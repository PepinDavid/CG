#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    int n; // the number of temperatures to analyse
    cin >> n; cin.ignore();
    string temps; // the n temperatures expressed as integers ranging from -273 to 5526
    string delimiter(" ");
    getline(cin, temps);
    int cpt = 0, index = 0;
    int * celsius = new int[n];
    int minZero; 
    unsigned int maxZero;
    if(temps.size() > 0)
    {
        while(index != string::npos)
        {
            index = temps.find(delimiter);
            celsius[cpt] = stoi(temps.substr(0, index));
            temps.erase(0, index + delimiter.length());
            cpt++;
        }
        maxZero = minZero = celsius[0];
        for(int i = 1; i < cpt; i++)
        {                
            if(celsius[i] >= 0 && celsius[i] < maxZero)
                maxZero = celsius[i];
            if(celsius[i] < 0 && celsius[i] > minZero)
                minZero = celsius[i];
        }
        if(maxZero > abs(minZero))
            cout << minZero << endl;
        else
            cout << maxZero << endl;
    }
    else
    {
        cout << 0 << endl;
    }
    delete [] celsius;
}