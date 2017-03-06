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

map<int, string> create_map_top()
{
  map<int, string> m;
  m[0] = "0";
  m[1] = "y";
  m[2] = "0";
  m[3] = "y";
  m[4] = "-x";
  m[5] = "x";
  m[6] = "0";
  m[7] = "y";
  m[8] = "y";
  m[9] = "y";
  m[10] = "-x";
  m[11] = "x";
  m[12] = "0";
  m[13] = "0";
  return m;
}
map<int, string> create_map_right()
{
  map<int, string> m;
  m[0] = "0";
  m[1] = "y";
  m[2] = "-x";
  m[3] = "0";
  m[4] = "y";
  m[5] = "0";
  m[6] = "-x";
  m[7] = "y";
  m[8] = "y";
  m[9] = "0";
  m[10] = "0";
  m[11] = "0";
  m[12] = "y";
  m[13] = "0";
  return m;
}
map<int, string> create_map_left()
{
  map<int, string> m;
  m[0] = "0";
  m[1] = "y";
  m[2] = "x";
  m[3] = "0";
  m[4] = "0";
  m[5] = "y";
  m[6] = "x";
  m[7] = "0";
  m[8] = "y";
  m[9] = "y";
  m[10] = "0";
  m[11] = "0";
  m[12] = "0";
  m[13] = "y";
  return m;
}
int main()
{
    int W; // number of columns.
    int H; // number of rows.
    map<int, string> piecesTop = create_map_top();
    map<int, string> piecesRight = create_map_right();
    map<int, string> piecesLeft = create_map_left();
    cin >> W >> H; cin.ignore();
    int ** columns = new int * [H];
    for (int i = 0; i < H; i++) {
        columns[i] = new int[W];
        int LINE; // represents a line in the grid and contains W integers. Each integer represents one room of a given type.
        for(int j = 0; j < W; j++){
            cin >> LINE; cin.ignore();
            columns[i][j] = LINE;
        }            
    }
    int EX; // the coordinate along the X axis of the exit (not useful for this first mission, but must be read).
    cin >> EX; cin.ignore();
    cerr << EX << endl;
    // game loop
    while (1) {
        int XI;
        int YI;
        string POS;
        string dir;
        cin >> XI >> YI >> POS; cin.ignore();
        cerr << XI << " " << YI << " " << POS <<  endl;
        int pieces = columns[YI][XI];
        cerr << "type piece " << pieces << endl;
        if(POS == "TOP"){
            dir = piecesTop.at(pieces);           
        }else if(POS == "RIGHT"){
            dir = piecesRight.at(pieces);
        }else{
            dir = piecesLeft.at(pieces);
        }
         if(dir == "x")
            XI++;
        else if(dir == "-x")
            XI--;
        else
            YI++;
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // One line containing the X Y coordinates of the room in which you believe Indy will be on the next turn.
        cout << XI << " " << YI << endl;
    }
}