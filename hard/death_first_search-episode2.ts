/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

enum EStateNode {
    TEMPORARY = 'TEMPORARY',
    VISITED = 'VISITED',
}

interface IGraphe {
    [key: number]: Array<string>
}

interface INode {
    [key: string]: {weight?: 0, isLeaf: boolean}
}

const graphe: IGraphe = {};
const nodes: INode = {};

var inputs: string[] = readline().split(' ');
const N: number = parseInt(inputs[0]); // the total number of nodes in the level, including the gateways
const L: number = parseInt(inputs[1]); // the number of links
const E: number = parseInt(inputs[2]); // the number of exit gateways

for (let i = 0; i < L; i++) {
    var inputs: string[] = readline().split(' ');
    const N1: number = parseInt(inputs[0]); // N1 and N2 defines a link between these nodes
    const N2: number = parseInt(inputs[1]);

    nodes[N1] = {isLeaf: false};
    nodes[N2] = {isLeaf: false};

    if (!graphe[N1])
        graphe[N1] = [''+N2];
    else
        graphe[N1].push(''+N2);

    if (!graphe[N2])
        graphe[N2] = [''+N1];
    else
        graphe[N2].push(''+N1);
}

for (let i = 0; i < E; i++) {
    const EI: string = readline(); // the index of a gateway node

    nodes[EI] = {isLeaf: true};
}

function addWeightBetweenRootNodeToLeaf(entryNode, graphe): Array<any> {
    let actualNode = entryNode;

    const nodesState = {[actualNode]: EStateNode.VISITED};
    const nodesVisited = [{weight: 0, nodes: [actualNode]}]
    const nodesToVisit = [actualNode];

    while (nodesToVisit.length) {
        actualNode = nodesToVisit.shift();
 
        const inferiorLevel = nodesVisited.find(el => el.nodes.includes(actualNode));
        const inferiorIndex = nodesVisited.findIndex(el => el.nodes.includes(actualNode));
        const children = graphe[actualNode];
        let actualLevel = nodesVisited[inferiorIndex + 1];
        
        for (let child of children) {
            if (nodesState[child] !== EStateNode.VISITED) {
                if (actualLevel === undefined) {
                    actualLevel = {weight: inferiorLevel.weight + 1, nodes: []};
                    nodesVisited.push(actualLevel)
                }
    
                if (!actualLevel.nodes.includes(child)) {
                    nodesState[child] = EStateNode.TEMPORARY;
                    actualLevel.nodes.push(child);
                    nodesToVisit.push(child);
                }
            }
        }
        
        nodesState[actualNode] = EStateNode.VISITED;
    }
    
    return nodesVisited;
}

function getWeight(weights, neighborNode) {

    for (const weightGroup of weights) {
        if (weightGroup.nodes.includes(neighborNode)) {
            return weightGroup.weight;
        }
    }

    return Infinity; // Pas de connexion si pas de poids trouvé
}

function findShortestPath(graphe, levelNodes, nodes, startNode, endNodes) {
    const distances = {};
    const previousNodes = {};
    const priorityQueue = [];

    for (const node in graphe) {
        distances[node] = Infinity;
        previousNodes[node] = null;
    }

    distances[startNode] = 0;
    priorityQueue.push({node: startNode, priority: 0});
    priorityQueue.sort((a, b) => a.priority - b.priority);

    while (priorityQueue.length > 0) {
        const currentNode = priorityQueue.shift().node;

        if (endNodes.includes(currentNode))
            break;

        for (const neighbor of graphe[currentNode]) {
            const weight = getWeight(levelNodes, neighbor);
            const altDistance = distances[currentNode] + weight;

            if (altDistance < distances[neighbor]) {
                distances[neighbor] = altDistance;
                previousNodes[neighbor] = currentNode;
                priorityQueue.push({node: neighbor, priority: altDistance});
                priorityQueue.sort((a, b) => a.priority - b.priority);
            }
        }
    }

    const path = [];
    let currentNode = endNodes.find(node => distances[node] !== Infinity);
    
    while (currentNode) {
        path.unshift(currentNode);
        currentNode = previousNodes[currentNode];
    }

    return { distance: distances[path[path.length - 1]], path };
}

function removeLinkInGraph(graphe, nodes, nodeA, nodeB) {
    const indexA = graphe[nodeA].findIndex(el => el === nodeB);
    const indexB = graphe[nodeB].findIndex(el => el === nodeA);
    
    graphe[nodeA].splice(indexA, 1);
    graphe[nodeB].splice(indexB, 1);

    if (!graphe[nodeA].length) {
        nodes[nodeA].isLeaf = false;
        delete graphe[nodeA]
    }

    if (!graphe[nodeB].length) {
        nodes[nodeB].isLeaf = false;
        delete graphe[nodeB]
    }
}

function getPrioritiesNodesToCut(pathNodes) {
    const length = pathNodes.length;

    return [pathNodes[length - 2], pathNodes[length - 1]];
}

// game loop
while (true) {
    const SI: number = parseInt(readline()); // The index of the node on which the Bobnet agent is positioned this turn
    const endNodes = Object.keys(nodes).filter(el => nodes[el].isLeaf ? el : null)
    const levelNodes = addWeightBetweenRootNodeToLeaf(''+SI, graphe);
    const paths = [];
    
    for (let endNode of endNodes) {
        const shortestPath = findShortestPath(graphe, levelNodes, nodes, '' + SI, [endNode]);

        paths.push(shortestPath);
    }

    const [priorityNode] = paths.sort((a, b) => a.distance - b.distance);
    let [nodeA, nodeB] = getPrioritiesNodesToCut(priorityNode.path);

    removeLinkInGraph(graphe, nodes, nodeA, nodeB);

    console.log(`${nodeA} ${nodeB}`);
}