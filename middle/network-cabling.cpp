#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> points;

int main()
{
    vector<points> positions;
    
    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        int X;
        int Y;
        cin >> X >> Y; cin.ignore();        
        positions.push_back({X, Y});
    }

    //calcule avg de Y
    //on trie dans le sens croissant
    sort(positions.begin(), positions.end(), [](points p1, points p2){ return p1.second < p2.second; });
    int mainLengthY;
    //si taille vector mod 2 != 0
    if (positions.size() % 2)
        mainLengthY = positions[positions.size() / 2].second;
    else //taille vector mod 2 == 0
        mainLengthY = (positions[(positions.size() / 2)-1].second + positions[positions.size() / 2].second) / 2;
    
    cerr << mainLengthY << endl;
    // Calcule de avg de X
    int minPosX = positions[0].first;
    int maxPosX = positions[0].first;
    for (points& pos : positions)
    {
        if (pos.first < minPosX)
            minPosX = pos.first;
        if (pos.first > maxPosX)
            maxPosX = pos.first;
    }
    
    int mainLengthX = maxPosX - minPosX;

    // Calcul taille total du cable principal
    long long total = mainLengthX;
    for (points& pos : positions)
        total += abs(mainLengthY - pos.second);
    
    cout << total << endl;
}