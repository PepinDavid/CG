let GAMELOOP = 0;
let BOMB = 2;
let sort = (obj)=>{
    let sortable = [];
    for(var dist in obj){
        sortable.push([dist, obj[dist]])
    }
    return sortable.sort((a,b)=>{ return a[1] - b[1]; });
};
let sortingDist = (dist)=>{
    Object.keys(dist).forEach((arrObj)=>{
        dist[arrObj].sort((a, b)=>{
            return a.dist - b.dist;
        });
    });
};
class Unit{
    constructor(id){
        this.id = id;
        this.userId = 0;
        this.cyborgs = 0;
        this.production = 0;
        this.initial = false;
        this.parentDist = {};
        this.childrenDist = {};
    }
}
class Node extends Unit{
    constructor(id){
        super(id);
        this.parents = [];
        this.children = [];    
    }
};
class Tree{
    constructor(root){
        if(root === undefined)
            this._root = null;
        else
            this._root = root;
    };
    insert(parentId, childId, distance){
        if(this._root === null){
            this._root = new Node(parentId);
            this.insertChild(childId, distance, this._root);
        }else{
            this.insertTwice(parentId, childId, distance, this._root);
        }
    };
    insertChild(childId, distance, rootNode){
        var child = new Node(childId);
        child.parentDist[rootNode.id] = distance;
        child.parents.push(rootNode);

        rootNode.children.push(child);
        rootNode.childrenDist[child.id] = distance;
    };
    search(id){
        return this.searchChild(id, this._root);
    };
    searchChild(id, rootNode){
        if(rootNode === null)
            return null;
        if(rootNode.id == id)
            return rootNode;
        for(var i = 0; i < rootNode.children.length; i++){
            var n = this.searchChild(id, rootNode.children[i]);
            if(n !== null)
                return n
        }
        return null;
    };
    searchDirectChild(id, rootNode){
        var rep = null;
        if(rootNode.id === id)
            return rootNode;
        for(var i = 0; i < rootNode.children.length; i++){
            if(rootNode.children[i].id == id)
                return rootNode.children[i];
        }
        return rep;
    };
    searchParents(id, rootNode){
        if(rootNode.id === id)
            return rootNode;
        for(let i = 0; i < rootNode.parents.length; i++){
            let n = this.searchParents(id, rootNode.parents[i]);
            if(n !== null)
                return n
        }
        return null;
    };
    searchDirectParents(id, rootNode){
        if(rootNode.id === id)
            return rootNode;
        for(var i = 0; i < rootNode.parents.length; i++){
            if(rootNode.parents[i].id == id)
                return rootNode.parents[i];
        }
        return null;
    };
    insertTwice(parentId, childId, distance, rootNode){
        //look if nodes exist in tree
        let _p = this.search(parentId);
        let _c = this.search(childId);
        if(_p !== null){
            if(_c === null){
                this.insertChild(childId, distance, _p);
            }else{
                //look if _c exist
                if(this.searchDirectChild(_c.id, _p) === null){
                    _p.children.push(_c);
                    _p.childrenDist[_c.id] = distance;
                }
                if(this.searchDirectParents(_p.id, _c) === null){
                    _c.parents.push(_p);
                    _c.parentDist[_p.id] = distance;
                }
            }
        }else{
            if(_c !== null){
                _p = new Node(parentId);
                _p.children.push(_c);
                _p.childrenDist[_c.id] = distance;

                _c.parents.push(_p);
                _c.parentDist[_p.id] = distance;
            }
        }
    };
    maj(id, arg1, arg2, arg3){
        let node = this.search(id);
        node.userId = arg1;
        node.cyborgs = arg2;
        node.production = arg3;
        if(GAMELOOP === 0 && arg1 === 1){
            node.initial = true;
        }
    };
    majRoot(rootNode){
        if(rootNode === undefined)
            rootNode = this._root;
        if(rootNode.userId != 1){
            for(let i = 0; i < rootNode.children.length; i++){
                let n = rootNode.children[i];
                if(n.userId == 1){
                    return n;
                    break;
                }else{
                    return this.majRoot(rootNode.children[i]);
                }
            }
        }
    };
    height(rootNode){
        if(rootNode === undefined)
            rootNode = this._root;
        if(rootNode.children.length < 1)
            return 1;
        else{
            let maxDepth = 1;
            for(let i = 0; i < rootNode.children.length; i++){
                maxDepth = Math.max(maxDepth, this.height(rootNode.children[i]));
            }
            return maxDepth + 1;
        }
    };
}
class Attack{
    constructor(trees){
      this.trees = trees;
      this.troops = null;
      this.enemyTroops = null;
      this.bomb = {1: false};
    };
    rebuildTree(node){
        if(node.userId == 1){
            var t = new Tree(node);

        }
    };
    findClosestChild(nod, listeNode = []){
        var list = [];
        var node = this.tree._root;
        var rep = "WAIT";
        if(nod)
            node = nod;
        if(node == null)
            return rep;

        if(node.userId == 1){
            var nodeC = parseInt(node.cyborgs);
            if(this.enemyTroops !== null){
                if(this.enemyTroops.hasOwnProperty(node.id))
                        nodeC -= this.enemyTroops[node.id].nbCybs
            }
            if(node.production < 3 && nodeC > 10)
                rep += ";"+this.increaseFactory(node)

            list = sort(node.childrenDist);
            for(var i = 0; i < list.length; i++){
                var n = this.tree.searchDirectChild(list[i][0], node);
                var nC = 0;
                if(n.userId == -1){
                    if(BOMB > 0 && parseInt(n.cyborgs) > nodeC){
                        rep += "; BOMB "+node.id+" "+n.id;
                        BOMB--;
                    }
                    nC = parseInt(n.cyborgs)+parseInt((list[i][1]+1)*n.production);
                    if(this.troops.hasOwnProperty(node.id).hasOwnProperty(n.id))
                            nC -= this.troops[node.id][n.id].nbCybs
                    if(this.enemyTroops.hasOwnProperty(n.id))
                            nC += this.enemyTroops[n.id].nbCybs
                    if(nC < nodeC && nodeC > 0){
                        var c = nC+1;
                        node.cyborgs -= c;
                        rep += ";MOVE "+ node.id+" "+n.id+" "+ c;
                    }
                }
                if(n.userId === 0){
                    nC = parseInt(n.cyborgs);
                    if(this.enemyTroops.hasOwnProperty(n.id))
                            nC += this.enemyTroops[n.id].nbCybs;
                    if(this.troops.hasOwnProperty(node.id).hasOwnProperty(n.id))
                            nC -= this.troops[node.id][n.id].nbCybs;
                    var c = nC+1;
                    node.cyborgs -= c;
                    if(c > 0){
                        if(nC < nodeC && nodeC > 0){
                            rep += ";MOVE "+ node.id+" "+n.id+" "+ c;
                        }
                    }
                }
            }
        }
        return rep;

    };
    increaseFactory(node){
        var rep = "WAIT";
        if(node.cyborgs > 10 && node.production < 3 && node.userId == 1){
            rep = "INC "+node.id;
            node.cyborgs -= 10;
            return rep;
        }
        return rep;
    };
    addTroop(obj){
        printErr("addTroop")
        this.troops = obj;
    };
    addEnemyTroop(obj){
        this.enemyTroops = obj;
    };
    addBomb(obj){
        this.bomb = obj;
    };
    resp(){
        var r = "WAIT", rep = "";
        this.trees.map((tree)=>{
            this.tree = tree;
            rep += (this.findClosestChild())+";";
        });

        rep = rep.split(";")
        if(rep.length > 1){
            rep.map((v)=>{
                if(v.indexOf("WAIT") == -1){
                    r += ";"+v;
                }
            })
        }
        return r
    }
};

