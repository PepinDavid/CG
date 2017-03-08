var points = {
    e: 1, 
    a: 1, 
    i: 1, 
    o: 1, 
    n: 1, 
    r: 1, 
    t: 1, 
    l: 1, 
    s: 1, 
    u: 1,
    d: 2, 
    g: 2,
    b: 3, 
    c: 3, 
    m: 3, 
    p: 3,
    f: 4, 
    h: 4, 
    v: 4, 
    w: 4,
    y: 4,
    k: 5,
    j: 8, 
    x: 8,
    q: 10, 
    z: 10
}


var N = parseInt(readline());
var WORDS = []
for (var i = 0; i < N; i++) {
    var W = readline();
    if( W.length < 8)
        WORDS.push(W)
}
var LETTERS = readline();
printErr(LETTERS.length)
var goodWords = [];
for(var i = 0; i < WORDS.length; i++){
    var count = 0;
    var word = WORDS[i];
    for(var j = 0; j < LETTERS.length; j++){
        var k = word.indexOf(LETTERS[j]);
        if( k != -1)
            count++, word = word.slice(0,k)+word.slice(k+1, word.length);
            
        printErr(word)
    }
    if(WORDS[i].length == count)
        goodWords.push(WORDS[i]);
}
var max = 0, index = 0;
for(var i = 0; i < goodWords.length; i++){
    var total = 0;
    for(var j = 0; j < goodWords[i].length; j++){
        total += points[goodWords[i][j]];
    }
    if(total > max)
        max = total, index = i;
}

print(goodWords[index]);
