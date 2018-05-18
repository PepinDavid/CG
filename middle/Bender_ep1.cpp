#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <string.h>

using namespace std;
map<int, string> base = {{0, "SOUTH"}, {1, "EAST"}, {2, "NORTH"}, {3, "WEST"}};
map<int, string> inverse = {{1, "WEST"}, {2, "NORTH"}, {3, "EAST"}, {0, "SOUTH"}};
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 struct pixel{
     int x;
     int y;
 };
 class Bender{
    private:
        bool _beer = false;
        bool _inversion = false;
        bool _obstacle = false;
        string _direction = "SOUTH";
        vector<string> _moves;
        int _dir = 0;
        pixel _pix;
        pixel _init;
    public:
        Bender(){};
        ~Bender(){};
        void setPos(int i, int j){
            _pix.x = i;
            _pix.y = j;
            _init.x = i;
            _init.y = j;
        }
        int getX(){
            return _pix.x;
        }
        int getY(){
            return _pix.y;
        }
        void setDirection(int changeDirection = -1){
            if(changeDirection > -1){
                _dir = changeDirection;
                if(getInverse())
                    _direction = inverse[changeDirection];
                else
                    _direction = base[changeDirection];
            }else{
                _dir++;
                if(_dir > 3)
                    _dir = 0;
                if(getInverse())
                    _direction = inverse[_dir];
                else
                    _direction = base[_dir];
            }
        }
        void setBeer(){
            if(_beer)
                _beer = false;
            else
                _beer = true;
        }
        void setInversion(){
            if(_inversion)
               _inversion = false;
            else
                _inversion = true;
        }
        bool getInverse(){
            return _inversion;
        }
        string getDirection(){
            return _direction;
        }
        void walk(int L, int C){
            if(_direction == "SOUTH")
                _pix.y++;
            else if(_direction == "NORTH")
                _pix.y--;
            else if(_direction == "EAST")
                _pix.x++;
            else if(_direction == "WEST")
                _pix.x--;
        }
        bool getBeer(){
            return _beer;
        }
        void addMove(string s){
            _moves.push_back(s);
        }
        int lengthMoves(){
            return _moves.size();
        }
        void reInit(){
            _pix = _init;
        }
};

class Map{
    private:
        char **_map = 0;
    public:
        Map(){}
        ~Map(){}
        void setWidth(int w){
            _map = new char *[w];
        }
        void setHeight(int x, int h){
            _map[x] = new char[h];
        }
        void setCase(int x, int y, char c){
            _map[x][y] = c;
        }
        char getCase(int x, int y){
            return _map[x][y];
        }
        //verification des obstables imaginer que si on demanre en bas a droite d'une map on rentre dans le mur!
        //TOD DO pas au point
        void verifyAdjacentCase(Bender * b, int C, int L){
            int x = b->getX(), y = b->getY();
            string d = b->getDirection();
            if(d == "SOUTH")
                y++;
            else if(d == "NORTH")
                y--;
            else if(d == "EAST")
                x++;
            else if(d == "WEST")
                x--;
            if(x < 0 || x > C)
                b->setDirection(), verifyAdjacentCase(b, C, L);
            else if(y < 0 || y > L)
                b->setDirection(), verifyAdjacentCase(b, C, L);

            if(isLimit(x, y) || (isObstacle(x, y) && !b->getBeer()))
                b->setDirection();
            else if(isObstacle(x, y) && b->getBeer())
                setCase(x, y, ' ');
        }
        bool isObstacle(int x, int y){
            return (getCase(x, y) == 'X');
        }
        bool isLimit(int x, int y){
            return (getCase(x, y) == '#');
        }
        bool isFinish(int x, int y, string d){
            if(d == "SOUTH")
                y++;
            else if(d == "NORTH")
                y--;
            else if(d == "EAST")
                x++;
            else if(d == "WEST")
                x--;
            if(getCase(x, y) == '$')
                return true;
            return false;
        }
        void findTeleporter(int x, int y, int L, int C, Bender *ben){
            for (int i = 0; i < L; i++){
                for (int j = 0; j < C; j++){
                    if(getCase(j, i) == 'T' && (j != x || i != y))
                        ben->setPos(j, i);
                }
            }
        }
        void printMap(int C, int L){
            for(int i = 0; i < L; i++){
                for(int j = 0; j < C; j++){
                    cerr << _map[j][i];
                }
                cerr << endl;
            }
        }
};

void play(Bender *ben, Map *carte, int L, int C){
    int x = 0, y = 0, changeDirection = -1;
    string d = ben->getDirection();
    while(!carte->isFinish(x, y, d)){
        x = ben->getX();
        y = ben->getY();
        d = ben->getDirection();

        if(carte->getCase(x, y) == 'I')
            ben->setInversion();
        else if(carte->getCase(x, y) == 'B')
            ben->setBeer();
        else if(carte->getCase(x, y) == 'T')
            carte->findTeleporter(x, y, L, C, ben);
        else if(carte->getCase(x, y) == 'S'){
            changeDirection = (ben->getInverse())?3:0;
            ben->setDirection(changeDirection);
        }else if(carte->getCase(x, y) == 'N'){
            changeDirection = (ben->getInverse())?1:2;
            ben->setDirection(changeDirection);
        }else if(carte->getCase(x, y) == 'E'){
            changeDirection = (ben->getInverse())?2:1;
            ben->setDirection(changeDirection);
        }else if(carte->getCase(x, y) == 'W'){
            changeDirection = (ben->getInverse())?0:3;
            ben->setDirection(changeDirection);
        }
        carte->verifyAdjacentCase(ben, C, L);
        cout << ben->getDirection() << endl;
        ben->walk(L, C);
    };
}

int main()
{
    Map m;
    int L;
    int C;
    cin >> L >> C; cin.ignore();
    Bender b;
    m.setWidth(C);
    for (int i = 0; i < C; i++)
        m.setHeight(i, L);
    for (int i = 0; i < L; i++) {
        string row;
        getline(cin, row);
        for(int j = 0; j < row.size(); j++){
            if(row[j] == '@')
                b.setPos(j, i);
            m.setCase(j, i, row[j]);
        }
    }
    m.printMap(C, L);
    play(&b, &m, L, C);
}
