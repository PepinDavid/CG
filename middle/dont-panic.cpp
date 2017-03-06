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
    int nbFloors; // number of floors
    int width; // width of the area
    int nbRounds; // maximum number of rounds
    int exitFloor; // floor on which the exit is found
    int exitPos; // position of the exit on its floor
    int nbTotalClones; // number of generated clones
    int nbAdditionalElevators; // ignore (always zero)
    int nbElevators; // number of elevators
    map<int,int> elevators;
    cin >> nbFloors >> width >> nbRounds >> exitFloor >> exitPos >> nbTotalClones >> nbAdditionalElevators >> nbElevators; cin.ignore();
    elevators.insert(make_pair(exitFloor, exitPos));
    for (int i = 0; i < nbElevators; i++) {
        int elevatorFloor; // floor on which this elevator is found
        int elevatorPos; // position of the elevator on its floor
        cin >> elevatorFloor >> elevatorPos; cin.ignore();
        cerr << "Floor ; " <<elevatorFloor << " pos : "<< elevatorPos << endl;
        elevators.insert(make_pair(elevatorFloor, elevatorPos));
    }
    // game loop
    while (1) {
        int cloneFloor; // floor of the leading clone
        int clonePos; // position of the leading clone on its floor
        string direction; // direction of the leading clone: LEFT or RIGHT
        cin >> cloneFloor >> clonePos >> direction; cin.ignore();
        map<int,int>::iterator i = elevators.find(cloneFloor);
        if(clonePos > i->second && direction == "RIGHT")
            cout << "BLOCK" << endl;
        else if(clonePos < i->second && direction == "LEFT")
            cout << "BLOCK" << endl;  
        else
            cout << "WAIT" << endl;
    }
}