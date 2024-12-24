#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

// ASCII 65[0] -> 91[26];
const int minAlpha = 65, maxAlpha = 91;

int main()
{

    string operation, response;
    array<string, 3> rotors;
    getline(cin, operation);

    int pseudo_random_number;
    cin >> pseudo_random_number; cin.ignore();

    if (pseudo_random_number > 26) {
        pseudo_random_number %= 26;
    }

    for (int i = 0; i < 3; i++) {
        string rotor;
        getline(cin, rotor);
        rotors[i] = rotor;
    }

    string message;
    getline(cin, message);

    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    vector<int> char_in_integer;

    if (operation == "ENCODE") {
        int counter = 0;

        for(char& c: message) {
            int cesar_char, ascii_value = static_cast<int>(c);
            cesar_char = ascii_value + pseudo_random_number;

            if (cesar_char >= maxAlpha) {
                cesar_char -= 26;
            }

            cesar_char = cesar_char + counter;

            if (cesar_char >= maxAlpha) {
                cesar_char -= 26;
            }

            char_in_integer.push_back(cesar_char);
            counter++;

            if(counter >= 26) {
                counter = 0;
            }
        }
        
        for (string rotor: rotors) {
            for (int i = 0; i < char_in_integer.size(); i++) {
                int c = char_in_integer[i];
                
                char_in_integer[i] = rotor[c - 65];
            }
        }

        for (const int& i: char_in_integer) response += static_cast<char>(i);
    } else {
        vector<char> index_finder(message.size());

        for (int j = rotors.size() -1; j >= 0; j--) {
            string rotor = rotors[j];
            cerr << rotor << endl;
            for (int i = 0; i < message.size(); i++) {
                int index = rotor.find(message[i]) + 65;
                message[i] = static_cast<char>(index);
            }
        }

        int counter = 0;
        for (char& c: message) {
            int cesar_char = c - pseudo_random_number;

            if (cesar_char < minAlpha) {
                cesar_char += 26;
            }

            cesar_char = cesar_char - counter;

            if (cesar_char < minAlpha) {
                cesar_char += 26;
            }

            counter++;

            if(counter >= 26) {
                counter = 0;
            }

            response += cesar_char;
        }
    }

    cout << response << endl;
}
