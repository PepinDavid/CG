//note: 3h30 de code, place 1332/2299

//enum
const DIRECTIONNUMBER = {
    S: {x: 0, y: -1},
    SW: {x: +1, y: -1},
    W: {x: +1, y: 0},
    NW: {x: +1, y: +1},
    N: {x: 0, y: +1},
    NE: {x: -1, y: +1},
    E: {x: -1, y: 0},
    SE: {x: -1, y: -1}
};

const PLAYER = {
    ME: "X",
    ENNEMY: "E"
};

class Units{
    constructor(x,y){
        this._x = x;
        this._y = y;
        this._lvl = 0;
    }
    get x(){
        return this._x;
    }
    get y(){
        return this._y;
    }
    set lvl(level){
        this._lvl = level;
    }
    get lvl(){
        return this._lvl;
    }
}

class Rect extends Units{
    constructor(x,y){
        super(x, y);

    }
    get coords(){
        return {x: this._x, y: this._y};
    }
    toString(){
        return this._x+" "+this._y+" "+this._lvl;
    }
}

class Player extends Units{
    constructor(x, y, idx, numPlayer){
        super(x,y);
        this._id = idx;
        this._player = numPlayer;
        this._futurMonter = [];
        this._futurDescente = [];
        this._futurConstruct = [];
        this._ConstructMonte = [];
        this._ConstructDescente = [];
    }
    get id() {
        return this._id;
    }
    get player(){
        return this._player;
    }
    findDeplacement(map){
        var rectAround = [];
        for(var k in DIRECTIONNUMBER){
            if(map.columns[this._y - (DIRECTIONNUMBER[k].y)] !== undefined){
                if(map.columns[this._y - (DIRECTIONNUMBER[k].y)][this._x - (DIRECTIONNUMBER[k].x)] !== undefined){
                    var rect = map.columns[this._y - (DIRECTIONNUMBER[k].y)][this._x - (DIRECTIONNUMBER[k].x)];
                   if(rect instanceof Rect){
                       if(rect.lvl > 0){
                           if((rect.lvl-1 == this._lvl || rect.lvl == this._lvl)&& rect.lvl < 4 && rect.lvl != '.')
                                this._futurMonter.push({ACTION: "MOVE&BUILD", r: rect, move: k});
                       }else if(rect.lvl <= this._lvl  && rect.lvl != '.')
                            this._futurDescente.push({ACTION: "MOVE&BUILD", r: rect, move: k});
                    }else if(rect instanceof Player){
                        if(rect.lvl > this._lvl && rect.lvl < 4 && rect.player != PLAYER.ME)
                            this._futurMonter.push({ACTION: "PUSH&BUILD", r: rect, move: k});
                        else if(rect.lvl <= this._lvl && rect.player != PLAYER.ME)
                            this._futurDescente.push({ACTION: "PUSH&BUILD", r: rect, move: k});
                    }
                }
            }
        }
    }
    findConstruct(map){
        //printErr('futur M : '+this._futurMonter.length)
        //printErr('futur D : '+this._futurDescente.length)
        if(this._futurMonter.length > 0){
            this._futurMonter.sort((a,b)=>{return a.r.lvl > b.r.lvl});
            this._futurMonter.forEach((monte)=>{
                for(var k in DIRECTIONNUMBER){
                    if(map.columns[monte.r.y - (DIRECTIONNUMBER[k].y)] !== undefined){
                        if(map.columns[monte.r.y - (DIRECTIONNUMBER[k].y)][monte.r.x - (DIRECTIONNUMBER[k].x)] !== undefined){
                            var rect = map.columns[monte.r.y - (DIRECTIONNUMBER[k].y)][monte.r.x - (DIRECTIONNUMBER[k].x)];
                            if(rect instanceof Rect && rect.lvl < 4 && rect.lvl != '.'){
                                if(monte.r instanceof Player){
                                    if(monte.r.lvl <= rect.lect)
                                        this._ConstructMonte.push({ACTION: monte.ACTION, r: rect, build: k, move: monte.move});
                                }else
                                    this._ConstructMonte.push({ACTION: monte.ACTION, r: rect, build: k, move: monte.move});
                            }
                        }
                    }
                }
            })
        }
        if(this._futurDescente.length > 0){
            this._futurDescente.forEach((desc)=>{
                for(var k in DIRECTIONNUMBER){
                    if(map.columns[desc.r.y - (DIRECTIONNUMBER[k].y)] !== undefined){
                        if(map.columns[desc.r.y - (DIRECTIONNUMBER[k].y)][desc.r.x - (DIRECTIONNUMBER[k].x)] !== undefined){
                            var rect = map.columns[desc.r.y - (DIRECTIONNUMBER[k].y)][desc.r.x - (DIRECTIONNUMBER[k].x)];
                            if(rect instanceof Rect && rect.lvl < 4 && rect.lvl != '.'){
                                if(desc.r instanceof Player){
                                    if(desc.r.lvl <= rect.lect)
                                        this._ConstructDescente.push({ACTION: desc.ACTION, r: rect, build: k, move: desc.move});
                                }else
                                    this._ConstructDescente.push({ACTION: desc.ACTION, r: rect, build: k, move: desc.move});
                            }
                        }
                    }
                }
            })
        }
    }
    maxMove(map){
        this.findDeplacement(map);
        this.findConstruct(map);
        return this._ConstructMonte.length + this._ConstructDescente.length;
    }
    resp(){
        if(this._ConstructMonte.length > 0){
            //printErr('monte')
            this._ConstructMonte.sort((a,b)=>{return a.r.lvl > b.r.lvl});
            print(this._ConstructMonte[0].ACTION+" "+this._id+" "+this._ConstructMonte[0].move+" "+this._ConstructMonte[0].build)
        }else if(this._ConstructDescente.length > 0){
            //printErr('descend')
            this._ConstructDescente.sort((a,b)=>{return a.r.lvl > b.r.lvl});
            print(this._ConstructDescente[0].ACTION+" "+this._id+" "+this._ConstructDescente[0].move+" "+this._ConstructDescente[0].build)
        }
    }
    toString(){
        return this._x+" "+this._y+" "+this._id+" "+this._lvl;
    }
}

