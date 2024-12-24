const N = parseInt(readline()),
    objBegin = {},    
    keys = [];

    
for (let i = 0; i < N; i++) {
    var inputs = readline().split(' ');
    const J = parseInt(inputs[0]),
        D = parseInt(inputs[1]),
        T = J + D  - 1;
        
    if (objBegin[J]) {
        if(T < objBegin[J])
            objBegin[J] = T;
    } else
        objBegin[J] = T;
}

Object.keys(objBegin).forEach((k)=>{ keys.push(parseInt(k))});

for (let i = 0; i < keys.length; i++) {
    let keyI = keys[i],
        endI = objBegin[keyI],
        j = i +1,
        iDeleted = false,
        keyJ = keys[j],
        endJ = objBegin[keyJ],
        indexesJ = [];
    if (endI && endJ) {
        while(parseInt(keyJ) <= parseInt(endI) && !iDeleted && endJ !== undefined && j < keys.length) {
            if (endI <= endJ) {   
                delete objBegin[keyJ];
                keys.splice(j,1);
                j--;
            } else {
                delete objBegin[keyI];
                iDeleted = true;
                keys.splice(i,1);
                i--;
            }
            j++;
            keyJ = keys[j];
            endJ = objBegin[keyJ];
        } 
    }
}

console.log(Object.keys(objBegin).length);
