#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
class Vector2D{
    protected:
        float _x;
        float _y;
    public:
        Vector2D(float x = 0.0, float y = 0.0)
        {
            _x = x;
            _y = y;
        }
        ~Vector2D(){}
        void setVector2D(float x = 0.0, float y = 0.0)
        {
            _x = x;
            _y = y;
        }
        float x () const{
            return _x;
        }
        float y () const{
            return _y;
        }
        float distanceSquared(float &x, float &y)//retourne la distance au carré vectoriel entre deux points (x et y)
        {
            return (_x - x) * (_x - x) + (_y - y) * (_y - y);
        }
};
class Unit : public Vector2D {
    protected:
        int _id;
    public:
        Unit(int id = -1, float x = 0.0, float y = 0.0) : Vector2D(x, y){
            _id = id;
        }
        ~Unit(){};
        void setUnit(int id, float x, float y){
            _id = id;
            Vector2D::setVector2D(x, y);
            cerr << _x << " " << _y << endl;
        }
        int id () const{
            return _id;
        }
};
class Barrel : public Unit {
    protected:
        int _qty;
        bool _spoted;
    public:
        Barrel(int id = -1, float x = 0.0, float y = 0.0, int qty = 0) : Unit(id, x, y){
            _qty = qty;
            _spoted = false;
        }
        ~Barrel(){
        }
        void setBarrel(int id, int x, int y, int qty){
            Unit::setUnit(id, x , y);
            _qty = qty;
        }
        bool isSpoted() const{
            return _spoted;
        }
        void setSpoted(bool spt){
            _spoted = spt;
        }
};
class CannonBall : public Unit{
    protected:
        int _endLap;
    public:
        CannonBall(int id = -1, float x = 0.0, float y = 0.0, int endLap = 0) : Unit(id, x, y){
            _endLap = endLap;
        }
        ~CannonBall(){}
        int endLap() const{
            return _endLap;
        }
};
class Ship : public Unit {
    protected:
        int _orientation;
        int _speed;
        int _qtyRhum;
        string _findTarget;
        int _distMinBarrel;
        Unit _target;
    public:
        Ship(int id = -1, float x = 0.0, float y = 0.0, int orient = 0, int speed = 0, int qty = 0) : Unit(id, x, y) {
            _orientation = orient;
            _speed = speed;
            _qtyRhum = qty;
            _findTarget = "";
            _distMinBarrel = 10000;
            _target = NULL;
        }
        ~Ship(){}
        void setShip(int id, int x, int y, int orientation, int speed, int stock){
            Unit::setUnit(id, x, y);
            _orientation = orientation;
            _speed = speed;
            _qtyRhum = stock;
            modifCoords();
        }
        void closestBarrel(vector<Barrel>& barrels, int warningRhum){
            for(int i = 0; i < barrels.size(); i++){
                float dist = barrels[i].distanceSquared(_x, _y);
                if(_distMinBarrel > dist && _qtyRhum <= warningRhum){
                    _distMinBarrel = dist;
                    _target = barrels[i];
                    barrels[i].setSpoted(true);
                    _findTarget = "MOVE";
                }
            }
        }
        void closestShipE(vector<Ship>& ships, int warningRhum){
            for(int i = 0; i < ships.size(); i++){
                float dist = sqrt(ships[i].distanceSquared(_x, _y));
                if(dist <= 10 && _qtyRhum > warningRhum){
                        cerr << " shipE x y " << ships[i].x() << " " << ships[i].y() << endl;
                        _target = ships[i];
                        _findTarget = "SHIP";
                }else if(dist > 10 && _qtyRhum > warningRhum){
                        _target = ships[i];
                        _findTarget = "MOVE";
                }
            }
        }
        void escapeCannon(vector<CannonBall>& cannons){
            for(int i = 0; i < cannons.size(); i++){
                float dist = cannons[i].distanceSquared(_x, _y);
                if(cannons[i].endLap() <= 2){
                    escapeCoords();
                }
            }
        }
        void output(vector<Barrel>& barrels, vector<Ship>& ships, vector<CannonBall>& cannons, int warningRhum){
            closestBarrel(barrels, warningRhum);
            closestShipE(ships, warningRhum);
            if(_findTarget == "MOVE")
                cout << "MOVE " <<  _target.x() << " " << _target.y() << endl;
            else if(_findTarget == "SHIP")
                cout << "FIRE " <<  _target.x() << " " << _target.y() << endl;
            else{
                if(cannons.size())
                    escapeCannon(cannons),
                    cout << "MOVE " <<  _x << " " << _y << endl;
                    cout << "WAIT" << endl;
            }

        }
    private:
        void modifCoords(){
            if((int)_y%2 == 0 || _y == 0){
                switch(_orientation){
                    case 0:
                        _x++;
                        break;
                    case 1:
                        _y--;
                        break;
                    case 2:
                        _x--, _y--;
                        break;
                    case 3:
                        _x--;
                        break;
                    case 4:
                        _x--, _y++;
                        break;
                    case 5:
                        _y++;
                        break;
                    default:
                        break;
                }
            }else{
                switch(_orientation){
                    case 0:
                        _x++;
                        break;
                    case 1:
                        _x++, _y--;
                        break;
                    case 2:
                        _y--;
                        break;
                    case 3:
                        _x--;
                        break;
                    case 4:
                        _y++;
                        break;
                    case 5:
                        _x++, _y++;
                        break;
                    default:
                        break;
                }
            }
        }
        void escapeCoords(){
            if((int)_y%2 == 0 || _y == 0){
                switch(_orientation){
                    case 0:
                        _x+=2;
                        break;
                    case 1:
                        _y-=2;
                        break;
                    case 2:
                        _x-=2, _y-=2;
                        break;
                    case 3:
                        _x-=2;
                        break;
                    case 4:
                        _x-=2, _y+=2;
                        break;
                    case 5:
                        _y+=2;
                        break;
                    default:
                        break;
                }
            }else{
                switch(_orientation){
                    case 0:
                        _x+=2;
                        break;
                    case 1:
                        _x+=2, _y-=2;
                        break;
                    case 2:
                        _y-=2;
                        break;
                    case 3:
                        _x-=2;
                        break;
                    case 4:
                        _y+=2;
                        break;
                    case 5:
                        _x+=2, _y+=2;
                        break;
                    default:
                        break;
                }
            }
        }
};
class Brain{
    protected:
        Ship* _myShips;
        int _nbShips;
        int _warningRhum;
        vector<Ship> _shipsE;
        vector<Barrel> _barrels;
        vector<CannonBall> _cannons;
    public:
        Brain(){
            _nbShips = 0;
            _warningRhum = 70;
        }
        ~Brain(){
            delete [] _myShips;
        }
        void deleteItems(){
            delete [] _myShips;
            _shipsE.clear();
            _barrels.clear();
            _cannons.clear();
            _nbShips = 0;
        }
        void setShips(int nbShips){
            _myShips = new Ship[nbShips];
            if(nbShips > 1)
                _warningRhum = 60;
        }
        void setEntity(int entityId, string entityType, int x, int y, int arg1, int arg2, int arg3, int arg4){
            if(entityType == "SHIP"){
                if(arg4 == 1){
                    _myShips[_nbShips].setShip(entityId, x, y, arg1, arg2, arg3);
                    _nbShips++;
                }else{
                    Ship s(entityId, x, y, arg1, arg2, arg3);
                    _shipsE.push_back(s);
                }
            }else if(entityType == "BARREL"){
                Barrel b(entityId, x, y, arg1);
                _barrels.push_back(b);
            }else if(entityType == "CANNONBALL"){
                CannonBall c(x, y, arg2);
                _cannons.push_back(c);
            }
        }
        void output(int nbShips){
            for (int i = 0; i < nbShips; i++) {
                _myShips[i].output(_barrels, _shipsE, _cannons, _warningRhum);
            }
        }
};
int main()
{
    Brain* brain = new Brain();
    // game loop
    while (1) {
        int nbShips = 0;
        vector<Ship> shipsE;
        vector<Barrel> barrels;
        vector<CannonBall> cannons;
        int myShipCount; // the number of remaining ships
        cin >> myShipCount; cin.ignore();
        brain->setShips(myShipCount);
        int entityCount; // the number of entities (e.g. ships, mines or cannonballs)
        cin >> entityCount; cin.ignore();
        for (int i = 0; i < entityCount; i++) {
            int entityId;
            string entityType;
            int x;
            int y;
            int arg1;
            int arg2;
            int arg3;
            int arg4;
            cin >> entityId >> entityType >> x >> y >> arg1 >> arg2 >> arg3 >> arg4; cin.ignore();
            brain->setEntity(entityId, entityType, x, y, arg1, arg2, arg3, arg4);

        }
        brain->output(myShipCount);
        brain->deleteItems();
    }
}
