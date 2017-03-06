#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <map>
using namespace std;

map<string, int> valCard;
string val[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
void instanciateMap (map<string, int> &m, string v[]){
    for(int i = 0; i < 13; i++)
        m.insert(make_pair(v[i], i));
}
void rebuildDeque(deque<pair<string, int>> &player, deque<pair<string, int>> &newGamePlayer, deque<pair<string, int>> &afterGamePlayer){
    deque<pair<string, int>>::iterator i;
    if(newGamePlayer.size() > 0){
        for(i = newGamePlayer.begin(); i != newGamePlayer.end(); i++)
            player.push_back(make_pair(i->first, i->second));
    }
    newGamePlayer.clear();
    if(afterGamePlayer.size() > 0){
        for(i = afterGamePlayer.begin(); i != afterGamePlayer.end(); i++)
            player.push_back(make_pair(i->first, i->second));
    }
    afterGamePlayer.clear();
}
void reduceDeque(deque<pair<string, int>> &afterGamePlayer, deque<pair<string, int>> &newPlayer)
{
    if(newPlayer.size() > 0){
        for(int i = 0; i < newPlayer.size(); i++){
            pair<string, int> pair1 = newPlayer.at(i);
            for(int j = 0; j < afterGamePlayer.size(); j++){
                pair<string, int> pair2 = afterGamePlayer.at(j);
                if(get<0>(pair1) == get<0>(pair2))
                    afterGamePlayer.erase(afterGamePlayer.begin() + j);
            }
        }
    }
}
int bataille(deque<pair<string, int>> &plOne, deque<pair<string, int>> &plTwo, deque<pair<string, int>> &afterP1, deque<pair<string, int>> &afterP2, int &i){
    pair<string, int> pair1;
    pair<string, int> pair2; 
    i += 4;
    for(int j = 0; j < 3; j++){
        if(plOne.size() < 1 || plTwo.size() < 1)
            break;
        pair1 = plOne.at(0);
        pair2 = plTwo.at(0);
        afterP1.push_back(pair1);
        afterP2.push_back(pair2);
        plOne.erase(plOne.begin());
        plTwo.erase(plTwo.begin());
    } 
    if(plOne.size() == 0 || plTwo.size() == 0){
        return 3;
    }
    pair2 = plTwo.at(0);    
    pair1 = plOne.at(0);
    plOne.erase(plOne.begin());
    plTwo.erase(plTwo.begin());
    afterP1.push_back(pair1);
    afterP2.push_back(pair2);
    if(get<1>(pair1) > get<1>(pair2)){
        rebuildDeque(plOne, afterP1, afterP2);
    }else if(get<1>(pair1) < get<1>(pair2)){ 
        rebuildDeque(plTwo, afterP1, afterP2);
        return 2;
    }else{
        return bataille(plOne, plTwo, afterP1, afterP2, i);
    }
}
void match(deque<pair<string, int>> &plOne, deque<pair<string, int>> &plTwo, int &rounds){
    int m, PAT;
    deque<pair<string, int>> afterMatchP1, afterMatchP2;
    if(plOne.size() > plTwo.size())
        m = plTwo.size();
    else
        m = plOne.size();
    for (int i = 0; i < m; i++) {
        rounds++;
        pair<string, int> pair1 = plOne.at(0);
        pair<string, int> pair2 = plTwo.at(0);
        plOne.erase(plOne.begin());
        plTwo.erase(plTwo.begin());
       if(get<1>(pair1) > get<1>(pair2)){
            plOne.push_back(pair1);
            plOne.push_back(pair2);
        }else if(get<1>(pair1) < get<1>(pair2)){
            plTwo.push_back(pair1);
            plTwo.push_back(pair2);            
        }else{
            afterMatchP1.push_back(pair1);
            afterMatchP2.push_back(pair2);
            PAT = bataille(plOne, plTwo, afterMatchP1, afterMatchP2, i);
        }
    }
    if(PAT == 3)
        cout << "PAT" << endl;
    else if(plOne.size() > 0 && plTwo.size() > 0)
        match(plOne, plTwo, rounds);
    else if(plOne.size() > plTwo.size())
        cout << 1 << " " << rounds << endl;
    else if(plOne.size() < plTwo.size())
        cout << 2 << " " << rounds << endl;
}
int main()
{
    int n; // the number of cards for player 1
    map<string, int>::iterator it;
    deque<pair<string, int>> plOne, plTwo;
    instanciateMap(valCard, val);
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        string cardp1, card; // the n cards of player 1
        cin >> card; cin.ignore();
        cardp1 = card;
        cardp1.pop_back();
        it = valCard.find(cardp1);
        plOne.push_back(make_pair(card, it->second));
    }
    cerr << "size game p1 : " << n << endl;
    int m; // the number of cards for player 2
    cin >> m; cin.ignore();
    for (int i = 0; i < m; i++) {
        string cardp2, card; // the m cards of player 2
        cin >> card; cin.ignore();
        cardp2 = card;
        cardp2.pop_back();
        it = valCard.find(cardp2);
        plTwo.push_back(make_pair(card, it->second));
    }
    cerr << "size game p2 : " << m << endl;
    int rounds = 0;
    match(plOne, plTwo, rounds);
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    //cout << "PAT" << endl;
}