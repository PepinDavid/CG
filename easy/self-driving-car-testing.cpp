#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class Move{
    private:
     int nb;
     string type;
    public:
        Move(int n, string t){nb=n;type=t;};
        ~Move(){};
        int getNb(){return nb;};
        string getType(){return type;};
};

int main()
{
    int N;
    char car = '#';
    vector<string> road;
    vector<Move*> moves;
    cin >> N; cin.ignore();
    string XthenCOMMANDS;
    getline(cin, XthenCOMMANDS);
    size_t posMove = XthenCOMMANDS.find(';');
    int posCar = stoi(XthenCOMMANDS.substr(0,posMove)) - 1;
    XthenCOMMANDS = XthenCOMMANDS.substr(posMove+1, XthenCOMMANDS.size());
    while(posMove != string::npos){
        posMove = XthenCOMMANDS.find(';');
        string strMove = XthenCOMMANDS.substr(0, posMove);
        int index = -1;
        for(int i = 0; i < strMove.size(); i++){
            if(isalpha(strMove[i]))
                index = i;
        }
        moves.push_back(new Move(stoi(strMove.substr(0, index)), strMove.substr(index, strMove.size()-1)));
        XthenCOMMANDS = XthenCOMMANDS.substr(posMove+1, XthenCOMMANDS.size());
    }

    for (int i = 0; i < N; i++) {
        string RthenROADPATTERN;
        getline(cin, RthenROADPATTERN);
        size_t pos = RthenROADPATTERN.find(";");
        int line = stoi(RthenROADPATTERN.substr(0, pos));
        string r = RthenROADPATTERN.substr(pos+1, RthenROADPATTERN.size());
        for(int j = 0; j < line; j++)
            road.push_back(r);
    }
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    int indexMoves = 0;
    int nbMove = moves[indexMoves]->getNb();
    for(int i = 0; i < road.size(); i++){
        Move *m = moves[indexMoves];
        if(nbMove == i+1 && moves.size() > indexMoves+1){
            indexMoves++;
            nbMove += moves[indexMoves]->getNb();
        }
        if(m->getType() == "R")
            posCar++;
        else if(m->getType() == "L")
            posCar--;
        road[i][posCar] = car;
        cout << road[i] << endl;
    }
}
