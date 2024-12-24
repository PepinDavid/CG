/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

enum ESIDE {
    R = 'R',
    L = 'L',
}

enum EWAY {
    '>' = '>',
    'v' = 'v',
    '<' = '<',
    '^' = '^',
}

enum EDIRECTION {
    RIGHT = 'RIGHT',
    LEFT = 'LEFT',
    TOP = 'TOP',
    BOTTOM = 'BOTTOM',
}

type TMatrice2D = string[][];

interface IPosition {
    x?: number;
    y?: number;
}

interface IPikachu {
    position: IPosition;
    side?: ESIDE;
    way?: EWAY;
}

const maze: TMatrice2D = [];

function drawMaze(maze: TMatrice2D): void {
    for (let row of maze) {
        console.error(row.join(''))
    }
}

function fillingMaze(maze: TMatrice2D, pikachuPosition: IPosition, valueCell: number, NextPosition: IPosition, pikachuWay: EWAY): number {
    maze[pikachuPosition.y][pikachuPosition.x] = valueCell.toString();
    valueCell = parseInt(maze[NextPosition.y][NextPosition.x]) + 1;
    maze[NextPosition.y][NextPosition.x] = pikachuWay;

    return valueCell;
}

const pikachu: IPikachu = {
    position: {x: 0, y: 0},
};

function positionToString(position: IPosition): string {
    return `${position.x},${position.y}`;
}

function findWallPosition(pikachu: IPikachu): [IPosition, EDIRECTION] {
    const wallPosition = {...pikachu.position};
    const way = pikachu.way;
    const wallOrientation = pikachu.side;

    switch (way) {
        case EWAY['>']:
            wallPosition.y = wallOrientation === ESIDE.L ? wallPosition.y -1 : wallPosition.y +1;
            return [wallPosition, EDIRECTION.RIGHT];

        case EWAY['<']:
            wallPosition.y = wallOrientation === ESIDE.L ? wallPosition.y +1 : wallPosition.y -1;
            return [wallPosition, EDIRECTION.LEFT];

        case EWAY['^']:
            wallPosition.x = wallOrientation === ESIDE.L ? wallPosition.x -1 : wallPosition.x +1;
            return [wallPosition, EDIRECTION.TOP];

        case EWAY['v']:
            wallPosition.x = wallOrientation === ESIDE.L ? wallPosition.x +1 : wallPosition.x -1;
            return [wallPosition, EDIRECTION.BOTTOM];
    }
}

function isWallOrLimitMap(newPosition: IPosition, maze: TMatrice2D): boolean {
    return newPosition.y < 0 || newPosition.y > maze.length -1 || newPosition.x < 0 || newPosition.x > maze[0].length -1 || maze[newPosition.y][newPosition.x] === '#';    
}

function changeWayDirection(pikachuWay: EWAY, wallDirection: ESIDE): EWAY {
    const ways = Object.keys(EWAY);
    const lengthWays = ways.length;

    let nextIndexWay = ways.findIndex(w => pikachuWay === w);
    nextIndexWay = wallDirection === ESIDE.L ? nextIndexWay + 1 : nextIndexWay - 1;

    if (nextIndexWay >= lengthWays)
        nextIndexWay = 0;

    if (nextIndexWay < 0)
        nextIndexWay = lengthWays - 1;

    return EWAY[ways[nextIndexWay]];
}

function walkToNextCase(pikachu: IPikachu, maze: TMatrice2D, directionToWalk: EDIRECTION): [IPosition, EWAY] {
    const direction = {
        right: {x: pikachu.position.x +1, y: pikachu.position.y},
        left: {x: pikachu.position.x -1, y: pikachu.position.y},
        top: {x: pikachu.position.x, y: pikachu.position.y -1},
        bottom: {x: pikachu.position.x, y: pikachu.position.y +1},
    };

    switch (EDIRECTION[directionToWalk]) {
        case EDIRECTION.RIGHT:
            if (isWallOrLimitMap(direction.right, maze))
                return [pikachu.position, changeWayDirection(pikachu.way, pikachu.side)];

            return [direction.right, pikachu.way];
        case EDIRECTION.LEFT:
            if (isWallOrLimitMap(direction.left, maze))
                return [pikachu.position, changeWayDirection(pikachu.way, pikachu.side)];
            
            return [direction.left, pikachu.way];
        case EDIRECTION.TOP:
            if (isWallOrLimitMap(direction.top, maze))
                return [pikachu.position, changeWayDirection(pikachu.way, pikachu.side)];
            
            return [direction.top, pikachu.way];
        case EDIRECTION.BOTTOM:
            if (isWallOrLimitMap(direction.bottom, maze))
                return [pikachu.position, changeWayDirection(pikachu.way, pikachu.side)];
            
            return [direction.bottom, pikachu.way];
    }
}

function move(pikachu: IPikachu, maze: TMatrice2D) {
    const startPosition: IPosition = {x: pikachu.position.x, y: pikachu.position.y};
    let valueCell = 0;
    let actualPosition: IPosition = {x: -1, y: -1};
    let counter = 0;

    while (positionToString(startPosition) !== positionToString(actualPosition) || counter < 4) {
        const [wallPosition, directionToWalk] = findWallPosition(pikachu);

        actualPosition = pikachu.position;

        if (isWallOrLimitMap(wallPosition, maze)) {
            const [nextPosition, way] = walkToNextCase(pikachu, maze, directionToWalk);

            pikachu.position = nextPosition;
            pikachu.way = way;
        } else {
            const direction = {
                right: {x: pikachu.position.x +1, y: pikachu.position.y},
                left: {x: pikachu.position.x -1, y: pikachu.position.y},
                top: {x: pikachu.position.x, y: pikachu.position.y -1},
                bottom: {x: pikachu.position.x, y: pikachu.position.y +1},
            };

            pikachu.way = changeWayDirection(pikachu.way, pikachu.side === ESIDE.L ? ESIDE.R : ESIDE.L);

            switch (pikachu.way) {
                case EWAY['>']:
                    pikachu.position = direction.right;
                    break;
                case EWAY['v']:
                    pikachu.position = direction.bottom;
                    break;
                case EWAY['<']:
                    pikachu.position = direction.left;
                    break;
                case EWAY['^']:
                    pikachu.position = direction.top;
                    break;
            }
        }

        if (actualPosition.x !== pikachu.position.x || actualPosition.y !== pikachu.position.y)
            valueCell = fillingMaze(maze, actualPosition, valueCell, pikachu.position, pikachu.way);

        actualPosition = pikachu.position;
        counter++;
    }
    
    maze[pikachu.position.y][pikachu.position.x] = counter === 4 ? '0' : '1';
}

var inputs: string[] = readline().split(' ');
const width: number = parseInt(inputs[0]);
const height: number = parseInt(inputs[1]);
const ways = Object.keys(EWAY);

let index = -1;

for (let i = 0; i < height; i++) {
    const line: string = readline();
    const cells = line.split('');
    
    if (index == -1)
        cells.forEach((cell, j) => {
            if (ways.includes(EWAY[cell]))
                index = j;
        });

    if (index > -1) {
        pikachu.way = EWAY[cells[index]];
        pikachu.position = {x: index, y: i};
        index = -1;
    }

    maze.push(cells);
}

pikachu.side = ESIDE[readline()];

move(pikachu, maze);

for (let i = 0; i < height; i++) {
    console.log(maze[i].join(''));
}
