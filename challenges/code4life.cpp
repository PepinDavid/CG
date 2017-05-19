#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>



using namespace std;

/**
 * Bring data on patient samples from the diagnosis machine to the laboratory with enough molecules to produce _medicine!
 **/

 const int MAX_SAMPLE = 3;
 const int MAX_MOLECULE = 10;

enum MODULES { START_POS, SAMPLES, DIAGNOSIS, MOLECULES, LABORATORY, WAIT };

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
 bool sortByRank(const Sample &a,const Sample &b){
     return a.rank > b.rank;
 };
 bool sortByPlayerId(const Sample &a, const Sample &b){
     return a.idPlayer < b.idPlayer;
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
        vector<Sample> _samples;
        Sample sampleChoose;
        bool _diag = false;
        bool _full = false;
        bool _allMols = false;
        string _rep;
    public:
        Robot(){
            _id = 0;
            _target = "";
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

            _storeMols = {{ "A", (storageA+expertiseA)}, {"B", (storageB+expertiseB)}, {"C", (storageC+expertiseC)}, {"D", (storageD+expertiseD)}, {"E", (storageE+expertiseE)}};
        }
        void setSample(vector<Sample> const &samples){
                _samples = samples;
        }
        string getMolsType(){
            int sum = accumulate(begin(_storeMols), end(_storeMols), 0, [](int value , const map<string, int>::value_type& p){return value+p.second;});
            for(int i = 0; i < _samples.size(); ++i){
                if( sum <= MAX_MOLECULE && _samples[i].costTotal > 0){
                    for(auto mol: _samples[i].mols){
                        if(_storeMols[mol.first] < mol.second)
                            return mol.first;
                    }
                }
            }
            return "F";
        }
        int getSampleId() {
            for(int i = 0; i < _samples.size(); ++i){
                    if(_samples[i].costTotal < 0)
                        return _samples[i].sampleId;
            }
            return -1;
        }
        void updateSample(const vector<Sample> &samp){
            for(int j = 0; j < samp.size(); ++j){
                for(int i = 0; i < _samples.size(); ++i){
                    if(samp[j].sampleId == _samples[i].sampleId){
                        _samples[i] = samp[j];
                        cerr << _samples[i].sampleId << endl;
                        debugMols(_samples[i].mols);
                        break;
                    }
                }
            }
        }
        int getSampleChooseId(){
            cerr << _target << endl;
            for(int i = 0; i < _samples.size(); ++i){
                cerr << "    compare : " << compareAvailMols(_samples[i].mols, _storeMols) << endl;
                if(compareMols(_samples[i].mols))
                    return _samples[i].sampleId;
            }
            return -1;
        }
        int getSampleRank() {
            int size = _samples.size();
            if(size < 2)
                return 1;
            else if(size >= 2 || size < 3){
                return 2;
            }
        }
        int out(map<string, int> &availMols){
            if(_target == "START_POS")
                return MODULES::SAMPLES;
            if(_eta > 0){
                return MODULES::WAIT;
            }else if(_target == "SAMPLES" && _samples.size() < MAX_SAMPLE){
                return -(MODULES::SAMPLES);
            }else if(_target == "SAMPLES" && _samples.size() >= MAX_SAMPLE){
                return MODULES::DIAGNOSIS;
            }else if(_target == "DIAGNOSIS" && !_diag){
                _diag = true;
                for(int i = 0; i < _samples.size(); ++i){
                    if(_samples[i].costTotal < 0)
                        _diag = false;
                }
                return -(MODULES::DIAGNOSIS);
            }else if(_target == "DIAGNOSIS"){
                for(int i = 0; i < _samples.size(); ++i){
                    cerr << compareAvailMols(_samples[i].mols, availMols) << endl;
                    if(compareAvailMols(_samples[i].mols, availMols))
                        return MODULES::MOLECULES;
                    else{
                        _diag = false;
                        return MODULES::DIAGNOSIS;
                    }
                }
            }else if(_target == "MOLECULES"){
                int sum = accumulate(begin(_storeMols), end(_storeMols), 0, [](int value , const map<string, int>::value_type& p){return value+p.second;});
                for(int i = 0; i < _samples.size(); ++i){
                    if(compareAvailMols(_samples[i].mols, _storeMols)){
                        return MODULES::LABORATORY;
                    }
                }
                return -(MODULES::MOLECULES);
            }else if(_target == "LABORATORY"){
                cerr << _target << endl;
                if(_samples.size() > 0){
                    for(int i = 0; i < _samples.size(); ++i){
                        cerr << _samples[i].sampleId << " compareMols : " << compareMols(_samples[i].mols) << " compareAvailMols : " << compareAvailMols(_samples[i].mols, _storeMols)<<endl;
                        if(compareMols(_samples[i].mols)){
                            return -(MODULES::LABORATORY);
                        }
                    }
                    return MODULES::MOLECULES;
                }else{
                    _diag = false;
                    return MODULES::SAMPLES;
                }
            }
        }
    private:

        bool compareAvailMols(map<string, int> &mols, map<string, int> &availMols){
            cerr << availMols["A"] << " " << availMols["B"] << " " << availMols["C"] << " " << availMols["D"] << " " << availMols["E"] << endl;
            if(mols["A"] <= availMols["A"] && mols["B"] <= availMols["B"] && mols["C"] <= availMols["C"] && mols["D"] <= availMols["A"] && mols["E"] <= availMols["E"])
                return true;
            else
                return false;
        }
        bool compareMols(map<string, int> &mols){
            bool isCheck = false;
            for(auto mol: mols){
                if(mol.second > 0){
                    if(_storeMols[mol.first] >= mol.second)
                        isCheck = true;
                    else
                        isCheck = false;
                }
            }
            return isCheck;
        }
        void debugMols(map<string, int> &mols){
            for(auto mol: mols)
                cerr << "string : " << mol.first <<" qty : " << mol.second << endl;
        }
 };
 class Game{
     private:
        Robot _me;
        Robot _enemy;
        map<string, int> _availableMols;
        vector<Sample> _availableSamples;
    public:
        Game(){}
        ~Game(){}
        void setAllSamples(const vector<Sample> &samp){
            _availableSamples = samp;
            vector<int> index;
            sort(_availableSamples.begin(), _availableSamples.end(), sortByPlayerId);
            for(int i = 0; i < _availableSamples.size(); i++){
                if(_availableSamples[i].idPlayer == 1)
                    index.push_back(i);
            }
            for(int i = 0; i < index.size(); ++i)
                _availableSamples.erase(_availableSamples.begin()+index[i]);

            _me.setSample(_availableSamples);
        }
        void setMolsAvailable(map<string, int> &availMols){
            _availableMols = availMols;
        }
        void setRobots(int id, string target, int eta, int score, int storageA, int storageB, int storageC, int storageD, int storageE, int expertiseA, int expertiseB, int expertiseC, int expertiseD, int expertiseE){
            if(id == 0)
                _me.setRobot(id, target, eta, score, storageA, storageB, storageC, storageD, storageE, expertiseA, expertiseB, expertiseC, expertiseD, expertiseB);
            else
                _enemy.setRobot(id, target, eta, score, storageA, storageB, storageC, storageD, storageE, expertiseA, expertiseB, expertiseC, expertiseD, expertiseB);
        }
        void play(const vector<Sample> &samp){
            if(samp.size() > 0)
                setAllSamples(samp);
            _me.updateSample(_availableSamples);

            int resp = _me.out(_availableMols);
            cerr << "resp : " << resp << endl;
            switch (resp) {
                case 1:
                    cout << "GOTO SAMPLES" << endl;
                    break;
                case -1:
                    cout << "CONNECT " << _me.getSampleRank() << endl;
                    break;
                case 2:
                    cout << "GOTO DIAGNOSIS" << endl;
                    break;
                case -2:
                    if(_me.getSampleId() > -1)
                        cout << "CONNECT " << _me.getSampleId() << endl;
                    else
                        cout << "GOTO MOLECULES" << endl;
                    break;
                case 3:
                    cout << "GOTO MOLECULES" << endl;
                    break;
                case -3:
                    if(_me.getMolsType() != "F")
                        cout << "CONNECT " << _me.getMolsType() << endl;
                    else
                        cout << "GOTO LABORATORY" << endl;
                    break;
                case 4:
                    cout << "GOTO LABORATORY" << endl;
                    break;
                case -4:
                        cout << "CONNECT " << _me.getSampleChooseId() << endl;
                    break;
                case 5:
                    cout << "WAIT" << endl;
                    break;
            }
        }
 };
int main()
{
    int projectCount;
    Game game;
    cin >> projectCount; cin.ignore();
    cerr << "projectCount : " << projectCount << endl;
    for (int i = 0; i < projectCount; i++) {
        int a;
        int b;
        int c;
        int d;
        int e;
        cin >> a >> b >> c >> d >> e; cin.ignore();
        cerr << a << " " << b << " " << c << " " << d << " " << e << endl;
    }

    // Game loop
    while (1) {
        vector<Sample> samples;
        map<string, int> availMols;
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
            cerr << "eta " << eta << endl;
            game.setRobots(i, target, eta, score, storageA, storageB, storageC, storageD, storageE, expertiseA, expertiseB, expertiseC, expertiseD, expertiseE);
        }
        int availableA;
        int availableB;
        int availableC;
        int availableD;
        int availableE;
        cin >> availableA >> availableB >> availableC >> availableD >> availableE; cin.ignore();
        availMols = {{"A", availableA}, {"B", availableB}, {"C", availableC}, {"D", availableD}, {"E", availableE}};
        game.setMolsAvailable(availMols);

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
        // To debug: cerr << "Debug _messages..." << endl;
        game.play(samples);
    }
}
