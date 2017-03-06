#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * The while loop represents the game.
 * Each iteration represents a turn of the game
 * where you are given inputs (the heights of the mountains)
 * and where you have to print an output (the index of the mountain to fire on)
 * The inputs you are given are automatically updated according to your last actions.
 **/
int main()
{
    // game loop
    while (1) {
        int * arrMoun = new int [8];
        int nbMountain = 0;
        int maxSize(0);
        int tempSize(0);
        
        for (int i = 0; i < 8; i++) {           
            int mountainH; // represents the height of one mountain.
            cin >> mountainH; cin.ignore();
            arrMoun[i] = mountainH;
        }
        
        for (int i = 0; i < sizeof(arrMoun); i++) {
            tempSize = arrMoun[i];
            if(maxSize < tempSize)
            {
                maxSize = tempSize;
                nbMountain = i;                
            }
        }
        
        cout << nbMountain << endl;

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        //cout << "4" << endl; // The index of the mountain to fire on.
    }
}