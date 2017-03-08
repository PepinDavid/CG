// game loop
while (true) {
    var arrMoun = [];
    var nbMountain = 0;
    var maxSize = 0;
    var tempSize = 0;
    for (var i = 0; i < 8; i++) {
        var mountainH = parseInt(readline()); // represents the height of one mountain.
        arrMoun.push(mountainH);
    }
    for(var i = 0; i < 8; i++) {
        tempSize = arrMoun[i];
        if(maxSize < tempSize)
            maxSize = tempSize,
            nbMountain = i;
    }
    print(nbMountain); // The index of the mountain to fire on.
}