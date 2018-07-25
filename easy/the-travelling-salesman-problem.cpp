#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <list>
#include <queue>
using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 int INF = 10000000000;
 struct point{
     int x;
     int y;
};

int main()
{
    int N;
    cin >> N; cin.ignore();
    vector<point> points;
    list<float> listDist[N];
    list<int> listNode[N];
    for (int i = 0; i < N; i++) {
        int X;
        int Y;
        cin >> X >> Y; cin.ignore();
        point p = {X, Y};
        points.push_back(p);
    }
    for(int i = 0; i < points.size(); i++){
        point p1 = points[i];
        for(int j = 0; j < points.size(); j++){
            if(i != j){
                point p2 = points[j];
                listDist[i].push_front( sqrt( pow(p2.x - p1.x, 2)+pow(p2.y-p1.y, 2) ) );
                listNode[i].push_front(j);
            }
        }
    }
    vector<int> nodesVisit;
    float dist = 0;
    int u = 0;
    int n = N+1;
    while(n-- > 0){
        list<float>::iterator itDist = listDist[u].begin();
        list<int>::iterator itNode = listNode[u].begin();
        float dist1 = INF;
        int nodeNB = -1;
        while(itDist != listDist[u].end()){
            vector<int>::iterator it = find(nodesVisit.begin(), nodesVisit.end(), *itNode);
            if((*itDist < dist1 && it == nodesVisit.end() && *itNode != 0) || n == 1)
                dist1 = *itDist, nodeNB = *itNode;
            itDist++;
            itNode++;
        }
        if(nodeNB != -1)
            nodesVisit.push_back(nodeNB), dist += dist1, u = nodeNB;
    }
    cout << round(dist) << endl;
}
