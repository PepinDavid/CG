#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

//node est l'id du noeud et nodes sont les relations
int count(int node, map<int, vector<int>>& nodes)
{
    //si l'id du noeud dans nodes n'est pas vide
    if (!nodes[node].empty())
    {
        int maxCount = 1;
        //pour chaque noeuds enfants 
        for (int v : nodes[node])
        {
            int c = count(v, nodes);
            if (c > maxCount)
                maxCount = c;
        }
        
        return maxCount + 1;
    }
    else
        return 1;
}

int main()
{
    set<int> roots;
    map<int, vector<int>> nodes;
    
    int n; // the number of relationships of influence
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        int x; // a relationship of influence between two people (x influences y)
        int y;
        cin >> x >> y; cin.ignore();
        
        // ajout des relations dans une listes
        nodes[x].push_back(y);
        roots.insert(x);
    }
    
    // trouver tous les noeuds racines
    for (auto& vs : nodes)
    {
        for (int v : vs.second)
            roots.erase(v);
    }
    
    // commencer de toutes les racines et compter les influences
    int maxCount = 0;
    for (int v : roots)
    {
        int c = count(v, nodes);
        if (c > maxCount)
            maxCount = c;
    }
    
    cout << maxCount << endl;
}