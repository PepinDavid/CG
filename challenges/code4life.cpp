#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <random>



using namespace std;

/**
 * Bring data on patient samples from the diagnosis machine to the laboratory with enough molecules to produce _medicine!
 **/

const int MAX_SAMPLE = 3;
const int MAX_MOLECULE = 10;

enum MODULES { START_POS, SAMPLES, DIAGNOSIS, MOLECULES, LABORATORY, WAIT };
enum RANK_BOT { ZERO, EASY, MEDIUM, HARD, VERY_HARD, EXPERT };

struct Sample{
    int sampleId;
    int idPlayer;
    int rank;
    string expertiseGain;
    int health;
    int costTotal;
    map<string, int> mols;
    bool completeMol = false;
};

struct MoleculesIdentifier{
    const string A = "A";
    const string B = "B";
    const string C = "C";
    const string D = "D";
    const string E = "E";
};

MoleculesIdentifier molecules;

int randomNumber() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1, 10);

    return distribution(gen);
}

const int RANDOM_NUMBER = randomNumber();

bool sortByCostTotal(const Sample &a,const Sample &b){
    return a.costTotal > b.costTotal;
};

bool sortByRank(const Sample &a,const Sample &b){
    return a.rank < b.rank;
};

bool sortByPlayerId(const Sample &a, const Sample &b){
    return a.idPlayer < b.idPlayer;
};

bool sortByLength(const int &a, const int &b){
return a > b;
};

