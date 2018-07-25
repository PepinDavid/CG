#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N;
    cin >> N; cin.ignore();
    int M;
    cin >> M; cin.ignore();
    vector<string> registerName;
    vector<int> registerCpt;
    vector<string> listName;
    vector<string> listVote;
    for (int i = 0; i < N; i++) {
        string personName;
        int nbVote;
        cin >> personName >> nbVote; cin.ignore();
        registerName.push_back(personName);
        registerCpt.push_back(nbVote);
    }
    for (int i = 0; i < M; i++) {
        string voterName;
        string voteValue;
        cin >> voterName >> voteValue; cin.ignore();
        listName.push_back(voterName);
        listVote.push_back(voteValue);
    }
    vector<int> nameNoFind;
    for(int i = 0; i < listName.size(); i++){
        vector<string>::iterator it;
        it = find(registerName.begin(), registerName.end(), listName[i]);
        if(it == registerName.end())
            nameNoFind.push_back(i);
    }
    for(int i = 0; i < nameNoFind.size(); i++){
        listName.erase(listName.begin()+nameNoFind[i]);
        listVote.erase(listVote.begin()+nameNoFind[i]);
    }
    for(int i = 0; i < registerName.size(); i++){
        string name = registerName[i];
        int nbVote = registerCpt[i];
        nameNoFind.clear();
        for(int j = 0; j < listName.size(); j++){
            string n = listName[j];
            if(n == name)
                nameNoFind.push_back(j);
        }
        if(nameNoFind.size() > nbVote){
            int cptErase = 0;
            for(int j = 0; j < nameNoFind.size(); j++){
                listName.erase(listName.begin()+nameNoFind[j]-cptErase);
                listVote.erase(listVote.begin()+nameNoFind[j]-cptErase);
                cptErase++;
            }
        }
    }
    int yes = 0, no = 0;
    for(int i = 0; i < listVote.size(); i++){
        cerr << listName[i] << endl;
        string s = listVote[i];
        if(s == "Yes")
            yes++;
        else if(s == "No")
            no++;
    }

    cout << to_string(yes) << " " << to_string(no) << endl;
}
