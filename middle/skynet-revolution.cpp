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
int main()
{
    multimap<int,int> lvl;
    multimap<int,int> exits;
    int N; // the total number of nodes in the level, including the gateways
    int L; // the number of links
    int E; // the number of exit gateways
    cin >> N >> L >> E; cin.ignore();
    for (int i = 0; i < L; i++) {
        int N1; // N1 and N2 defines a link between these nodes
        int N2;
        cin >> N1 >> N2; cin.ignore();
        cerr << N1 << " " << N2 << endl;
        lvl.insert(make_pair(N1,N2));
    }
    cerr << lvl.size() << endl;
    cerr << L << endl;
    for (int i = 0; i < E; i++) {
        int EI; // the index of a gateway node
        cin >> EI; cin.ignore();
        cerr << EI << endl;
        for(map<int,int>::iterator it = lvl.begin(); it != lvl.end(); it++)
        {
            cerr <<" search exit : first : " << it->first << ", second : " << it->second << ", find ? " << EI << endl;
            if(it->first == EI){
                cerr << it->first << " " << EI << endl;
                exits.insert(make_pair(it->second, EI));
            }else if(it->second == EI){
                cerr << it->second << " " << EI << endl;
                exits.insert(make_pair(it->first, EI));
            }
                
        }   
    }

    // game loop
    while (1) {
        int SI; // The index of the node on which the Skynet agent is positioned this turn
        cin >> SI; cin.ignore();
        map<int,int>::iterator itLvl = lvl.find(SI);
        map<int,int>::iterator itExt = exits.find(SI);
        if(itExt != exits.end()){
            cerr << "Find exist"<< endl;
            cout << itExt->first << " " << itExt->second << endl; 
            exits.erase(itExt);
        }else{
            cerr << "Not Find exist"<< endl;
            cout << itLvl->first << " " << itLvl->second << endl; 
            lvl.erase(itLvl);
        }
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        
    
        // Example: 0 1 are the indices of the nodes you wish to sever the link between
        //cout << "1 2" << endl;
    }
}