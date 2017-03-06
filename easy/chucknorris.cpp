#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//retourne la taille de la chaine binaire
//converti une string en tableau
int asciiToBinary(string &c, int * &s);
void binaryToUnary(int * &s, int &size, string &resp);
int main()
{
    //for store de binary message
    int * binaryRep = NULL;
    int size;
    //store final answer
    string resp;
    //donnés au départ -------
    string MESSAGE;
    getline(cin, MESSAGE);
    //------------------------
    cerr << MESSAGE << endl;    
    size = asciiToBinary(MESSAGE, binaryRep);
    cerr << size << endl;
    binaryToUnary(binaryRep, size, resp);
    
    delete [] binaryRep;
    cout << resp.substr(0, resp.size()-1) << endl;
}

int asciiToBinary(string &c, int * &s)
{
    cerr << c.size() << endl;
    cerr << c.length() << endl;
    string rep;
    //pour que les binaires soit dans l'ordre de la phrase
    //il faut la lire a l'envers;
    for(int i = c.length()-1; i >= 0; i--)
    {   
        int a = (int)c[i]; //char
        int y = 0; //compteur
        while( a > 0)
        {
            if( a%2 == 1)
                rep += "1";
            else
                rep += "0";
                
            a /= 2;
            y++;
        }
        //un code binaire fait 7 de long
        if(y < 7)
            for(; y < 7; y++)
                rep += "0";
    }
    s = new int[rep.size()];
    //boucle servant a mettre la chaine binaire a l'endroit
    for(int i = 1; i <= rep.size(); i++)
    {
        //taille de la chaine de caractère - i pour 
        //prendre chaque caractere de la fin au debut
        if(rep[rep.size() - i] == 49)
            s[i-1] = 1; //i-1 pour 0 commencer a zero
        else
            s[i-1] = 0;
        
    }
    return rep.size();
}

void binaryToUnary(int * &s, int &size, string &resp)
{
    //for make comparison between i and i+1
    int temp;
    //stock 0 or 00 if 1 or 0
    string bin;
    //stock count of comparison between i and i++ binaryRep is true
    int count = 0;
    
    for(int i = 0; i < size; i++)
    {   
        //pour comparaison entre 0 et 1
        temp = s[i];
        count++; // a chaque tour on incremente
        if(temp == 1)
            bin = "0";
        else
            bin = "00";
        //on compare si le prochain char est différent
        if(temp != s[i+1] || i == size - 1)
        {
            resp += bin +" ";
            for(int j = 0; j < count; j++)
                resp += "0";
            resp += " ";
            count = 0;
        }
    }
}