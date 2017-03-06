#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Don't let the machines win. You are humanity's last hope...
 **/
int main()
{
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();
    char ** arrChar = new char * [height]; //on declare la matrice
    for (int i = 0; i < height; i++) 
    {
        arrChar[i] = new char[width];
        string line; // width characters, each either 0 or .
        getline(cin, line);
        for(int j = 0; j < width; j++)
        {
            arrChar[i][j] = line[j]; //on complete la matrice avec chaque char
        }
    }
    
    for (int i = 0; i < height; i++) //sur chaque colonne
    {
        for(int j = 0; j < width; j++) //sur chaque ligne
        {
            //convertion char en int
            int a = arrChar[i][j] - 48; 
            if(a ==  0){
                int cpI(i), cpJ(j);
                cout << j << " " << i << " "; //on stock dans le tampon de sorti
                while(cpJ < width)
                {
                    cpJ++; //on se deplace sur la droite
                    if(cpJ >= width)
                    {
                        cout << "-1 " << "-1 ";
                        
                    }
                    else
                    {
                        int a = arrChar[i][cpJ] - 48;
                        if(a ==  0){
                            cout << cpJ << " " << i << " ";
                            break;
                        }
                    }
                    
                }
                while(cpI < height)
                {
                    cpI++; //on descend 
                    if(cpI >= height)
                    {
                        cout << "-1 " << "-1 ";
                    }
                    else
                    {
                        int a = arrChar[cpI][j] - 48;
                        if(a ==  0){
                            cout << j << " " << cpI << " ";
                            break;
                        }                   
                    }
                }
                cout << endl; //on affiche le tampon de sorti
            }
        }
        delete [] arrChar[i];
    }
    delete [] arrChar;
}