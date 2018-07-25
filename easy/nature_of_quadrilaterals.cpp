#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

float distance(int xA, int xB, int yA, int yB)
{
    return sqrt((xA - xB) * (xA - xB) + (yA - yB) * (yA - yB));
}

int main()
{
    int n;
    cin >> n; cin.ignore();
    string resp;
    vector<string> resps;
    for (int i = 0; i < n; i++) {
        string A;
        int xA;
        int yA;
        string B;
        int xB;
        int yB;
        string C;
        int xC;
        int yC;
        string D;
        int xD;
        int yD;
        cin >> A >> xA >> yA >> B >> xB >> yB >> C >> xC >> yC >> D >> xD >> yD; cin.ignore();
        float AB = distance(xA, xB, yA, yB);
        float BC = distance(xB, xC, yB, yC);
        float CD = distance(xC, xD, yC, yD);
        float DA = distance(xD, xA, yD, yA);
        float AC = distance(xA, xC, yA, yC);
        float BD = distance(xB, xD, yB, yD);
        cerr << "AB : " << AB << " BC: " << BC << " CD : " << CD << " DA : " << DA << endl;
        cerr << "AC : " << AC << " BD: " << BD << endl;
        if(AB == BC && BC == CD && CD == DA  && DA == AB){
            resp = A+B+C+D+" is a rhombus.";
            if(AB/BC == 1 && BC/CD == 1 && CD/DA == 1 && DA/AB == 1 && AC == BD)
                    resp = A+B+C+D+" is a square.";
        }else if(AB == CD && BC == DA){
            resp = A+B+C+D+" is a parallelogram.";
            if(AB/BC == CD/DA && BC/CD == DA/AB && AC == BD){
                    resp = A+B+C+D+" is a rectangle.";
                }
        }else{
            resp = A+B+C+D+" is a quadrilateral.";
        }
        resps.push_back(resp);
    }
    for (int i = 0; i < n; i++) {

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << resps[i] << endl;
    }
}
