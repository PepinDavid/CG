/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class Node {
    constructor(x, y, id, exit) {
        this._id = id;
        this._x = x;
        this._y = y;
        this._children = [];
    }
    addChildren (node) {
        const id = node._id;
        if (this._children.length < 1)
            this._children.push(node._id);
        else {
            let finded = false;
            for (let i = 0; i < this._children.length; i++) {
                let idChildren = this._children._id;
                if (idChildren === id) {
                    finded = true;
                    break;
                }
            }
            if(!finded)
                this._children.push(node._id);
        }
    }
}

const A_Star = (graph, start, end) => {
    const visited = {},
        cost = {},
        children = {},
        file = [];
    Object.keys(graph).forEach((id) => { 
        visited[id] = false;
        children[id] = -1;
        cost[id] = 0;
    });

    file.push(start);

    while (file.length > 0) {
        const node = file.shift();

        visited[node._id] = true;

        node._children.forEach((childNodeId) => {
            const childNode = graph[childNodeId];

            if (!visited[childNodeId]) {
                if (node._id !== childNodeId) {
                    // insert back in file
                    file.push(childNode); 
                    // calculate weight between nodes
                    cost[childNodeId] = cost[node._id] + Math.abs((Math.pow(childNode._y - node._y, 2) - Math.pow(childNode._x - node._x, 2)));
                    children[childNodeId] = node._id;
                }
            }
        });
    }
    Object.keys(graph).forEach((id) => { 
        console.error("start path")
        print_path(id, end._id, children)
    });
    return cost;
}

const print_path = (start, end, children) => {
    if(start === end)
        console.error(start);
    else if(children[end] === -1)
        console.error("pas de chemin vers ", end);
    else {
        print_path(start, children[end], children);
        console.error(end);
    }
}

const buildId = (l) => {
    let asciiNB = l.charCodeAt(0);
    asciiNB++;
    return String.fromCharCode(asciiNB);
}

var inputs = readline().split(' ');
const nbFloors = parseInt(inputs[0]); // number of floors
const width = parseInt(inputs[1]); // width of the area
const nbRounds = parseInt(inputs[2]); // maximum number of rounds
const exitFloor = parseInt(inputs[3]); // floor on which the exit is found
const exitPos = parseInt(inputs[4]); // position of the exit on its floor
const nbTotalClones = parseInt(inputs[5]); // number of generated clones
const nbAdditionalElevators = parseInt(inputs[6]); // number of additional elevators that you can build
const nbElevators = parseInt(inputs[7]); // number of elevators
const elevators = {};
let letter = "a";
let graph = {};

elevators[exitFloor] = [exitPos];

let n = new Node(exitPos, exitFloor, letter, true);

const nextLevelElevator = (obj, it) => {
    if (obj[it] === undefined) {
        it += 1;
        return nextLevelElevator(obj, it);
    } else
        return it;
}

for (let i = 0; i < nbElevators; i++) {
    var inputs = readline().split(' ');
    const elevatorFloor = parseInt(inputs[0]); // floor on which this elevator is found
    const elevatorPos = parseInt(inputs[1]); // position of the elevator on its floor
    if (elevators[elevatorFloor] === undefined)
        elevators[elevatorFloor] = [elevatorPos];
    else
        elevators[elevatorFloor].push(elevatorPos);
}

// game loop
while (true) {
    var inputs = readline().split(' ');
    const cloneFloor = parseInt(inputs[0]); // floor of the leading clone
    const clonePos = parseInt(inputs[1]); // position of the leading clone on its floor
    const direction = inputs[2]; // direction of the leading clone: LEFT or RIGHT
    let elevatorsArr = [];
    // Write an action using console.log()
    // To debug: console.error('Debug messages...');
    
    if (elevators[cloneFloor] === undefined) {
        let nextLevel = nextLevelElevator(elevators, cloneFloor);
        
        elevatorsArr = elevators[nextLevel];
        
        if(elevatorsArr.length > 1) {
            let moreClose = -1,
                distClose = 100;

            elevatorsArr.forEach( (el, i) => {
                let dist = Math.abs(clonePos - el);
                if(dist < distClose)
                    distClose = dist, moreClose = i;
            });

            if(clonePos > elevatorsArr[moreClose]-1 && direction == "RIGHT" )
                elevators[cloneFloor] = clonePos, console.log('ELEVATOR');
            else if(clonePos < elevatorsArr[moreClose]-1 && direction == "LEFT" )
                elevators[cloneFloor] = clonePos, console.log('ELEVATOR')
            else
                console.log('WAIT');
        } else {
            if(clonePos > elevatorsArr[0]-1 && direction == "RIGHT" )
                elevators[cloneFloor] = clonePos, console.log('ELEVATOR');
            else if(clonePos < elevatorsArr[0]-1 && direction == "LEFT" )
                elevators[cloneFloor] = clonePos, console.log('ELEVATOR')
            else
                console.log('WAIT');   
        }
    } else {
        elevatorsArr = elevators[cloneFloor];
        
        if(elevatorsArr.length > 1) {
            let moreClose = -1,
                distClose = 100;

            elevatorsArr.forEach( (el, i) => {
                let dist = Math.abs(clonePos - el);
                if(dist < distClose)
                    distClose = dist, moreClose = i;
            });

            if(clonePos > elevatorsArr[moreClose] && direction == "RIGHT" )
                elevators[cloneFloor] = clonePos, console.log('BLOCK');
            else if(clonePos < elevatorsArr[moreClose] && direction == "LEFT" )
                elevators[cloneFloor] = clonePos, console.log('BLOCK')
            else
                console.log('WAIT');
        } else {
            if(clonePos > elevatorsArr[0] && direction == "RIGHT" )
                elevators[cloneFloor] = clonePos, console.log('BLOCK');
            else if(clonePos < elevatorsArr[0] && direction == "LEFT" )
                elevators[cloneFloor] = clonePos, console.log('BLOCK')
            else
                console.log('WAIT');
        }
    }
}