class Map {
    constructor(size){
        this._size = size;
        this._columns = new Array(size);
        for(var i = 0; i < this._columns.length; i++){
            this._columns[i] = new Array(size);
        }
    }
    set columns(unit){
        this._columns[unit.y][unit.x] = unit;

    }
    get columns(){
        return this._columns;
    }
    printMap(){
        for (var i = 0; i < this._columns.length; i++) {
            var row = this._columns[i];
            var r = '';
            for(var j = 0; j < row.length; j++){
                if(row[j] instanceof Rect)
                    r += row[j].lvl;
                else
                    r += row[j].player;
            }
           printErr(r)
        }
    }
}


var size = parseInt(readline());
var carte = new Map(size);
var unitsPerPlayer = parseInt(readline());
// game loop
while (true) {
    var myPlayer = [];
    var enPlayer = [];
    for (var i = 0; i < size; i++) {
        var row = readline();
       for(var j = 0; j < row.length; j++){
           var rect = new Rect(j, i);
           rect.lvl = row[j];
           carte.columns = rect;
       }
    }

    for (var i = 0; i < unitsPerPlayer; i++) {
        var inputs = readline().split(' ');
        var unitX = parseInt(inputs[0]);
        var unitY = parseInt(inputs[1]);
        var play = new Player(unitX, unitY, i, PLAYER.ME);
        play.lvl = carte.columns[unitY][unitX].lvl;
        carte.columns = play;
        myPlayer.push(play);
    }
    for (var i = 0; i < unitsPerPlayer; i++) {
        var inputs = readline().split(' ');
        var otherX = parseInt(inputs[0]);
        var otherY = parseInt(inputs[1]);
        var play = new Player(otherX, otherY, i, PLAYER.ENNEMY);
        play.lvl = carte.columns[unitY][unitX].lvl;
        carte.columns = play;
        enPlayer.push(play);
    }

   // carte.printMap();



    var legalActions = parseInt(readline());
    printErr('legalactions : '+legalActions)
    for (var i = 0; i < legalActions; i++) {
        var inputs = readline().split(' ');
        var atype = inputs[0];
        var index = parseInt(inputs[1]);
        var dir1 = inputs[2];
        var dir2 = inputs[3];
    }

    //myPlayer[0].resp(carte)
    var index = 0;
    var max = 0;
    for(var i = 0; i < myPlayer.length; i++){
        var move =myPlayer[i].maxMove(carte)
        printErr(move)
        if(max < move){
            index = i;
            max = move;
        }
    }
    myPlayer[index].resp();
}
