/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

enum TYPE_NODE {
    START = 'START',
    ELEVATOR = 'ELEVATOR',
    EXIT = 'EXIT',
}

enum ACTION {
    LEFT = 'LEFT',
    RIGHT = 'RIGHT',
    WAIT = 'WAIT',
    BLOCK = 'BLOCK',
}

function pow2(num) {
    return Math.pow(num, 2)
}

function calculateDistance(xStart, xEnd, yStart, yEnd) {
    const x = xEnd - xStart;
    const y = yEnd - yStart;

    return Math.sqrt(pow2(x) + pow2(y));
}

function findElevatorNextLevel(graphe, actualLevel) {
    const nextLevel = actualLevel + 1;
    if (graphe[nextLevel] === undefined)
        return findElevatorNextLevel(graphe, nextLevel);

    return [nextLevel, graphe[nextLevel]]
}

function findNearElevator(graphe, nodeStart, nodeEnd) {
    const actualLevel = nodeStart.y;
    const actualX = nodeStart.x;

    const elevators = graphe[actualLevel];
    const [nextLevel, nextElevators] = findElevatorNextLevel(graphe, actualLevel);    

}

const graphe = {}

let inputs: string[] = readline().split(' ');
const nbFloors: number = parseInt(inputs[0]); // number of floors
const width: number = parseInt(inputs[1]); // width of the area
const nbRounds: number = parseInt(inputs[2]); // maximum number of rounds
const exitFloor: number = parseInt(inputs[3]); // floor on which the exit is found
const exitPos: number = parseInt(inputs[4]); // position of the exit on its floor
const nbTotalClones: number = parseInt(inputs[5]); // number of generated clones
const nbAdditionalElevators: number = parseInt(inputs[6]); // number of additional elevators that you can build
const nbElevators: number = parseInt(inputs[7]); // number of elevators

graphe[exitFloor] = [{x: exitPos, type: TYPE_NODE.EXIT}];

for (let i = 0; i < nbElevators; i++) {
    inputs = readline().split(' ');
    const elevatorFloor: number = parseInt(inputs[0]); // floor on which this elevator is found
    const elevatorPos: number = parseInt(inputs[1]); // position of the elevator on its floor

    const node = {x: elevatorPos, type: TYPE_NODE.ELEVATOR};

    if (graphe[elevatorFloor] === undefined)
        graphe[elevatorFloor] = [node];
    else
        graphe[elevatorFloor].push(node);
}

// game loop
while (true) {
    inputs = readline().split(' ');
    const cloneFloor: number = parseInt(inputs[0]); // floor of the leading clone
    const clonePos: number = parseInt(inputs[1]); // position of the leading clone on its floor
    const direction: string = inputs[2]; // direction of the leading clone: LEFT or RIGHT

    const clonePosition = {y: cloneFloor, x: clonePos, type: TYPE_NODE.START};

    console.error(graphe)
    
    // Write an action using console.log()
    // To debug: console.error('Debug messages...');

    console.log('WAIT');     // action: WAIT or BLOCK

}
