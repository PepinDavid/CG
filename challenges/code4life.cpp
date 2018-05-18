//note place 767/2366

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
     return a.rank < b.rank;
 };
 bool sortByPlayerId(const Sample &a, const Sample &b){
     return a.idPlayer < b.idPlayer;
 };
 bool sortByLength(const int &a, const int &b){
   return a > b;
 };

template<class InputIt, class T, class BinaryOperation>
T accumulate(InputIt first, InputIt last, T init,
             BinaryOperation op)
{
    for (; first != last; ++first) {
        init = op(init, *first);
    }
    return init;
};
 class Robot{
     private:
        int _id;
        string _target;
        int _eta;
        int _score;
        map<string, int> _storeMolsExp;
        map<string, int> _storeMols;
        map<string, int> _availMols;
        vector<Sample> _samples;
        vector<string> _lettersMols;
        bool _diag = false;
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
            _storeMols = {{ "A", storageA}, {"B", storageB}, {"C", storageC}, {"D", storageD}, {"E", storageE}};
            _storeMolsExp = {{ "A", expertiseA}, {"B", expertiseB}, {"C", expertiseC}, {"D", expertiseD}, {"E", expertiseE}};
            _lettersMols.clear();
        }
        void setSample(vector<Sample> const &samples){
                _samples = samples;
        }
        void updateSample(const vector<Sample> &samp){
            for(int j = 0; j < samp.size(); ++j){
                for(int i = 0; i < _samples.size(); ++i){
                    if(samp[j].sampleId == _samples[i].sampleId){
                        _samples[i] = samp[j];
                    }
                }
            }
        }
        void updateAvailMols(map<string, int> &availMols){
            _availMols = availMols;
        }
        //if target diagnosis
        bool isNotDiag(){
            for(int i = 0; i < _samples.size(); ++i){
                if(_samples[i].costTotal < 0 && _samples[i].idPlayer == 0){
                    return true;
                }
            }
            return false;
        }
        //for diagnosis samples
        int getSampleId() {
            for(int i = 0; i < _samples.size(); ++i){
                if(_samples[i].costTotal < 0 && _samples[i].idPlayer == 0)
                    return _samples[i].sampleId;
            }
            return -1;
        }
        int getSampleIdDiag() {
            for(int i = 0; i < _samples.size(); ++i){
                if(compareAvailMols(_samples[i].mols) && _samples[i].idPlayer == -1)
                    return _samples[i].sampleId;
            }
            return -1;
        }
        //eject samples not possbile
        int getSampleIdImpossible(){
            for(int i = 0; i < _samples.size(); ++i){
                if(_samples[i].idPlayer == 0 && compareAvailDiag(_samples[i].mols))
                    return _samples[i].sampleId;
            }
            return -1;
        }
        //find sample in laboratory for eject it
        int getSampleChooseId(){
            for(int i = 0; i < _samples.size(); ++i){
                if( _samples[i].idPlayer == 0){
                    if(compareMols(_samples[i].mols))
                        return i;
                }
            }
            return -1;
        }
        //get samples by rank and experience mols
        int getSampleRank() {
            int size = _samples.size();
            int r = betterRank();
            if(r < 1){
                return 1;
            }else if(r >= 1 && r <= 4){
                if(size < 2)
                    return 1;
                else if(size >= 2 || size < 3)
                    return 2;
            }else if(r > 4 && r <= 6){
                if(size < 1)
                    return 1;
                else if(size >= 1 || size < 3)
                    return 2;
            }else if(r > 6 && r <= 8){
                if(size < 2)
                    return 2;
                else if(size >= 2 || size < 3)
                    return 3;
            }else{
                return 3;
            }
        }
        //set array for catch all letters is possible
        void setMolsType(){
            int sum = accumulate(begin(_storeMols), end(_storeMols), 0, [](int value , const map<string, int>::value_type& p){return value+p.second;});
            if(sum < MAX_MOLECULE){
                for(int i = 0; i < _samples.size(); ++i){
                    if(_samples[i].idPlayer == 0){
                        //debugMols(_samples[i].mols);
                        if(!compareMols(_samples[i].mols)){
                            for(auto mol: _samples[i].mols){
                                int reste = (mol.second - _storeMolsExp[mol.first] > 0)?(mol.second - _storeMolsExp[mol.first]): (_storeMolsExp[mol.first]-mol.second);
                                if(_availMols[mol.first] >= reste && _storeMolsExp[mol.first] < mol.second){
                                    //cerr << "letters " << mol.first << " :" << _availMols[mol.first] << " >= " << (mol.second - _storeMolsExp[mol.first]) << " && " << _storeMolsExp[mol.first] << " < " << mol.second << endl;
                                    //(_availMols[mol.first] - mol.second > 0)? _availMols[mol.first] -= mol.second: _availMols[mol.first] = 0;
                                    _lettersMols.push_back(mol.first);
                                }
                            }
                        }
                    }
                }
            }
        }
        string getMolsType(){
            for(auto l: _lettersMols){
                return l;
            }
            return "";
        }
        //look if have enough mmols for sample
        bool enoughMols(){
            for(int i = 0; i < _samples.size(); ++i){
                if(_samples[i].idPlayer == 0){
                    if(compareMols(_samples[i].mols))
                        return true;
                }
            }
            return false;
        }
        //size vector of my samples
        int sizeMySamples(){
            int size = 0;
            for(int i = 0; i < _samples.size(); ++i){
                if(_samples[i].idPlayer == 0)
                    size++;
            }
            return size;
        }
        string actionDiag(){
            string resp;
            if(getSampleId() > -1 && isNotDiag()){
                resp = "CONNECT " + to_string(getSampleId());
                return resp;
            }
            if(getSampleIdImpossible() > -1){
                resp =  "CONNECT " + to_string(getSampleIdImpossible());
                return resp;
            }
            if(enoughMols())
                resp = "GOTO LABORATORY";
            else{
                if(getSampleIdDiag() > -1 && sizeMySamples() < 3)
                    resp = "CONNECT " + to_string(getSampleIdDiag());
                else if(sizeMySamples() < 1)
                    resp = "GOTO SAMPLES";
                else
                    resp = "GOTO MOLECULES";
            }
            return resp;
        }
        string actionMolecules(){
            string resp;
            if(getMolsType().size() > 0){
                resp = "CONNECT " + getMolsType();
                return resp;
            }else{
                for(int i = 0; i < _samples.size(); i++){
                    if(_samples[i].idPlayer == 0){
                        if(compareMols(_samples[i].mols) && _lettersMols.size() < 1)
                            return "GOTO LABORATORY";
                    }
                }
                if(getSampleIdImpossible() > -1){
                    resp =  "GOTO DIAGNOSIS";
                }
                if(resp.size() > 1 && sizeMySamples() < 3)
                    return resp;
                else{
                    if(sizeMySamples() > 2)
                        resp = "WAIT";
                    else
                        resp = "GOTO SAMPLES";
                    return resp;
                }
            }
        }
        string actionLabo(){
            string resp;
            if(getSampleChooseId() > -1){
                int itSamp = getSampleChooseId();
                int idSamp = _samples[itSamp].sampleId;
                _samples.erase(_samples.begin() + itSamp);
                return "CONNECT " + to_string(idSamp);
            }else{
                sort(_samples.begin(), _samples.end(), sortByPlayerId);
                for(int i = 0; i < _samples.size(); ++i){
                    if(_samples[i].idPlayer == 0 && compareAvailMols(_samples[i].mols) ){
                        return "GOTO MOLECULES";
                    }
                }
                if(getSampleIdDiag() > -1){
                    resp =  "GOTO DIAGNOSIS";
                }
                if(resp.size() > 1 && sizeMySamples() < 3)
                    return resp;

                return "GOTO SAMPLES";
            }
        }
        int out(){
            if(_target == "START_POS")
                return MODULES::SAMPLES;
            if(_eta > 0){
                return MODULES::WAIT;
            }else if(_target == "SAMPLES" && sizeMySamples() < MAX_SAMPLE){
                return -(MODULES::SAMPLES);
            }else if(_target == "SAMPLES" && sizeMySamples() >= MAX_SAMPLE){
                return MODULES::DIAGNOSIS;
            }else if(_target == "DIAGNOSIS"){
                return -(MODULES::DIAGNOSIS);
            }else if(_target == "MOLECULES"){
                return -(MODULES::MOLECULES);
            }else if(_target == "LABORATORY"){
                return -(MODULES::LABORATORY);
            }
        }
    private:
        bool compareAvailMols(map<string, int> &mols){
            if(mols["A"] <= (_availMols["A"]+_storeMolsExp["A"])
                && mols["B"] <= (_availMols["B"]+_storeMolsExp["B"])
                 && mols["C"] <= (_availMols["C"]+_storeMolsExp["C"])
                  && mols["D"] <= (_availMols["D"]+_storeMolsExp["D"])
                   && mols["E"] <= (_availMols["E"]+_storeMolsExp["E"]))
                return true;
            else
                return false;
        }
        bool compareAvailDiag(map<string, int> &mols){
            bool isCheck = false;
            for(auto mol: mols){
                if(mol.second > 0){
                    if(mol.second > _availMols[mol.first] + _storeMolsExp[mol.first])
                        isCheck = true;
                    else{
                        isCheck = false;
                        break;
                    }
                }
            }
            return isCheck;
        }
        bool compareMols(map<string, int> &mols){
            bool isCheck = false;
            for(auto mol: mols){
                if(mol.second > 0){
                    if(_storeMolsExp[mol.first] >= mol.second)
                        isCheck = true;
                    else{
                        isCheck = false;
                        break;
                    }
                }
            }
            return isCheck;
        }
        int betterRank(){
            int rank = 0;
            for(auto mol: _storeMolsExp){
                rank += mol.second;
            }
            return rank;
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
        vector<map<string, int>> _projects;
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
        void setProjects(map<string, int> &projs){
            _projects.push_back(projs);
        }
        void setMolsAvailable(map<string, int> &_availMols){
            _availableMols = _availMols;
        }
        void setRobots(int id, string target, int eta, int score, int storageA, int storageB, int storageC, int storageD, int storageE, int expertiseA, int expertiseB, int expertiseC, int expertiseD, int expertiseE){
            if(id == 0)
                _me.setRobot(id, target, eta, score, storageA, storageB, storageC, storageD, storageE, storageA+expertiseA, storageB+expertiseB, storageC+expertiseC, storageD+expertiseD, storageE+expertiseE);
            // else
            //     _enemy.setRobot(id, target, eta, score, storageA, storageB, storageC, storageD, storageE, expertiseA, expertiseB, expertiseC, expertiseD, expertiseB);
        }
        void play(const vector<Sample> &samp){
            if(samp.size() > 0)
                setAllSamples(samp);
            _me.updateSample(_availableSamples);
            _me.updateAvailMols(_availableMols);
            _me.setMolsType();

            int resp = _me.out();
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
                    cout << _me.actionDiag() << endl;
                    break;
                case 3:
                    cout << "GOTO MOLECULES" << endl;
                    break;
                case -3:
                    cout << _me.actionMolecules() << endl;
                    break;
                case 4:
                    cout << "GOTO LABORATORY" << endl;
                    break;
                case -4:
                        cout << _me.actionLabo() << endl;
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
        map<string, int> _availMols;
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
        _availMols = {{"A", availableA}, {"B", availableB}, {"C", availableC}, {"D", availableD}, {"E", availableE}};
        game.setMolsAvailable(_availMols);

        int sampleCount;
        cin >> sampleCount; cin.ignore()
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
