#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    //stockage du mini, maxi de X et Y ainsi que la moitié de la distance
    int maxX, midX, minX(0); // width of the building.nb columns X
    int maxY, midY, minY(0); // height of the building.nb lines Y
    cin >> maxX >> maxY; cin.ignore();
    int N; // maximum number of turns before game over.
    cin >> N; cin.ignore();
    cerr << maxX << " " << maxY << endl;
    int X0;
    int Y0;
    cin >> X0 >> Y0; cin.ignore();    
    cerr << "Depart : the Batman x & y : " << X0 << " " << Y0 << endl;
    //calcule de la moitié pour X et Y
    midX = (maxX+minX)/2;
    midY = (maxY+minY)/2;
    //si position initial "-" la moitié de la distance est superieur a zero (donc si on est dans la parti superieur)
    if(X0 - midX > 0)
        maxX = X0;
    if(Y0 - midY > 0)
        maxY = Y0;
    // game loop
    while (1) {
        string bombDir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> bombDir; cin.ignore();
        cerr << bombDir << endl;
        //declaration de nouvelle borne maxX/maxY et minX/minY par rapport au deplacement que l'on doit effectuer
        if(bombDir == "U"){//exemple: on doit monté donc la limite maxY va augmenté
            maxY = Y0;
        }
        else if(bombDir == "UR"){
            minX = X0;
            maxY = Y0;
        }
        else if(bombDir == "R"){
            minX = X0;
        }
        else if(bombDir == "DR"){
            minX = X0;
            minY = Y0;           
        }
        else if(bombDir == "D"){
            minY = Y0;
        }
        else if(bombDir == "DL"){
            maxX = X0;
            minY = Y0;
        }
        else if(bombDir == "L"){                
            maxX = X0;
        }
        else if(bombDir == "UL"){  
            maxX = X0;
            maxY = Y0;
        }        
        //on calcule le nouveau milieu par rapport aux nouveaux intervalles
        midX = (maxX+minX)/2;
        midY = (maxY+minY)/2;
        //la position du Batman sera la moitié de X et Y
        X0 = midX;
        Y0 = midY;
        cerr << "min Move x & y : " << minX << " " << minY << endl;
        cerr << "Batman/middle x & y : " << midX << " " << midY << endl;
        cerr << "max Move x & y : " << maxX << " " << maxY << endl;
        cout << X0 << " " << Y0 << endl;
    }    
}