template<class InputIt, class T, class BinaryOperation>
T sumStoreMolecules(InputIt first, InputIt last, T init, BinaryOperation op) {
    for (; first != last; ++first) {
        init = op(init, *first);
    }
    return init;
};

 class Robot{
     private:
        int _id;
        int _eta;
        int _score;
        int _rank = RANK_BOT::ZERO;
        string _target;
        bool _diag = false;
        bool _firstVisit = true;
        map<string, int> _storeMolsExp;
        map<string, int> _storeMols;
        map<string, int> _storeTotalMols;
        map<string, int> _tableMols;
        vector<Sample> _samples;
        vector<string> _lettersMols;
        
    public:
        Robot(){
            _id = 0;
            _target = "";
            _score = 0;
            _eta = 0;
        }
        ~Robot(){};
        void setRobot(int id, string target, int eta, int score, int storageA, int storageB, int storageC, int storageD, int storageE, int expertiseA, int expertiseB, int expertiseC, int expertiseD, int expertiseE){
            _id = id;
            _target = target;
            _eta = eta;
            _score = score;
            string A = "A";
            _storeMols = {
                {molecules.A, storageA},
                {molecules.B, storageB},
                {molecules.C, storageC},
                {molecules.D, storageD},
                {molecules.E, storageE}
            };
            _storeMolsExp = {
                {molecules.A, expertiseA},
                {molecules.B, expertiseB},
                {molecules.C, expertiseC},
                {molecules.D, expertiseD},
                {molecules.E, expertiseE}
            };
            _storeTotalMols = {
                {molecules.A, storageA + expertiseA},
                {molecules.B, storageB + expertiseB},
                {molecules.C, storageC + expertiseC},
                {molecules.D, storageD + expertiseD},
                {molecules.E, storageE + expertiseE}
            };
            _lettersMols.clear();
        }

        void setTableMolecules(map<string, int> &tableMols) {
            _tableMols = tableMols;
        }

        void setSample(vector<Sample> const &samples) {
            _samples = samples;
        }

        //if target diagnosis
        bool isNotDiag(){
            for(int i = 0; i < _samples.size(); ++i){
                if(_samples[i].costTotal < 0){
                    return true;
                }
            }
            return false;
        }

        //for diagnosis samples
        int getSampleId() {
            for(int i = 0; i < _samples.size(); ++i){
                if(_samples[i].costTotal < 0)
                    return _samples[i].sampleId;
            }
            return -1;
        }

        int getSampleIdDiag(vector<Sample> &diagSamples) {
            for(int i = 0; i < diagSamples.size(); ++i){
                if (compareAvailMolsTableAndExperience(diagSamples[i].mols))
                    return diagSamples[i].sampleId;
            }

            return -1;
        }

        //eject samples not possible
        pair<int, int> getNCheckSample(){
            for(int i = 0; i < _samples.size(); ++i){
                if(compareMolsOnDiagnosis(_samples[i].mols)) {
                    return {_samples[i].sampleId, i};
                }

            }
            return {-1, -1};
        }

        //find sample in laboratory for eject it
        int getSampleChooseId(){
            for(int i = 0; i < _samples.size(); ++i){
                if(compareMolInHandAndTotal(_samples[i].mols))
                    return i;
            }

            return -1;
        }
        //get samples by rank and experience mols
        int actionSamples(vector<Sample>& samplesDiag) {
            int sum = sumStoreMolecules(begin(_storeMols), end(_storeMols), 0, [](int value , const map<string, int>::value_type& p){return value+p.second;});
            int sampleInHands = _samples.size();
            int idSamplePossibleInDiag = getSampleIdDiag(samplesDiag);

            if (idSamplePossibleInDiag > -1 && _samples.size() < 3)
                sampleInHands++;

            int r = betterRank();

            if(r < 1){
                return 1;
            }else if(r >= 1 && r <= 4){
                if(sampleInHands < 2)
                    return 1;
                else if(sampleInHands >= 2 || sampleInHands < 3)
                    return 2;
            }else if(r > 4 && r <= 6){
                if(sampleInHands < 1)
                    return 1;
                else if(sampleInHands >= 1 || sampleInHands < 3)
                    return 2;
            }else if(r > 6 && r <= 8 || sum == MAX_MOLECULE){
                if(sampleInHands < 2)
                    return 2;
                else if(sampleInHands >= 2 || sampleInHands < 3)
                    return 3;
            }else{
                return 3;
            }

        }

        //set array for catch all letters is necessary
        void takeMolsTypeForSample(vector<Sample> samples){
            int sum = sumStoreMolecules(begin(_storeMols), end(_storeMols), 0, [](int value , const map<string, int>::value_type& p){return value+p.second;});
            map<string, int> totalMoleculesToTake;

            for(int i = 0; i < samples.size(); ++i) {
                if(sum == MAX_MOLECULE){
                    break;
                }

                map<string, int> moleculesToTake;

                for(auto mol: samples[i].mols){
                    if(_tableMols[mol.first] > 0) {
                        int totalTotal = mol.second;

                        if (samples[i].expertiseGain == mol.first && i > 0)
                            totalTotal = (mol.second - 1);

                        moleculesToTake[mol.first] = totalTotal;
                        totalMoleculesToTake[mol.first] += totalTotal;
                    }
                }

                for(auto& mol: moleculesToTake) {
                    int molToTake = 0;
                
                    if (totalMoleculesToTake[mol.first] > _storeTotalMols[mol.first]) 
                        molToTake = totalMoleculesToTake[mol.first] - _storeTotalMols[mol.first];

                    for(int j = 0; j < molToTake; j++) {
                        // cerr << "molecule taken: " << mol.first << endl;
                        _lettersMols.push_back(mol.first);
                    }
                }
            }
        }

        //look if have enough mols for sample
        vector<int> enoughMolsExperience(){
            vector<int> samplesPossible;
            for(int i = 0; i < _samples.size(); ++i){
                if(compareMolInHandAndTotal(_samples[i].mols))
                    samplesPossible.push_back(_samples[i].sampleId);
            }

            return samplesPossible;
        }

        vector<int> enoughMolsTableAndExperience(){
            vector<int> samplesPossible;
            for(int i = 0; i < _samples.size(); ++i){
                if(compareAvailMolsTableAndExperience(_samples[i].mols))
                    samplesPossible.push_back(_samples[i].sampleId);
            }

            return samplesPossible;
        }
        
        string actionDiag(vector<Sample> &diagSamples){
            int sum = sumStoreMolecules(begin(_storeMols), end(_storeMols), 0, [](int value , const map<string, int>::value_type& p){return value+p.second;});

            if (getSampleId() > -1 && isNotDiag()) {
                return "CONNECT " + to_string(getSampleId());
            }

            vector<Sample> samplesNotPossible;
            for(auto& s: _samples) {
                if(!compareAvailMolsTableAndExperience(s.mols) || (!checkMolsSampleComplete(s.mols) && sum == MAX_MOLECULE)) {
                    cerr << "sample not possible" << endl;
                    samplesNotPossible.push_back(s);
                }
            }

            for(auto& s: samplesNotPossible) {
                return "CONNECT " + to_string(s.sampleId);
            }

            if(diagSamples.size() > 0 && _samples.size() < 3) {
                int idSamplePossibleInDiag = getSampleIdDiag(diagSamples);

                if (idSamplePossibleInDiag > -1 && sum < MAX_MOLECULE) {
                    return "CONNECT " + to_string(idSamplePossibleInDiag);
                }
            }

            vector<int> samplesWithEnoughMolsExperience = enoughMolsExperience();
                
            if(samplesWithEnoughMolsExperience.size() > 0) {
                if(_samples.size() < 2) {
                    return "GOTO SAMPLES";
                }

                return "GOTO LABORATORY";
            }

            if(_samples.size() < 1) {
                return "GOTO SAMPLES";
            }

            return "GOTO MOLECULES";
        }

        string actionMolecules(Robot& enemy, vector<Sample>& samplesDiag) {
            string resp;
            
            takeMolsTypeForSample(_samples);

            for (auto l: _lettersMols) {
                return "CONNECT " + l;
            }

            int sum = sumStoreMolecules(begin(_storeMols), end(_storeMols), 0, [](int value , const map<string, int>::value_type& p){return value+p.second;});

            if(sum < MAX_MOLECULE) {
                if (samplesDiag.size() && _samples.size() < 2) {
                    int idSamplePossibleInDiag = getSampleIdDiag(samplesDiag);

                    if (idSamplePossibleInDiag > -1) {
                        takeMolsTypeForSample(samplesDiag);

                        for (auto l: _lettersMols) {
                            return "CONNECT " + l;
                        }

                        return "GOTO DIAGNOSIS";
                    }
                }
            }

            for(int i = 0; i < _samples.size(); i++) {
                if(checkMolsSampleComplete(_samples[i].mols))
                    return "GOTO LABORATORY";
            }

            pair<int, int> sampleImpossible = getNCheckSample();

            if (sampleImpossible.first > -1) {
                cerr << "ici" << endl;
                return  "GOTO DIAGNOSIS";
            }

            for(int i = 0; i < _samples.size(); i++) {
                cerr << "là" << endl;
                if(!checkMolsSampleComplete(_samples[i].mols))
                    return "GOTO DIAGNOSIS";
            }

            if(_samples.size() < 1) {
                resp = "GOTO SAMPLES";
            }

            return resp;
        }

        string actionLabo(vector<Sample> &diagSamples){
            string resp;
            if (getSampleChooseId() > -1) {
                int itSamp = getSampleChooseId();
                int idSamp = _samples[itSamp].sampleId;
                _samples.clear();
                return "CONNECT " + to_string(idSamp);
            } else {
                if (_samples.size() > 1) {
                    for(int i = 0; i < _samples.size(); i++) {
                        if(compareAvailMolsTableAndExperience(_samples[i].mols))
                            return "GOTO MOLECULES";
                    }
                }

                if(diagSamples.size() > 0) {
                    int idSamplePossibleInDiag = getSampleIdDiag(diagSamples);
                    
                    if (idSamplePossibleInDiag > -1 && _samples.size() < 2) {
                        return "GOTO MOLECULES";
                    }
                }

                return "GOTO SAMPLES";
            }
        }
        int out(Robot& enemy, vector<Sample>& diagSamples){
            int sizeSample = MAX_SAMPLE;
            int idSamplePossibleInDiag = -1;

            if (diagSamples.size() > 0) 
                idSamplePossibleInDiag = getSampleIdDiag(diagSamples);

            if ((RANDOM_NUMBER >= 5 && _firstVisit)|| idSamplePossibleInDiag > -1)
                sizeSample = 2;

            if (_target == "START_POS")
                return MODULES::SAMPLES;

            if (_eta > 0) {
                return MODULES::WAIT;
            }else if(_target == "SAMPLES" && _samples.size() < sizeSample){
                return -(MODULES::SAMPLES);
            }else if(_target == "SAMPLES" && _samples.size() >= sizeSample){
                _firstVisit = false;
                return MODULES::DIAGNOSIS;
            }else if(_target == "DIAGNOSIS"){
                return -(MODULES::DIAGNOSIS);
            }else if(_target == "MOLECULES"){
                return -(MODULES::MOLECULES);
            }else if(_target == "LABORATORY"){
                return -(MODULES::LABORATORY);
            }

            return MODULES::WAIT;
        }

    private:
        bool compareAvailMolsTableAndExperience(map<string, int> &mols) {
            if(mols["A"] <= (_tableMols["A"]+_storeTotalMols["A"])
                && mols["B"] <= (_tableMols["B"]+_storeTotalMols["B"])
                 && mols["C"] <= (_tableMols["C"]+_storeTotalMols["C"])
                  && mols["D"] <= (_tableMols["D"]+_storeTotalMols["D"])
                   && mols["E"] <= (_tableMols["E"]+_storeTotalMols["E"]))
                return true;
            else
                return false;
        }

        bool checkMolsSampleComplete(map<string, int> &mols) {
            if(mols["A"] <= _storeTotalMols["A"]
                && mols["B"] <= _storeTotalMols["B"]
                 && mols["C"] <= _storeTotalMols["C"]
                  && mols["D"] <= _storeTotalMols["D"]
                   && mols["E"] <= _storeTotalMols["E"])
                return true;
            else
                return false;
        }

        bool compareMolInHandAndTotal(map<string, int> &sampleMols){
            bool isCheck = false;
    
            for(auto mol: sampleMols){
                if(mol.second > 0){
                    if(_storeTotalMols[mol.first] >= mol.second)
                        isCheck = true;
                    else{
                        isCheck = false;
                        break;
                    }
                }
            }

            return isCheck;
        }

        bool compareMolsOnDiagnosis(map<string, int> &sampleMols){
            for(auto mol: sampleMols){
                if(mol.second > 0){
                    cerr << mol.first << " " << mol.second << " " << (_storeTotalMols[mol.first] + _tableMols[mol.first]) << endl; 
                    if(_storeTotalMols[mol.first] + _tableMols[mol.first] < mol.second)
                        return true;
                }
            }

            return false;
        }
        int betterRank(){
            int rank = 0;
            for(auto mol: _storeMolsExp){
                rank += mol.second;
            }

            return rank;
        }
 };
 class Game{
     private:
        Robot _me;
        Robot _enemy;
        map<string, int> _availableMols;
        vector<Sample> _availableSamples;
        vector<Sample> _diagSamples;
        vector<map<string, int>> _projects;
    public:
        Game(){}
        ~Game(){}
        void addRobots(const Robot& me, const Robot& enemy){
            _me = me;
            _enemy = enemy;
        }

        void setAllSamples(const vector<Sample> &samp){
            _availableSamples = samp;
            vector<Sample> enemySamples;
            vector<Sample> mySamples;

            //sort available samples by bot id
            sort(_availableSamples.begin(), _availableSamples.end(), sortByPlayerId);

            for(int i = 0; i < _availableSamples.size(); i++){
                if(_availableSamples[i].idPlayer == 1)
                    enemySamples.push_back(_availableSamples[i]);
                else if(_availableSamples[i].idPlayer == -1)
                    _diagSamples.push_back(_availableSamples[i]);
                else if(_availableSamples[i].idPlayer == 0)
                    mySamples.push_back(_availableSamples[i]);
                
            }
            //send available samples to our bot
            _me.setSample(mySamples); //prend les samples lui appartenant ainsi que ceux stocké dans l'ordi diag,
            //possibilité d'amélioré en ne prenant que les siens mais pas sure de la reussite
        }
        void setProjects(map<string, int> &projs){
            for(auto &p: projs){
                cerr << "projetct: " << p.first << " : " << p.second << endl;
            }
            _projects.push_back(projs);
        }
        void setMolsAvailable(map<string, int> &availMols){
            _availableMols = availMols;
        }
        void setRobots(int id, string target, int eta, int score, int storageA, int storageB, int storageC, int storageD, int storageE, int expertiseA, int expertiseB, int expertiseC, int expertiseD, int expertiseE){
            if(id == 0)
                _me.setRobot(id, target, eta, score, storageA, storageB, storageC, storageD, storageE, expertiseA, expertiseB, expertiseC, expertiseD, expertiseE);
            else
                _enemy.setRobot(id, target, eta, score, storageA, storageB, storageC, storageD, storageE, expertiseA, expertiseB, expertiseC, expertiseD, expertiseB);
        }
        void play(const vector<Sample> &samp){
            if(samp.size() > 0)
                setAllSamples(samp);

            _me.setTableMolecules(_availableMols);

            int resp = _me.out(_enemy, _diagSamples);

            switch (resp) {
                case 1:
                    cout << "GOTO SAMPLES" << endl;
                    break;
                case -1:
                    cout << "CONNECT " << _me.actionSamples(_diagSamples) << endl; //take sample
                    break;
                case 2:
                    cout << "GOTO DIAGNOSIS" << endl;
                    break;
                case -2:
                    cout << _me.actionDiag(_diagSamples) << endl; //diag sample
                    break;
                case 3:
                    cout << "GOTO MOLECULES" << endl;
                    break;
                case -3:
                    cout << _me.actionMolecules(_enemy, _diagSamples) << endl; //take molecules
                    break;
                case 4:
                    cout << "GOTO LABORATORY" << endl;
                    break;
                case -4:
                        cout << _me.actionLabo(_diagSamples) << endl; //send sample with molecules
                    break;
                case 5:
                    cout << "WAIT" << endl;
                    break;
            }

            _diagSamples.clear();
        }
};

int main()
{
    int projectCount;
    Game game;
    Robot me = Robot();
    Robot enemy = Robot();
    game.addRobots(me, enemy);

    cin >> projectCount; cin.ignore();
    for (int i = 0; i < projectCount; i++) {
        int a;
        int b;
        int c;
        int d;
        int e;
        cin >> a >> b >> c >> d >> e; cin.ignore();
        map<string, int> mols = {{"A", a}, {"B", b}, {"C", c}, {"D", d}, {"E", e}};
        game.setProjects(mols);
    }

    // Game loop
    while (1) {
        vector<Sample> samples;
        map<string, int> availMols;
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
            if(i == 0)
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
