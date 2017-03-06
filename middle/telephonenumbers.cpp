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
 struct Node{
     map<char,Node*> children;
};

int main()
{
    int N;
    cin >> N; cin.ignore();
    Node* root = new Node{};
    int cpt;
    for (int i = 0; i < N; i++) {
        string telephone;
        cin >> telephone; cin.ignore();
        //a chaque nouveau numéro on copie le node racine
        Node * node = root;
        //chaque lettre position d'un chiffre dans un numéro est un id d'un noeud
        for(int j = 0; j < telephone.size(); j++){
            //iteration sur chaque id de noeud
            map<char,Node*>::iterator it = node->children.find(telephone[j]);
            //si on trouve un enfant dans le noeud où on est
            if(it == node->children.end()){
                //on l'ajoute et on compte un noeud
                node->children[telephone[j]] = new Node{};
                cpt++;
            }
            //on se déplace sur un noeud existant ou sur le noeud que l'on vient de créer
            node = node->children[telephone[j]];
        }
    }
    cout << cpt << endl;
}