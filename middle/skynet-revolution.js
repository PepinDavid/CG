let find = (arr, search)=>{
    for(let i = 0; i < arr.length; i++){
        if(arr[i][0] == search)
            return i;
    }
    return -1;
}
var inputs = readline().split(' ');
var N = parseInt(inputs[0]); // the total number of nodes in the level, including the gateways
var L = parseInt(inputs[1]); // the number of links
var E = parseInt(inputs[2]); // the number of exit gateways
let lvl = [];
let exits = [];
for (var i = 0; i < L; i++) {
    var inputs = readline().split(' ');
    var N1 = parseInt(inputs[0]); // N1 and N2 defines a link between these nodes
    var N2 = parseInt(inputs[1]);
    lvl.push([N1,N2]);
}
for (var i = 0; i < E; i++) {
    var EI = parseInt(readline()); // the index of a gateway node
    for(let j = 0; j < lvl.length; j++){
        if(lvl[j][0] == EI)
            exits.push([lvl[j][1], EI]);
        else if(lvl[j][1] == EI)
            exits.push([lvl[j][0], EI]);
    }
}

// game loop
while (true) {
    var SI = parseInt(readline()); // The index of the node on which the Skynet agent is positioned this turn
    let iLvl = find(lvl, SI);
    let iExits = find(exits, SI);
    let temp = [];
    printErr(iExits);
    if(iExits > -1){
        print(exits[iExits][0],exits[iExits][1]);
        //arr splice
    }else{
        print(lvl[iLvl][0],lvl[iLvl][1]);
    }
}