var factoryCount = parseInt(readline()); // the number of factories
var linkCount = parseInt(readline()); // the number of links between factories
var trees = []
var dist = {}
for (var i = 0; i < linkCount; i++) {
    var inputs = readline().split(' ');
    var factory1 = parseInt(inputs[0]);
    var factory2 = parseInt(inputs[1]);
    var distance = parseInt(inputs[2]);
    if(!dist.hasOwnProperty(factory1))
        dist[factory1] = [];
    if(!dist.hasOwnProperty(factory2))
        dist[factory2] = []

    dist[factory1].push({key: factory2, dist: distance});
    dist[factory2].push({key: factory1, dist: distance});
}
sortingDist(dist);
Object.keys(dist).forEach((arrObj)=>{
    var tree = new Tree();
    dist[arrObj].map((o)=>{
        tree.insert(arrObj, o.key, o.dist);
    });
    trees.push(tree);
})
printErr("height : ",trees.length);
// game loop
while (true) {
    var entityCount = parseInt(readline()); // the number of entities (e.g. factories and troops)
    var troop = {}, bomb = {}, enemyTroop = {};
    var rep = "";
    for (var i = 0; i < entityCount; i++) {
        var inputs = readline().split(' ');
        var entityId = parseInt(inputs[0]);
        var entityType = inputs[1];
        var arg1 = parseInt(inputs[2]);
        var arg2 = parseInt(inputs[3]);
        var arg3 = parseInt(inputs[4]);
        var arg4 = parseInt(inputs[5]);
        var arg5 = parseInt(inputs[6]);
        if(entityType === "FACTORY"){
            trees.map(v=>v.maj(entityId, arg1, arg2, arg3));
        }else if(entityType === "TROOP"){
            printErr(inputs);
            if(troop.hasOwnProperty(arg2).hasOwnProperty(arg3)){
                troop[arg2][arg3].nbCybs += arg4;
            }else{
                troop[arg2] = {};
                troop[arg2][arg3] = {
                    user: arg1,
                    nodeDep: arg2,
                    nodeArr: arg3,
                    nbCybs: arg4,
                    nbLap: arg5
                };
            }
            if(arg1 == -1){
                if(enemyTroop.hasOwnProperty(arg3)){
                    enemyTroop[arg3].nbCybs += arg4;
                }else{
                    enemyTroop[arg3] = {
                        user: arg1,
                        nodeDep: arg2,
                        nodeArr: arg3,
                        nbCybs: arg4,
                        nbLap: arg5
                    };
                }
            }
        }else if(entityType === "BOMB"){
            bomb[arg1] = {
                user: arg1,
                nodeDep: arg2,
                nodeArr: arg3,
                nbLap: arg4
            };
        }
    }

    var attack = new Attack(trees);
    attack.addTroop(troop);
    attack.addEnemyTroop(enemyTroop);
    attack.addBomb(bomb);
    var rep = attack.resp();
    print(rep.slice(0,rep.length-1));
    GAMELOOP++;
}
