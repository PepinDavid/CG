#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 float tofloat(string s){
    replace(s.begin(), s.end(), ',', '.');
    istringstream iss(s);
    float f_val = 0;    
    iss >> f_val;
    return f_val;
}
int main()
{
    vector<string> DEFIBs;
    map<int,float> searchArray;
    string LON;
    cin >> LON; cin.ignore();
    float Lon = tofloat(LON);
    string LAT;
    cin >> LAT; cin.ignore();
    float Lat = tofloat(LAT);
    int N;
    cin >> N; cin.ignore();
    float minLon = 10000, minLat = 10000; 
    cerr << LON << " " << LAT << endl;
    for (int i = 0; i < N; i++) {
        float diffLat = 0;
        float diffLon = 0;
        int cpt = 0;
        string DEFIB;
        getline(cin, DEFIB);        
        float lon;
        float lat;
        int nbDefib;
        while(cpt < 4)
        {
            int index = DEFIB.find_last_of(';');
            if(cpt == 0)
            {
                int index = DEFIB.find_last_of(';');
                lat = tofloat(DEFIB.substr(index+1, DEFIB.size()));
                DEFIB.erase(index);
            }                
            else if(cpt == 1)
            {
                int index = DEFIB.find_last_of(';');
                lon = tofloat(DEFIB.substr(index+1, DEFIB.size()));
                DEFIB.erase(index);
            }
            else if(cpt == 2)
            {
                int index = DEFIB.find(';');
                string n = DEFIB.substr(0, index);
                DEFIB.erase(0, index+1);
                nbDefib = stoi(n);
            }
            else
            {
                int index = DEFIB.find(';');
                DEFIB.erase(index, DEFIB.size());
                DEFIBs.push_back(DEFIB);
            }
              
            cpt++;
        }
        
        float diff = sqrt((Lon-lon)*(Lon-lon) + (Lat-lat)*(Lat-lat));
        if(minLon >= diff)
        {
            minLon = diff;
            float dd = minLon;
            searchArray.insert(make_pair(i,dd));
        }
    }
    
    int index = 0;
    for(auto d : searchArray)
    { 
            if(minLon == d.second)
            {
                minLon = d.second;
                index = d.first;
            }                
    }
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << DEFIBs[index] << endl;
}