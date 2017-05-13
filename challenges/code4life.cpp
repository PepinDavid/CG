#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>



using namespace std;

/**
 * Bring data on patient samples from the diagnosis machine to the laboratory with enough molecules to produce medicine!
 **/

 const int MAX_SAMPLE = 3;
 const int MAX_MOLECULE = 10;
 struct Sample{
    int sampleId;
    int idPlayer;
    int rank;
    string expertiseGain;
    int health;
    int costTotal;
    map<string, int> mols;
 };
 bool sortByCostTotal(const Sample &a,const Sample &b){
     return a.costTotal > b.costTotal;
 };
 bool sortByLength(const int &a, const int &b){
   return a > b;
 }
 class Robot{
     private:
        int _id;
        string _target;
        int _eta;
        int _score;
        map<string, int> _storeMols;
        Sample _samples;
        bool _chooseSample = false;
        bool _full = false;
        string _rep;
    public:
        Robot(){
            _id = 0;
            _target = "DIAGNOSIS";
            _score = 0;
            _eta = 0;
        }
        ~Robot(){};
        string goTarget();
        void setRobot(int id, string target, int eta, int score, int storageA, int storageB, int storageC, int storageD, int storageE, int expertiseA, int expertiseB, int expertiseC, int expertiseD, int expertiseE){
            _id = id;
            _target = target;
            _eta = eta;
            _score = score;

            _storeMols = {{ "A", (storageA-expertiseA)}, {"B", (storageB-expertiseB)}, {"C", (storageC-expertiseC)}, {"D", (storageD-expertiseD)}, {"E", (storageE-expertiseE)}};
        }
        void setSample(vector<Sample> const &samples){
            if(!_chooseSample)
                _samples = samples[0];
        }
        void chooseSample(){
            sortSampleMols();
            _rep = "CONNECT " + _samples.sampleId;
            cerr << "rep : chooseSample " << _samples.sampleId << endl;
        }
        void getMols(){
            int sum = accumulate(begin(_storeMols), end(_storeMols), 0, [](int value , const map<string, int>::value_type& p){return value+p.second;});
            if( sum <= MAX_MOLECULE && sum <= _samples.costTotal){
                for(auto mol: _samples.mols){
                    cerr <<" mol: " << mol.first << endl;
                    if(_storeMols[mol.first] < mol.second){
                        cerr << "GET : " << mol.first << endl;
                        _rep = mol.first;
                    }
                }
            }
        }
        void sortSampleMols(){
            vector<string> index;
            for(auto it: _samples.mols){
                if(it.second == 0)
                    index.push_back(it.first);
            }
            for(int i = 0; i < index.size(); ++i)
                _samples.mols.erase(index[i]);
        }
        void out(){
            if(_target == "START_POS")
                cout << "GOTO DIAGNOSIS" << endl;
            if(_target == "DIAGNOSIS" && !_chooseSample){
                chooseSample();
                _chooseSample = true;
                cout << "CONNECT " << _samples.sampleId << endl;
            }else if(_target == "DIAGNOSIS" && _chooseSample)
                cout << "GOTO MOLECULES" << endl;
            else if(_target == "MOLECULES" && _chooseSample){
                int sum = accumulate(begin(_storeMols), end(_storeMols), 0, [](int value , const map<string, int>::value_type& p){return value+p.second;});
                if(sum <=  _samples.costTotal){
                    getMols();
                    cout << "CONNECT " << _rep << endl;
                }else{
                    cout << "GOTO LABORATORY" << endl;
                }
            }else if(_target == "LABORATORY"){
                if(_chooseSample){
                    cout << "CONNECT " << _samples.sampleId << endl;
                    _chooseSample = false;
                }else
                    cout << "GOTO DIAGNOSIS" << endl;
            }


        }
 };
 class Game{
     private:
        Robot me;
        Robot enemy;
        vector<Sample> allSamples;
        vector<Sample> availableSamples;
    public:
        Game(){}
        ~Game(){}
        void setAllSamples(const vector<Sample> &samp){
            allSamples = samp;
            availableSamples = samp;
            setAvailSamples();
        }
        void setRobots(int id, string target, int eta, int score, int storageA, int storageB, int storageC, int storageD, int storageE, int expertiseA, int expertiseB, int expertiseC, int expertiseD, int expertiseE){
            if(id == 0)
                me.setRobot(id, target, eta, score, storageA, storageB, storageC, storageD, storageE, expertiseA, expertiseB, expertiseC, expertiseD, expertiseB);
            else
                enemy.setRobot(id, target, eta, score, storageA, storageB, storageC, storageD, storageE, expertiseA, expertiseB, expertiseC, expertiseD, expertiseB);
        }
        void output(){
          me.out();
        }
    private:
        void setAvailSamples(){
            int index = -1;
            for(int i = 0; i < availableSamples.size(); ++i){
                if(availableSamples[i].idPlayer == 1){
                    index = i;
                    break;
                }
            }
            if(index != -1){
                availableSamples.erase(availableSamples.begin()+index);
                me.setSample(availableSamples);
            }else{
                me.setSample(allSamples);
                enemy.setSample(allSamples);
            }
        }
 };
int main()
{
    int projectCount;
    Game game;
    cin >> projectCount; cin.ignore();
    cerr << "projectCount : " << projectCount << endl;;
    for (int i = 0; i < projectCount; i++) {
        int a;
        int b;
        int c;
        int d;
        int e;
        cin >> a >> b >> c >> d >> e; cin.ignore();
        cerr << a << " " << b << " " << c << " " << d << " " << e << endl;
    }

    // game loop
    while (1) {
        vector<Sample> samples;
        cerr << "target" << endl;
        for (int i = 0; i < 2; i++) {
            string target;
            int eta;
            int score;
            int storageA;
            int storageB;
            int storageC;
            int storageD;
            int storageE;
            int expertiseA;
            int expertiseB;
            int expertiseC;
            int expertiseD;
            int expertiseE;
            cin >> target >> eta >> score >> storageA >> storageB >> storageC >> storageD >> storageE >> expertiseA >> expertiseB >> expertiseC >> expertiseD >> expertiseE; cin.ignore();
            game.setRobots(i, target, eta, score, storageA, storageB, storageC, storageD, storageE, expertiseA, expertiseB, expertiseC, expertiseD, expertiseE);
        }
        int availableA;
        int availableB;
        int availableC;
        int availableD;
        int availableE;
        cin >> availableA >> availableB >> availableC >> availableD >> availableE; cin.ignore();

        int sampleCount;
        cin >> sampleCount; cin.ignore();
        cerr << "samplecount " << sampleCount << endl;
        for (int i = 0; i < sampleCount; i++) {
            int sampleId;
            int carriedBy;
            int rank;
            string expertiseGain;
            int health;
            int costA;
            int costB;
            int costC;
            int costD;
            int costE;
            cin >> sampleId >> carriedBy >> rank >> expertiseGain >> health >> costA >> costB >> costC >> costD >> costE; cin.ignore();
            map<string, int> mols = {{"A", costA}, {"B", costB}, {"C", costC}, {"D", costD}, {"E", costE}};
            Sample s = {sampleId, carriedBy, rank, expertiseGain, health, costA+costB+costC+costD+costE, mols};
            samples.push_back(s);
        }
        sort(samples.begin(), samples.end(), sortByCostTotal);
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        game.setAllSamples(samples);
        game.output();
    }
}
