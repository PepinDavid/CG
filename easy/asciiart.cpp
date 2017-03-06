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
    int L;
    cin >> L; cin.ignore();//largeur lettre dans le tableau
    
    int H;
    cin >> H; cin.ignore();//hauteur lettre dans le tableau
    
    string T;
    getline(cin, T);//le texte que l'on a à ecrire
    
    int * asciiString = new int[T.size()]; // pour stocker le numéro de lettre
    // stock dans un tableau le numero (ascii - 65)
    // le numero des lettres souhaitees
    for(int i = 0; i < T.size(); i++) 
    {
        int nb;
         nb = T.at(i);
         if(nb > 64 && nb < 91) //si majuscule
            asciiString[i] = (nb - 65);
        else if(nb > 96 && nb < 123)//si minuscule
            asciiString[i] = (nb - 97);
        else //sinon autre
            asciiString[i] = 26; // correspond au "?"
    }
    
    string ROW; //stock l'alphabet en ascii style    
    for (int i = 0; i < H; i++) 
    {        
        getline(cin, ROW);//prend la ligne i de "#" de l'alphabet en ascii style
        for(int j = 0; j < T.size(); j++)  //pour chaque lettre du mot
        {
            int nbLettre = asciiString[j]; //on prend le numero de lettre (0 a 25)
            for(int k = 0; k < L; k++) //dessine la largeur de chaque lettre sur la ligne i
            {            
                //on va cherche le "char" correspond 
                // on doit prendre le numero de la lettre * la largeur pour etre sur
                // le bon char et on avance le curseur a chaque tour pour faire la largeur
                cout << ROW[k+L*nbLettre]; 
            }
        }     
        cout << endl; //on revient a la ligne
    }      
}